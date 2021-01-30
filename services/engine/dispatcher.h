#pragma once
#include "event_manager.h"
#include <minecpp/game/notifier.h>
#include <minecpp/game/entity/entity.h>

namespace Engine {

using boost::uuids::uuid;

class Dispatcher : public minecpp::game::Notifier {
   EventManager &events;

 public:
   explicit Dispatcher(EventManager &events);

   void load_terrain(boost::uuids::uuid player, minecpp::game::block::ChunkPos central_chunk,
                     std::vector<minecpp::game::block::ChunkPos> coords) override;

   void transfer_player(boost::uuids::uuid player, boost::uuids::uuid target_engine);

   void entity_move(int eid, uuid id, minecpp::game::entity::Movement movement, float yaw, float pitch) override;
};

} // namespace Engine
