#pragma once
#include "blocks/position.h"
#include <boost/uuid/uuid.hpp>
#include <vector>

namespace Game {

namespace Entity {
struct Movement;
}

using boost::uuids::uuid;

class Notifier {
 public:
   virtual void load_terrain(uuid player, Game::Block::ChunkPos central_chunk,
                             std::vector<Game::Block::ChunkPos> coords) = 0;
   virtual void entity_move(int eid, uuid id, Entity::Movement movement, float yaw, float pitch) = 0;
};

} // namespace Game
