#pragma once
#include "ApiHandler.h"
#include "minecpp/world/Chunk.h"
#include <minecpp/chat/Chat.h>
#include <minecpp/game/IDispatcher.hpp>
#include <minecpp/game/player/Id.h>
#include <minecpp/game/player/Player.h>

namespace minecpp::player {
class Player;
}

namespace minecpp::game {
class Entity;
}

namespace minecpp::entity {
class EntitySystem;
}

namespace minecpp::service::engine {

class EventManager;
class EntityManager;
using boost::uuids::uuid;

class Dispatcher : public minecpp::game::IDispatcher
{
 public:
   explicit Dispatcher(EventManager &events, entity::EntitySystem &entity_system);
   void spawn_entity(game::EntityId entity_id, const math::Vector3 &position) override;
   void load_terrain(game::PlayerId player_id, const game::ChunkPosition &central_chunk,
                     std::vector<minecpp::game::ChunkPosition> coords) override;
   void remove_entity(game::EntityId entity_id) override;
   void remove_entity_for_player(game::PlayerId player_id, game::EntityId entity_id) override;
   void transfer_player(game::PlayerId player_id, boost::uuids::uuid target_engine);
   void spawn_entity_for_player(game::PlayerId player_id, game::EntityId entity_id) override;
   void spawn_player_for_player(game::PlayerId receiver, game::PlayerId spawned_player,
                                game::EntityId entity_id) override;
   void update_block(game::BlockPosition block, game::BlockStateId state) override;

   void entity_move(game::EntityId entity_id, const math::Vector3 &position, const math::Vector3s &movement,
                    const math::Rotation &rotation, bool is_on_ground) override;
   void player_look(game::PlayerId player_id, game::EntityId entity_id, const math::Vector3 &position,
                    const math::Rotation &rotation) override;
   void entity_look(game::EntityId entity_id, const math::Vector3 &position,
                    const math::Rotation &rotation) override;
   void teleport_entity(game::EntityId entity_id, const math::Vector3 &position,
                        const math::Rotation &rotation, bool is_on_ground) override;

   void add_player(game::PlayerId player_id, const std::string &name, mb::u32 ping) override;
   void spawn_player(game::PlayerId player_id, game::EntityId entity_id,
                     const math::Vector3 &position) override;
   void remove_player(game::PlayerId player_id, mb::u32 entity_id) override;
   void send_chat(chat::MessageType msg_type, const std::string &msg) override;
   void send_direct_chat(game::PlayerId player_id, chat::MessageType msg_type,
                         const std::string &msg) override;
   void acknowledge_block_change(game::PlayerId player_id, int sequence_id) override;
   void animate_entity(game::EntityId entity_id, const math::Vector3 &position,
                       game::EntityAnimation animation) override;
   void animate_player_entity(game::PlayerId player_id, game::EntityId entity_id,
                              const math::Vector3 &position, game::EntityAnimation animation) override;
   void unload_chunk(game::PlayerId player_id, const game::ChunkPosition &chunk_position) override;

   void player_list(game::PlayerId player_id, const std::vector<game::player::Status> &status_list);
   void send_entities(game::PlayerId player_id, std::span<game::EntityId> entities) override;

   void accept_player(const game::player::Player &player_id);
   void deny_player(const game::PlayerId &player_id, const std::string &reason);

   void set_inventory_slot(game::PlayerId player_id, game::ItemId item_id, game::SlotId slot_id,
                           int count) override;
   void update_block_light(game::ISectionSlice &slice, game::SectionRange range) override;

   void send_chunk(game::PlayerId player_id, world::Chunk *chunk);
   void update_chunk_position(game::PlayerId player_id, const game::ChunkPosition &chunk_position) override;
   void synchronise_player_position_and_rotation(game::PlayerId player_id, math::Vector3 position,
                                                 math::Rotation rotation) override;
   void set_spawn_position(game::PlayerId player_id, game::BlockPosition position, float angle) override;
   void set_player_equipment(game::PlayerId player_id, game::EntityId entity_id, game::EquipmentSlot slot,
                             game::ItemSlot item) override;
   void set_health_and_food(game::PlayerId player_id, float health, int food, float food_saturation) override;
   void collect_item(game::EntityId collected_entity, game::EntityId collector_entity,
                     const math::Vector3 &position, int count) override;
   void set_entity_velocity(game::EntityId entity_id, const math::Vector3 &position,
                            const math::Vector3s &velocity) override;
   void display_death_screen(game::PlayerId player_id, game::EntityId victim_entity_id,
                             game::EntityId killer_entity_id, const std::string &message) override;
   void respawn_player(game::PlayerId player_id) override;

 private:
   void send_to_players_in_view_distance(const math::Vector3 &position,
                                         const google::protobuf::Message &message) const;
   void send_to_players_in_view_distance_except(game::PlayerId player_id, const math::Vector3 &position,
                                                const google::protobuf::Message &message) const;
   void send_to_player_visible_by(game::Entity &entity, const google::protobuf::Message &message) const;

   EventManager &m_events;
   entity::EntitySystem &m_entity_system;
};

}// namespace minecpp::service::engine
