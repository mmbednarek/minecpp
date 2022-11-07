#pragma once
#include "../IStorage.h"
#include "Fdb.h"
#include "Transaction.h"
#include <future>
#include <minecpp/game/Game.h>
#include <mutex>
#include <optional>

namespace minecpp::service::storage::fdb {

class Storage : public IStorage
{
 public:
   Storage(std::thread network_thread, FDBDatabase *database);
   ~Storage() override;

   Storage(Storage &)                      = delete;
   Storage &operator=(Storage &)           = delete;
   Storage(Storage &&) noexcept            = delete;
   Storage &operator=(Storage &&) noexcept = delete;

   static std::unique_ptr<Storage> create(std::string_view cluster_file_path);

   static void network_thread();

   bool write_chunk(const proto_chunk::Chunk &chunk) override;
   std::optional<proto_chunk::Chunk> read_chunk(game::ChunkPosition position) override;
   bool update_chunk(game::ChunkPosition position,
                     const std::function<void(proto_chunk::Chunk &chunk)> &callback) override;
   bool add_chunk_subscription(game::ChunkPosition position,
                               const proto_storage::ClientId &client_id) override;

 private:
   Result<Transaction> create_transaction();

   std::thread m_network_thread;
   FDBDatabase *m_database{};
   std::mutex m_mutex;
};

}// namespace minecpp::service::storage::fdb