#include "Storage.h"
#include "Future.h"
#include <fmt/core.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::storage::fdb {

Storage::~Storage()
{
   Error err(fdb_stop_network());
   if (not err.ok()) {
      spdlog::error("could not stop network: {}", err.to_string());
   }

   m_network_thread.join();
   fdb_database_destroy(m_database);
}

std::unique_ptr<Storage> Storage::create(std::string_view cluster_file_path)
{
   if (auto err = fdb_select_api_version(FDB_API_VERSION); err != 0) {
      spdlog::error("invalid api version: {}", fdb_get_error(err));
      return {};
   }

   if (auto err = fdb_setup_network(); err != 0) {
      spdlog::error("failed to setup network: {}", fdb_get_error(err));
      return {};
   }

   std::thread network_thread(&Storage::network_thread);

   FDBDatabase *database;

   if (auto err = fdb_create_database(cluster_file_path.data(), &database); err != 0) {
      spdlog::error("failed to create database: {}", fdb_get_error(err));
      if (auto err2 = fdb_stop_network(); err2 != 0) {
         spdlog::error("failed to stop network: {}", fdb_get_error(err2));
      }
      network_thread.join();
      return {};
   }

   return std::make_unique<Storage>(std::move(network_thread), database);
}

void Storage::network_thread()
{
   if (auto err = fdb_run_network(); err != 0) {
      spdlog::error("failed to create database: {}", fdb_get_error(err));
   }
}

bool Storage::write_chunk(const proto_chunk::Chunk &chunk)
{
   std::unique_lock lock{m_mutex};

   const auto chunk_position = game::ChunkPosition::from_proto(chunk.position());
   const auto key            = fmt::format("chunk_data.{}", chunk_position.hash());
   const auto data           = chunk.SerializeAsString();

   auto transaction = create_transaction();
   if (not transaction.ok()) {
      spdlog::error("fdb: failed to create transaction. {}", transaction.err().to_string());
      return false;
   }

   transaction->set(key, {data.data(), data.size()});

   const auto commit_future = transaction->commit();
   auto err                 = commit_future.await();
   if (not err.ok()) {
      spdlog::error("failed to commit transaction: {}", err.to_string());
      return false;
   }

   return true;
}

Result<Transaction> Storage::create_transaction()
{
   FDBTransaction *transaction{};
   Error err(fdb_database_create_transaction(m_database, &transaction));
   if (not err.ok()) {
      return err;
   }

   assert(transaction != nullptr);

   return Transaction(transaction);
}

std::optional<proto_chunk::Chunk> Storage::read_chunk(game::ChunkPosition position)
{
   std::unique_lock lock{m_mutex};

   auto key = fmt::format("chunk_data.{}", position.hash());

   auto transaction = create_transaction();
   if (not transaction.ok()) {
      spdlog::error("fdb: failed to create transaction. {}", transaction.err().to_string());
      return std::nullopt;
   }

   auto future = transaction->get(key);

   auto value = future.get_value();
   if (not value.ok()) {
      spdlog::error("fdb: failed to get value. {}", value.err().to_string());
      return std::nullopt;
   }

   if (value->data == nullptr)
      return std::nullopt;

   proto_chunk::Chunk chunk;
   if (not chunk.ParseFromArray(value->data, static_cast<int>(value->size)))
      return std::nullopt;

   return chunk;
}

Storage::Storage(std::thread network_thread, FDBDatabase *database) :
    m_network_thread{std::move(network_thread)},
    m_database{database}
{
}

bool Storage::update_chunk(game::ChunkPosition position,
                           const std::function<void(proto_chunk::Chunk &chunk)> &callback)
{
   std::unique_lock lock{m_mutex};

   game::ChunkPosition chunk_position{position.x(), position.z()};
   auto key = fmt::format("chunk_data.{}", chunk_position.hash());

   auto transaction = create_transaction();
   if (not transaction.ok()) {
      spdlog::error("fdb: failed to create transaction. {}", transaction.err().to_string());
      return false;
   }

   auto future = transaction->get(key);
   auto value  = future.get_value();
   if (not value.ok()) {
      spdlog::error("fdb: failed to get value. {}", value.err().to_string());
      return false;
   }

   proto_chunk::Chunk chunk;
   if (not chunk.ParseFromArray(value->data, static_cast<int>(value->size)))
      return false;

   callback(chunk);

   auto data = chunk.SerializeAsString();

   transaction->set(key, {data.data(), data.size()});

   auto commit_future = transaction->commit();
   return Error(commit_future.await()).ok();
}

bool Storage::add_chunk_subscription(game::ChunkPosition position, const proto_storage::ClientId &client_id)
{
   std::unique_lock lock{m_mutex};

   game::ChunkPosition chunk_position{position.x(), position.z()};
   auto key = fmt::format("chunk_subscription.{}", chunk_position.hash());

   auto transaction = create_transaction();
   if (not transaction.ok()) {
      spdlog::error("fdb: failed to create transaction. {}", transaction.err().to_string());
      return false;
   }

   auto future = transaction->get(key);
   auto value  = future.get_value();
   if (not value.ok()) {
      spdlog::error("fdb: failed to get value. {}", value.err().to_string());
      return false;
   }

   proto_storage::ChunkSubscription subscription;
   if (value->data != nullptr) {
      if (not subscription.ParseFromArray(value->data, static_cast<int>(value->size)))
         return false;
   }

   *subscription.mutable_client_ids()->Add() = client_id;

   auto data = subscription.SerializeAsString();

   transaction->set(key, {data.data(), data.size()});
   auto commit_future = transaction->commit();

   return Error(commit_future.await()).ok();
}

}// namespace minecpp::service::storage::fdb
