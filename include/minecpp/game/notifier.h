#pragma once
#include <boost/uuid/uuid.hpp>
#include <mb/int.h>
#include <minecpp/game/block/position.h>
#include <minecpp/util/vec.h>
#include <string>
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
   virtual void add_player(uuid player, const std::string &name, mb::u32 ping) = 0;
   virtual void spawn_player(uuid player, mb::u32 entity_id, util::Vec3 position, mb::f32 yaw, mb::f32 pitch) = 0;
   virtual void send_chat(mb::i32 msg_type, const std::string &msg) = 0;
   virtual void entity_look(uuid player, mb::u32 entity_id, mb::f32 yaw, mb::f32 pitch) = 0;
   virtual void remove_player(uuid player, mb::u32 entity_id) = 0;
   virtual void update_block(game::block::Position block, mb::u32 state) = 0;
   virtual void update_block(mb::i32 x, mb::i32 y, mb::i32 z, mb::u32 state) = 0;
   virtual void animate_hand(uuid player, mb::u32 entity_id, mb::u32 hand) = 0;
   virtual void unload_chunk(uuid player, mb::i32 x, mb::i32 z) = 0;
};

}// namespace minecpp::game
