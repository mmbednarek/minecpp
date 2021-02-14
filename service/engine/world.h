#pragma once
#include "dispatcher.h"
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <minecpp/game/world.h>
#include <minepb/chunk_storage.grpc.pb.h>

namespace Engine {

using ChunkService = std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub>;

using boost::uuids::uuid;
using minecpp::game::block::ChunkPos;

class World : public minecpp::game::World {
   const ChunkService &service;
   Dispatcher &dispatcher;
   uuid engine_id;

 public:
   World(uuid engine_id, const ChunkService &service, Dispatcher &dispatcher);

   minecpp::game::Notifier &notifier() override;
   mb::result<mb::empty> add_refs(uuid player, std::vector<ChunkPos> refs) override;
   mb::result<mb::empty> free_refs(uuid player, std::vector<ChunkPos> refs) override;
   mb::result<int> height_at(int x, int z) override;
};

}// namespace Engine
