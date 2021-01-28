#pragma once
#include <boost/uuid/uuid.hpp>
#include <minecpp/game/block/position.h>
#include <vector>

namespace minecpp::game {

namespace entity {
struct Movement;
}

using boost::uuids::uuid;

class Notifier {
 public:
   virtual void load_terrain(uuid player, game::block::ChunkPos central_chunk,
                             std::vector<game::block::ChunkPos> coords) = 0;
   virtual void entity_move(int eid, uuid id, entity::Movement movement, float yaw, float pitch) = 0;
};

}// namespace minecpp::game
