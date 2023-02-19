#pragma once
#include <boost/uuid/uuid.hpp>
#include <mb/int.h>
#include <minecpp/chat/Chat.h>
#include <minecpp/game/Entity.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/item/Item.h>
#include <minecpp/math/Vector3.h>
#include <string>
#include <vector>

namespace minecpp::game {

class ISectionSlice;

using boost::uuids::uuid;

class IDispatcher
{
 public:
   virtual void load_terrain(PlayerId player, const ChunkPosition &central_chunk,
                             std::vector<game::ChunkPosition> coords)                                     = 0;
   virtual void player_move(PlayerId player_id, EntityId entity_id, const math::Vector3s &movement,
                            const Rotation &rotation)                                                     = 0;
   virtual void entity_move(EntityId entity_id, const math::Vector3s &movement, const Rotation &rotation)       = 0;
   virtual void player_look(PlayerId player, EntityId entity_id, const Rotation &rotation)                 = 0;
   virtual void entity_look(EntityId entity_id, const Rotation &rotation)                                  = 0;
   virtual void add_player(PlayerId player, const std::string &name, mb::u32 ping)                        = 0;
   virtual void spawn_player(PlayerId player, EntityId entity_id, math::Vector3 position,
                             const Rotation &rotation)                                                    = 0;
   virtual void send_chat(chat::MessageType msg_type, const std::string &msg)                             = 0;
   virtual void send_direct_chat(game::PlayerId player_id, chat::MessageType msg_type,
                                 const std::string &msg)                                                  = 0;
   virtual void remove_player(PlayerId player, EntityId entity_id)                                         = 0;
   virtual void update_block(game::BlockPosition block, game::BlockStateId state)                         = 0;
   virtual void animate_entity(game::EntityId entity_id, game::EntityAnimation animation)                 = 0;
   virtual void animate_player_entity(game::PlayerId player_id, game::EntityId entity_id,
                                      game::EntityAnimation animation)                                    = 0;
   virtual void acknowledge_block_change(PlayerId player_id, int sequence_id)                             = 0;
   virtual void unload_chunk(PlayerId player, const game::ChunkPosition &chunk_position)                  = 0;
   virtual void set_inventory_slot(PlayerId player_id, ItemId item_id, SlotId slot_id, int count) = 0;
   virtual void update_block_light(ISectionSlice &slice, SectionRange range)                              = 0;
   virtual void update_chunk_position(PlayerId player_id, const game::ChunkPosition &chunk_position)      = 0;
   virtual void synchronise_player_position_and_rotation(PlayerId player_id, math::Vector3 position,
                                                         float yaw, float pitch)                          = 0;
   virtual void set_spawn_position(game::PlayerId player_id, game::BlockPosition position, float angle)   = 0;
   virtual void set_player_equipment(game::PlayerId player_id, game::EntityId entity_id,
                                     game::EquipmentSlot slot, game::ItemSlot item)                       = 0;
   virtual void set_health_and_food(game::PlayerId player_id, float health, int food,
                                    float food_saturation)                                                = 0;
};

}// namespace minecpp::game
