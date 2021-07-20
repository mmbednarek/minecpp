#pragma once
#include <boost/uuid/uuid.hpp>
#include <mb/int.h>
#include <minecpp/chat/chat.h>
#include <minecpp/game/game.h>
#include <minecpp/player/id.h>
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
   virtual void load_terrain(player::Id player, game::ChunkPosition central_chunk,
                             std::vector<game::ChunkPosition> coords) = 0;
   virtual void entity_move(int eid, uuid id, entity::Movement movement, float yaw, float pitch) = 0;
   virtual void add_player(player::Id player, const std::string &name, mb::u32 ping) = 0;
   virtual void spawn_player(player::Id player, mb::u32 entity_id, util::Vec3 position, mb::f32 yaw, mb::f32 pitch) = 0;
   virtual void send_chat(chat::MessageType msg_type, const std::string &msg) = 0;
   virtual void entity_look(player::Id player, mb::u32 entity_id, mb::f32 yaw, mb::f32 pitch) = 0;
   virtual void remove_player(player::Id player, mb::u32 entity_id) = 0;
   virtual void update_block(game::BlockPosition block, mb::u32 state) = 0;
   virtual void update_block(mb::i32 x, mb::i32 y, mb::i32 z, mb::u32 state) = 0;
   virtual void animate_hand(player::Id player, mb::u32 entity_id, mb::u32 hand) = 0;
   virtual void unload_chunk(player::Id player, mb::i32 x, mb::i32 z) = 0;
};

}// namespace minecpp::game
