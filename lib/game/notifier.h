#pragma once
#include "blocks/position.h"
#include <boost/uuid/uuid.hpp>
#include <vector>

namespace Game {

using boost::uuids::uuid;

class Notifier {
 public:
   virtual void load_terrain(uuid player, Game::Block::ChunkPos central_chunk,
                             std::vector<Game::Block::ChunkPos> coords) = 0;
};

} // namespace Game
