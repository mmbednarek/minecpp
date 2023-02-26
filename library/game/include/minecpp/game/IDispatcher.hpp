#pragma once
#include <boost/uuid/uuid.hpp>
#include <mb/int.h>
#include <minecpp/chat/Chat.h>
#include <minecpp/game/Entity.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/item/Item.h>
#include <minecpp/math/Vector3.h>
#include <span>
#include <string>
#include <vector>

namespace minecpp::game {

class ISectionSlice;

using boost::uuids::uuid;

class IDispatcher
{
 public:
   virtual void load_terrain(PlayerId player, const ChunkPosition &central_chunk,
                             std::vector<ChunkPosition> coords)                                          = 0;
   virtual void player_move(PlayerId player_id, EntityId entity_id, const math::Vector3 &position,
                            const math::Vector3s &movement, const Rotation &rotation)                    = 0;
   virtual void spawn_entity(EntityId entity_id, const math::Vector3 &position)                          = 0;
   virtual void spawn_entity_for_player(PlayerId player_id, EntityId entity_id)                          = 0;
   virtual void entity_move(EntityId entity_id, const math::Vector3 &position, const math::Vector3s &movement,
                            const Rotation &rotation)                                                    = 0;
   virtual void player_look(PlayerId player, EntityId entity_id, const math::Vector3 &position,
                            const Rotation &rotation)                                                    = 0;
   virtual void entity_look(EntityId entity_id, const math::Vector3 &position, const Rotation &rotation) = 0;
   virtual void entity_list(PlayerId player_id, std::span<EntityId> entities)                            = 0;
   virtual void add_player(PlayerId player, const std::string &name, mb::u32 ping)                       = 0;
   virtual void spawn_player(PlayerId player, EntityId entity_id, const math::Vector3 &position)         = 0;
   virtual void spawn_player_for_player(PlayerId receiver, PlayerId spawned_player, EntityId entity_id)  = 0;
   virtual void send_chat(chat::MessageType msg_type, const std::string &msg)                            = 0;
   virtual void send_direct_chat(PlayerId player_id, chat::MessageType msg_type, const std::string &msg) = 0;
   virtual void remove_player(PlayerId player, EntityId entity_id)                                       = 0;
   virtual void update_block(BlockPosition block, BlockStateId state)                                    = 0;
   virtual void animate_entity(EntityId entity_id, const math::Vector3 &position,
                               EntityAnimation animation)                                                = 0;
   virtual void animate_player_entity(PlayerId player_id, EntityId entity_id, const math::Vector3 &position,
                                      EntityAnimation animation)                                         = 0;
   virtual void acknowledge_block_change(PlayerId player_id, int sequence_id)                            = 0;
   virtual void unload_chunk(PlayerId player, const ChunkPosition &chunk_position)                       = 0;
   virtual void set_inventory_slot(PlayerId player_id, ItemId item_id, SlotId slot_id, int count)        = 0;
   virtual void update_block_light(ISectionSlice &slice, SectionRange range)                             = 0;
   virtual void update_chunk_position(PlayerId player_id, const ChunkPosition &chunk_position)           = 0;
   virtual void synchronise_player_position_and_rotation(PlayerId player_id, math::Vector3 position,
                                                         float yaw, float pitch)                         = 0;
   virtual void set_spawn_position(PlayerId player_id, BlockPosition position, float angle)              = 0;
   virtual void set_player_equipment(PlayerId player_id, EntityId entity_id, EquipmentSlot slot,
                                     ItemSlot item)                                                      = 0;
   virtual void set_health_and_food(PlayerId player_id, float health, int food, float food_saturation)   = 0;
   virtual void collect_item(EntityId collected_entity, EntityId collector_entity,
                             const math::Vector3 &position, int count)                                   = 0;
   virtual void remove_entity(EntityId entity_id)                                                        = 0;
   virtual void remove_entity_for_player(PlayerId player_id, EntityId entity_id)                         = 0;
   virtual void set_entity_velocity(EntityId entity_id, const math::Vector3 &position,
                                    const math::Vector3s &velocity)                                      = 0;
};

}// namespace minecpp::game
