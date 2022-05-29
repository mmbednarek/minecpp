#pragma once
#include <boost/uuid/uuid.hpp>
#include <mb/int.h>
#include <minecpp/chat/chat.h>
#include <minecpp/entity/entity.h>
#include <minecpp/game/game.h>
#include <minecpp/game/item/item.h>
#include <minecpp/player/id.h>
#include <minecpp/player/inventory.h>
#include <minecpp/util/vec.h>
#include <string>
#include <vector>

namespace minecpp::game {

namespace entity {
struct Movement;
}

using boost::uuids::uuid;

class Notifier
{
 public:
   virtual void load_terrain(player::Id player, const ChunkPosition &central_chunk,
                             std::vector<game::ChunkPosition> coords)                      = 0;
   virtual void entity_move(player::Id player_id, minecpp::entity::Id entity_id,
                            const minecpp::entity::Movement &movement,
                            const minecpp::entity::Rotation &rotation)                     = 0;
   virtual void add_player(player::Id player, const std::string &name, mb::u32 ping)       = 0;
   virtual void spawn_player(player::Id player, mb::u32 entity_id, minecpp::util::Vec3 position,
                             const minecpp::entity::Rotation &rotation)                    = 0;
   virtual void send_chat(chat::MessageType msg_type, const std::string &msg)              = 0;
   virtual void entity_look(player::Id player, mb::u32 entity_id,
                            const minecpp::entity::Rotation &rotation)                     = 0;
   virtual void remove_player(player::Id player, mb::u32 entity_id)                        = 0;
   virtual void update_block(game::BlockPosition block, game::BlockState state)            = 0;
   virtual void animate_hand(player::Id player, mb::u32 entity_id, mb::u32 hand)           = 0;
   virtual void acknowledge_player_digging(player::Id player_id, game::BlockPosition &pos,
                                           game::BlockState block_state, PlayerDiggingState state,
                                           bool successful)                                = 0;
   virtual void unload_chunk(player::Id player, const game::ChunkPosition &chunk_position) = 0;
   virtual void set_inventory_slot(player::Id player_id, item::ItemId item_id, player::SlotId slot_id,
                                   std::size_t count)                                      = 0;
};

}// namespace minecpp::game
