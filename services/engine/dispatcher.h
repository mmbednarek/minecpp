#pragma once
#include "event_manager.h"
#include <minecpp/game/entity/entity.h>
#include <minecpp/game/notifier.h>

namespace Engine {

using boost::uuids::uuid;

class Dispatcher : public minecpp::game::Notifier {
   EventManager &events;

 public:
   explicit Dispatcher(EventManager &events);

   void load_terrain(boost::uuids::uuid player, minecpp::game::block::ChunkPos central_chunk,
                     std::vector<minecpp::game::block::ChunkPos> coords) override;
   void transfer_player(boost::uuids::uuid player, boost::uuids::uuid target_engine);
   void update_block(minecpp::game::block::Position block, mb::u32 state) override;

   void entity_move(int eid, uuid id, minecpp::game::entity::Movement movement, float yaw, float pitch) override;
   void entity_look(uuid player, mb::u32 entity_id, mb::f32 yaw, mb::f32 pitch) override;

   void add_player(uuid player, const std::string &name, mb::u32 ping) override;
   void spawn_player(uuid player, mb::u32 entity_id, minecpp::util::Vec3 position, mb::f32 yaw, mb::f32 pitch) override;
   void remove_player(uuid player, mb::u32 entity_id) override;
   void send_chat(mb::i32 msg_type, const std::string &msg) override;
   void update_block(mb::i32 x, mb::i32 y, mb::i32 z, mb::u32 state) override;
   void animate_hand(uuid player, mb::u32 entity_id, mb::u32 hand) override;
   void unload_chunk(uuid player, mb::i32 x, mb::i32 z) override;
};

}// namespace Engine
