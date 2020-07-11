#pragma once
#include "dispatcher.h"
#include <boost/uuid/uuid.hpp>
#include <game/world.h>
#include <minepb/chunk_storage.grpc.pb.h>

namespace Engine {

using ChunkService = std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub>;

using boost::uuids::uuid;
using Game::Block::ChunkPos;

class World : public Game::World {
   const ChunkService &service;
   Dispatcher &dispatcher;
   uuid engine_id;

 public:
   World(uuid engine_id, const ChunkService &service, Dispatcher &dispatcher);

   Game::Notifier &notifier() override;
   void add_refs(uuid player, std::vector<ChunkPos> refs) override;
   void free_refs(uuid player, std::vector<ChunkPos> refs) override;
   int height_at(int x, int z) override;
};

} // namespace Engine
