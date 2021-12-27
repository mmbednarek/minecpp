#pragma once
#include "dispatcher.h"
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <minecpp/game/world.h>
#include <minecpp/proto/service/chunk_storage/v1/chunk_storage.grpc.pb.h>

namespace minecpp::service::engine {

using ChunkService = minecpp::proto::service::chunk_storage::v1::ChunkStorage::Stub;

using boost::uuids::uuid;
using minecpp::game::ChunkPosition;

class World : public minecpp::game::World {
   ChunkService &service;
   Dispatcher &dispatcher;
   uuid engine_id;

 public:
   World(uuid engine_id, ChunkService &service, Dispatcher &dispatcher);

   minecpp::game::Notifier &notifier() override;
   mb::result<mb::empty> add_refs(player::Id player, std::vector<game::ChunkPosition> refs) override;
   mb::result<mb::empty> free_refs(player::Id player, std::vector<game::ChunkPosition> refs) override;
   mb::result<int> height_at(int x, int z) override;
   mb::result<mb::empty> set_block(const game::BlockPosition &pos, game::BlockState state) override;
};

}// namespace minecpp::service::engine
