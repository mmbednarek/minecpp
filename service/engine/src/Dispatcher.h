#pragma once
#include "ApiHandler.h"
#include "minecpp/world/Chunk.h"
#include <minecpp/chat/Chat.h>
#include <minecpp/game/Notifier.h>
#include <minecpp/game/player/Id.h>
#include <minecpp/game/player/Player.h>

namespace minecpp::player {
class Player;
}

namespace minecpp::entity {
class EntitySystem;
}

namespace minecpp::service::engine {

class EventManager;
class EntityManager;
using boost::uuids::uuid;

class Dispatcher : public minecpp::game::Notifier
{
 public:
   explicit Dispatcher(EventManager &events, entity::EntitySystem &entity_system);

   void load_terrain(game::PlayerId player_id, const game::ChunkPosition &central_chunk,
                     std::vector<minecpp::game::ChunkPosition> coords) override;
   void transfer_player(game::PlayerId player_id, boost::uuids::uuid target_engine);
   void update_block(game::BlockPosition block, game::BlockStateId state) override;

   void player_move(game::PlayerId player_id, game::EntityId entity_id, const math::Vector3s &movement,
                    const game::Rotation &rotation) override;
   void entity_move(game::EntityId entity_id, const math::Vector3s &movement,
                    const game::Rotation &rotation) override;
   void player_look(game::PlayerId player_id, mb::u32 entity_id, const game::Rotation &rotation) override;
   void entity_look(mb::u32 entity_id, const game::Rotation &rotation) override;

   void add_player(game::PlayerId player_id, const std::string &name, mb::u32 ping) override;
   void spawn_player(game::PlayerId player_id, mb::u32 entity_id, math::Vector3 position,
                     const game::Rotation &rotation) override;
   void remove_player(game::PlayerId player_id, mb::u32 entity_id) override;
   void send_chat(chat::MessageType msg_type, const std::string &msg) override;
   void send_direct_chat(game::PlayerId player_id, chat::MessageType msg_type,
                         const std::string &msg) override;
   void acknowledge_block_change(game::PlayerId player_id, int sequence_id) override;
   void animate_entity(game::EntityId entity_id, game::EntityAnimation animation) override;
   void animate_player_entity(game::PlayerId player_id, game::EntityId entity_id,
                              game::EntityAnimation animation) override;
   void unload_chunk(game::PlayerId player_id, const game::ChunkPosition &chunk_position) override;

   void player_list(game::PlayerId player_id, const std::vector<game::player::Status> &status_list);
   void entity_list(game::PlayerId player_id, const math::Vector3 &origin, double range);

   void accept_player(const game::player::Player &player_id);
   void deny_player(const game::PlayerId &player_id, const std::string &reason);

   void set_inventory_slot(game::PlayerId player_id, game::ItemId item_id, game::SlotId slot_id,
                           std::size_t count) override;
   void update_block_light(game::ISectionSlice &slice, game::SectionRange range) override;

   void send_chunk(game::PlayerId player_id, world::Chunk *chunk);
   void update_chunk_position(game::PlayerId player_id, const game::ChunkPosition &chunk_position) override;
   void synchronise_player_position_and_rotation(game::PlayerId player_id, math::Vector3 position, float yaw,
                                                 float pitch) override;
   void set_spawn_position(game::PlayerId player_id, game::BlockPosition position, float angle) override;
   void set_player_equipment(game::PlayerId player_id, game::EntityId entity_id, game::EquipmentSlot slot,
                             game::ItemSlot item) override;
   void set_health_and_food(game::PlayerId player_id, float health, int food, float food_saturation) override;

 private:
   EventManager &m_events;
   entity::EntitySystem &m_entity_system;
};

}// namespace minecpp::service::engine
