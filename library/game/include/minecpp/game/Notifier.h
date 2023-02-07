#pragma once
#include <boost/uuid/uuid.hpp>
#include <mb/int.h>
#include <minecpp/chat/Chat.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/item/Item.h>
#include <minecpp/util/Vec.h>
#include <string>
#include <vector>

namespace minecpp::game {

class ISectionSlice;

namespace entity {
struct Movement;
struct Rotation;
}// namespace entity

using boost::uuids::uuid;

class Notifier
{
 public:
   virtual void load_terrain(PlayerId player, const ChunkPosition &central_chunk,
                             std::vector<game::ChunkPosition> coords)                                     = 0;
   virtual void entity_move(PlayerId player_id, EntityId entity_id, const entity::Movement &movement,
                            const entity::Rotation &rotation)                                             = 0;
   virtual void add_player(PlayerId player, const std::string &name, mb::u32 ping)                        = 0;
   virtual void spawn_player(PlayerId player, mb::u32 entity_id, minecpp::util::Vec3 position,
                             const entity::Rotation &rotation)                                            = 0;
   virtual void send_chat(chat::MessageType msg_type, const std::string &msg)                             = 0;
   virtual void send_direct_chat(game::PlayerId player_id, chat::MessageType msg_type,
                                 const std::string &msg)                                                  = 0;
   virtual void entity_look(PlayerId player, mb::u32 entity_id, const entity::Rotation &rotation)         = 0;
   virtual void remove_player(PlayerId player, mb::u32 entity_id)                                         = 0;
   virtual void update_block(game::BlockPosition block, game::BlockStateId state)                         = 0;
   virtual void animate_hand(PlayerId player, mb::u32 entity_id, mb::u32 hand)                            = 0;
   virtual void acknowledge_block_change(PlayerId player_id, int sequence_id)                             = 0;
   virtual void unload_chunk(PlayerId player, const game::ChunkPosition &chunk_position)                  = 0;
   virtual void set_inventory_slot(PlayerId player_id, ItemId item_id, SlotId slot_id, std::size_t count) = 0;
   virtual void update_block_light(ISectionSlice &slice, SectionRange range)                              = 0;
   virtual void update_chunk_position(PlayerId player_id, const game::ChunkPosition &chunk_position)      = 0;
   virtual void synchronise_player_position_and_rotation(PlayerId player_id, minecpp::util::Vec3 position,
                                                         float yaw, float pitch)                          = 0;
   virtual void set_spawn_position(game::PlayerId player_id, game::BlockPosition position, float angle)   = 0;
   virtual void set_player_equipment(game::PlayerId player_id, game::EntityId entity_id,
                                     game::EquipmentSlot slot, game::ItemSlot item)                       = 0;
};

}// namespace minecpp::game
