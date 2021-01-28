#pragma once
#include "event_manager.h"
#include <minecpp/game/notifier.h>
#include <minecpp/game/entity/entity.h>

namespace Engine {

using boost::uuids::uuid;

class Dispatcher : public Game::Notifier {
   EventManager &events;

 public:
   explicit Dispatcher(EventManager &events);

   void load_terrain(boost::uuids::uuid player, Game::Block::ChunkPos central_chunk,
                     std::vector<Game::Block::ChunkPos> coords) override;

   void transfer_player(boost::uuids::uuid player, boost::uuids::uuid target_engine);

   void entity_move(int eid, uuid id, Game::Entity::Movement movement, float yaw, float pitch) override;
};

} // namespace Engine
