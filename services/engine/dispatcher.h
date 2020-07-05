#pragma once
#include "event_manager.h"
#include <game/notifier.h>

namespace Engine {

class Dispatcher : public Game::Notifier {
   EventManager &events;

 public:
   explicit Dispatcher(EventManager &events);

   void load_terrain(boost::uuids::uuid player, Game::Block::ChunkPos central_chunk,
                     std::vector<Game::Block::ChunkPos> coords) override;

   void transfer_player(boost::uuids::uuid player, boost::uuids::uuid target_engine);
};

} // namespace Engine
