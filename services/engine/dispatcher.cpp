#include "dispatcher.h"
#include <minepb/events.pb.h>

namespace Engine {

Dispatcher::Dispatcher(EventManager &events) : events(events) {}

void Dispatcher::load_terrain(boost::uuids::uuid player, Game::Block::ChunkPos central_chunk,
                              std::vector<Game::Block::ChunkPos> coords) {
   minecpp::events::LoadTerrain event;
   event.set_uuid(player.data, player.size());
   event.mutable_central_chunk()->set_x(central_chunk.x);
   event.mutable_central_chunk()->set_z(central_chunk.z);
   for (const auto &c : coords) {
      auto new_coord = event.add_coords();
      new_coord->set_x(c.x);
      new_coord->set_z(c.z);
   }
   events.post(event);
}

void Dispatcher::transfer_player(boost::uuids::uuid player, boost::uuids::uuid target_engine) {
   minecpp::events::TransferPlayer event;
   event.set_player(player.data, player.size());
   event.set_target_engine(target_engine.data, target_engine.size());
   events.post(event);
}

void Dispatcher::entity_move(int eid, uuid id, Game::Entity::Movement movement, float yaw, float pitch) {
   minecpp::events::EntityMove event;
   event.set_id(eid);
   event.set_uuid(id.data, id.size());
   event.set_x(movement.x);
   event.set_y(movement.y);
   event.set_z(movement.z);
   event.set_yaw(yaw);
   event.set_pitch(pitch);
   events.post(event);
}

} // namespace Engine
