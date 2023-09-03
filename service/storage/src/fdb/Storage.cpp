#include "Storage.h"
#include "Future.h"

#include "minecpp/net/storage/Serverbound.schema.h"
#include "minecpp/util/Cast.hpp"

#include <fmt/core.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::storage::fdb {

Storage::~Storage()
{
   Error err(fdb_stop_network());
   if (not err.ok()) {
      auto msg = err.to_string();
      spdlog::error("could not stop network: {}", msg);
   }

   m_network_thread.join();
   fdb_database_destroy(m_database);
}

std::unique_ptr<Storage> Storage::create(std::string_view cluster_file_path)
{
   if (auto err = fdb_select_api_version(FDB_API_VERSION); err != 0) {
      const auto *err_msg = fdb_get_error(err);
      spdlog::error("invalid api version: {}", err_msg);
      return {};
   }

   if (auto err = fdb_setup_network(); err != 0) {
      auto err_msg = fdb_get_error(err);
      spdlog::error("failed to setup network: {}", err_msg);
      return {};
   }

   std::thread network_thread(&Storage::network_thread);

   FDBDatabase *database;

   if (auto err = fdb_create_database(cluster_file_path.data(), &database); err != 0) {
      auto err_msg = fdb_get_error(err);
      spdlog::error("failed to create database: {}", err_msg);
      if (auto err2 = fdb_stop_network(); err2 != 0) {
         auto err_msg2 = fdb_get_error(err2);
         spdlog::error("failed to stop network: {}", err_msg2);
      }
      network_thread.join();
      return {};
   }

   return std::make_unique<Storage>(std::move(network_thread), database);
}

void Storage::network_thread()
{
   if (auto err = fdb_run_network(); err != 0) {
      auto err_msg = fdb_get_error(err);
      spdlog::error("failed to create database: {}", err_msg);
   }
}

bool Storage::write_chunk(const net::Chunk &chunk)
{
   std::unique_lock lock{m_mutex};

   network::message::Writer writer;
   chunk.serialize(writer);

   const auto key = fmt::format("chunk_data.{}", game::ChunkPosition(chunk.position).hash());

   auto transaction = create_transaction();
   if (not transaction.ok()) {
      auto err_msg = transaction.err().to_string();
      spdlog::error("fdb: failed to create transaction. {}", err_msg);
      return false;
   }

   transaction->set(key, {writer.view().data(), writer.view().size()});

   const auto commit_future = transaction->commit();
   auto err                 = commit_future.await();
   if (not err.ok()) {
      auto err_msg = err.to_string();
      spdlog::error("failed to commit transaction: {}", err_msg);
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

std::optional<net::Chunk> Storage::read_chunk(game::ChunkPosition position)
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
      auto err_msg = value.err().to_string();
      spdlog::error("fdb: failed to get value. {}", err_msg);
      return std::nullopt;
   }

   if (value->data == nullptr)
      return std::nullopt;

   container::BufferView buffer{util::unsafe_cast<unsigned char *>(value->data), value->size};
   auto buff_stream = buffer.make_stream();

   network::message::Reader reader(buff_stream);
   auto chunk = net::Chunk::deserialize(reader);

   return chunk;
}

Storage::Storage(std::thread network_thread, FDBDatabase *database) :
    m_network_thread{std::move(network_thread)},
    m_database{database}
{
}

bool Storage::update_chunk(game::ChunkPosition position,
                           const std::function<void(net::Chunk &chunk)> &callback)
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

   container::BufferView buffer{util::unsafe_cast<unsigned char *>(value->data), value->size};
   auto buff_stream = buffer.make_stream();

   network::message::Reader reader(buff_stream);
   auto chunk = net::Chunk::deserialize(reader);

   callback(chunk);

   network::message::Writer writer;
   chunk.serialize(writer);

   transaction->set(key, {writer.view().data(), writer.view().size()});

   auto commit_future = transaction->commit();
   return Error(commit_future.await()).ok();
}

bool Storage::add_chunk_subscription(game::ChunkPosition position, std::uint64_t client_id)
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

   container::BufferView buffer{util::unsafe_cast<unsigned char *>(value->data), value->size};
   auto buff_stream = buffer.make_stream();
   network::message::Reader reader(buff_stream);

   auto subscription = net::storage::sb::ChunkSubscription::deserialize(reader);

   subscription.client_ids.push_back(client_id);

   network::message::Writer writer;
   subscription.serialize(writer);

   transaction->set(key, {writer.view().data(), writer.view().size()});
   auto commit_future = transaction->commit();

   return Error(commit_future.await()).ok();
}

}// namespace minecpp::service::storage::fdb
