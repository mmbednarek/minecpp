#include "Dispatcher.h"

#include "ChunkSystem.h"
#include "EventManager.h"

#include "minecpp/chat/Chat.h"
#include "minecpp/debug/TraceManager.h"
#include "minecpp/entity/Aliases.hpp"
#include "minecpp/entity/component/Abilities.h"
#include "minecpp/entity/component/Location.h"
#include "minecpp/entity/component/Player.h"
#include "minecpp/entity/EntitySystem.h"
#include "minecpp/game/ChunkPosition.h"
#include "minecpp/game/ChunkRange.h"
#include "minecpp/game/player/Player.h"
#include "minecpp/net/play/Clientbound.schema.h"
#include "minecpp/util/Uuid.h"
#include "minecpp/world/ChunkSerializer.h"
#include "minecpp/world/SectionSlice.h"

namespace minecpp::service::engine {

Dispatcher::Dispatcher(EventManager &events, ChunkSystem &chunk_system, entity::EntitySystem &entity_system,
                       nbt::repository::Registry &registry) :
    m_events{events},
    m_chunk_system{chunk_system},
    m_entity_system{entity_system},
    m_registry{registry}
{
}

void Dispatcher::entity_move(game::EntityId entity_id, const math::Vector3 &position,
                             const math::Vector3s &movement, const math::Rotation &rotation,
                             const bool is_on_ground)
{
   net::play::cb::EntityMove entity_move{
           .entity_id    = entity_id,
           .difference   = movement,
           .yaw          = math::radians_to_degrees(rotation.yaw),
           .pitch        = math::radians_to_degrees(rotation.pitch),
           .is_on_ground = is_on_ground,
   };

   auto entity = m_entity_system.entity(entity_id);
   if (entity.has_component<PlayerComponent>()) {
      this->send_raw_to_player_visible_by(entity, entity_move);
   } else {
      this->send_raw_to_players_in_view_distance(position, entity_move);
   }
}

void Dispatcher::add_player(game::PlayerId player_id, const std::string &name, mb::u32 ping)
{
   auto add_player = net::play::cb::UpdatePlayerInfo{
           .action_bits = 0b11101,
   };
   add_player.actions.push_back(net::play::cb::PlayerInfoChange{
           .player_id = player_id,
           .add_player =
                   net::play::cb::ActionAddPlayer{
                                                  .name = name,
                                                  .properties{},
                                                  },
           .set_game_mode =
                   net::play::cb::ActionSetGameMode{
                                                  .game_mode = 0,
                                                  },
           .set_is_listed =
                   net::play::cb::ActionSetIsListed{
                                                  .is_listed = true,
                                                  },
           .set_latency =
                   net::play::cb::ActionSetLatency{
                                                  .ping = static_cast<std::int32_t>(ping),
                                                  },
   });

   this->send_raw_to_all(add_player);
}

void Dispatcher::send_chat(chat::MessageType msg_type, const std::string &msg)
{
   net::play::cb::SystemChat chat{
           .message      = msg,
           .is_actionbar = msg_type == chat::MessageType::SystemMessage,
   };
   this->send_raw_to_all(chat);
}

void Dispatcher::send_direct_chat(game::PlayerId player_id, chat::MessageType msg_type,
                                  const std::string &msg)
{
   net::play::cb::SystemChat chat{
           .message      = msg,
           .is_actionbar = msg_type == chat::MessageType::SystemMessage,
   };
   this->send_raw_to_player(player_id, chat);
}

void Dispatcher::entity_look(game::EntityId entity_id, const math::Vector3 &position,
                             const math::Rotation &rotation)
{
   auto entity = m_entity_system.entity(entity_id);

   net::play::cb::EntityMove entity_look{
           .entity_id    = entity_id,
           .difference   = math::Vector3s{0, 0, 0},
           .yaw          = math::radians_to_degrees(rotation.yaw),
           .pitch        = math::radians_to_degrees(rotation.pitch),
           .is_on_ground = entity.component<LocationComponent>().is_on_ground(),
   };

   if (entity.has_component<PlayerComponent>()) {
      this->send_raw_to_player_visible_by(entity, entity_look);

      net::play::cb::EntityHeadLook entity_head_look{
              .entity_id = entity_id,
              .yaw       = math::radians_to_degrees(rotation.yaw),
      };
      this->send_raw_to_player_visible_by(entity, entity_head_look);
   } else {
      this->send_raw_to_players_in_view_distance(position, entity_look);
   }
}

void Dispatcher::remove_player(game::PlayerId player_id, mb::u32 entity_id)
{
   auto entity = m_entity_system.entity(entity_id);

   net::play::cb::RemoveEntities destroy_entity{
           .entity_ids{entity_id},
   };
   this->send_raw_to_player_visible_by(entity, destroy_entity);

   net::play::cb::RemovePlayerInfo remove_player{
           .player_ids{player_id},
   };
   this->send_raw_to_all(remove_player);
}

void Dispatcher::update_block(minecpp::game::BlockPosition block_position, game::BlockStateId state)
{
   net::play::cb::BlockChange change{
           .block_position = block_position.as_long(),
           .block_id       = state,
   };
   this->send_raw_to_players_in_view_distance(block_position.to_vector3(), change);
}

void Dispatcher::animate_entity(game::EntityId entity_id, const math::Vector3 &position,
                                game::EntityAnimation animation)
{
   net::play::cb::AnimateEntity animate{
           .entity_id = entity_id,
           .type      = static_cast<std::uint8_t>(animation),
   };
   this->send_raw_to_players_in_view_distance(position, animate);
}

void Dispatcher::animate_player_entity(game::PlayerId player_id, game::EntityId entity_id,
                                       const math::Vector3 &position, game::EntityAnimation animation)
{
   net::play::cb::AnimateEntity animate{
           .entity_id = entity_id,
           .type      = static_cast<std::uint8_t>(animation),
   };
   this->send_raw_to_players_in_view_distance_except(player_id, position, animate);
}

void Dispatcher::acknowledge_block_change(game::PlayerId player_id, int sequence_id)
{
   net::play::cb::AcknowledgeBlockChanges acknowledge{
           .sequence_id = static_cast<std::uint32_t>(sequence_id),
   };
   this->send_raw_to_player(player_id, acknowledge);
}

void Dispatcher::unload_chunk(game::PlayerId player_id, const game::ChunkPosition &chunk_position)
{
   net::play::cb::UnloadChunk unload_chunk{
           .position = chunk_position.position(),
   };
   this->send_raw_to_player(player_id, unload_chunk);
}

void Dispatcher::accept_player(const game::player::Player &player)
{
   auto entity = m_entity_system.entity(player.entity_id());
   assert(entity.has_component<entity::component::Abilities>());

   this->send_raw_to_player(player.id(), net::play::cb::JoinGame{
                                                 .entity_id          = player.entity_id(),
                                                 .game_mode          = 0,
                                                 .previous_game_mode = 0,
                                                 .available_dimensions{"overworld", "the_nether", "the_end",
                                                                       "overworld_caves"},
                                                 .dimension_codec            = m_registry,
                                                 .dimension_name             = "minecraft:overworld",
                                                 .world_name                 = "overworld",
                                                 .seed                       = 0,
                                                 .max_players                = 32,
                                                 .view_distance              = 32,
                                                 .reduced_debug_info         = false,
                                                 .should_show_respawn_screen = true,
                                                 .is_debug                   = false,
                                                 .is_flat                    = false,
                                                 .death_location{}
   });

   this->send_raw_to_player(player.id(), net::play::cb::PluginMessage{"minecraft:brand", "minecpp"});

   this->send_raw_to_player(player.id(), net::play::cb::Difficulty{
                                                 .difficulty = 0,
                                                 .locked     = false,
                                         });

   auto abilities = entity.component<AbilitiesComponent>();
   this->send_raw_to_player(player.id(), net::play::cb::PlayerAbilities{
                                                 .flags = static_cast<mb::u8>(abilities.abilities().flags()),
                                                 .fly_speed     = abilities.abilities().fly_speed,
                                                 .field_of_view = abilities.abilities().field_of_view,
                                         });

   // TODO: Send command list
   this->send_raw_to_player(player.id(), net::play::cb::RecipeBook{
                                                 .state = 0,
                                                 .crafting_table{
                                                                 .is_open                = false,
                                                                 .is_filtering_craftable = false,
                                                                 },
                                                 .furnace{
                                                                 .is_open                = false,
                                                                 .is_filtering_craftable = false,
                                                                 },
                                                 .blaster{
                                                                 .is_open                = false,
                                                                 .is_filtering_craftable = false,
                                                                 },
                                                 .smoker{
                                                                 .is_open                = false,
                                                                 .is_filtering_craftable = false,
                                                                 },
                                                 .recipes{},
                                                 .additional_recipes{
                                                                 net::play::cb::RecipeList{},
                                                                 },
   });
}

void Dispatcher::deny_player(const game::PlayerId &player_id, const std::string &reason)
{
   this->send_raw_to_player(player_id, net::play::cb::Disconnect{
                                               .reason = format::Builder()
                                                                 .bold(format::Color::Red, "DISCONNECTED ")
                                                                 .text(reason)
                                                                 .to_string(),
                                       });
}

void Dispatcher::player_list(game::PlayerId player_id, const std::vector<game::player::Status> &status_list)
{
   auto player_list = net::play::cb::UpdatePlayerInfo{
           .action_bits = 0b11101,
   };

   for (const auto &status : status_list) {
      player_list.actions.push_back(net::play::cb::PlayerInfoChange{
              .player_id = status.id,
              .add_player =
                      net::play::cb::ActionAddPlayer{
                                                     .name = status.name,
                                                     .properties{},
                                                     },
              .set_game_mode =
                      net::play::cb::ActionSetGameMode{
                                                     .game_mode = 0,
                                                     },
              .set_is_listed =
                      net::play::cb::ActionSetIsListed{
                                                     .is_listed = true,
                                                     },
              .set_latency =
                      net::play::cb::ActionSetLatency{
                                                     .ping = status.ping,
                                                     },
      });
   }

   this->send_raw_to_player(player_id, player_list);
}

void Dispatcher::send_entities(game::PlayerId player_id, std::span<game::EntityId> entities)
{
   for (const auto entity_id : entities) {
      this->spawn_entity_for_player(player_id, entity_id);
   }
}

void Dispatcher::set_inventory_slot(game::PlayerId player_id, game::ItemId item_id, game::SlotId slot_id,
                                    int count)
{
   this->send_raw_to_player(
           player_id, net::play::cb::SetSlot{
                              .window_id = 0,
                              .state_id  = 0,
                              .slot_id   = static_cast<short>(slot_id),
                              .slot      = count == 0 ? std::nullopt
                                                      : std::make_optional(net::Slot{
                                                                .item_id    = item_id,
                                                                .item_count = static_cast<std::int8_t>(count),
                                                   }),
                      });
}

void Dispatcher::update_block_light(const math::Vector3 &center, game::SectionRange range)
{
   assert(range.min_section() <= range.max_section());

   auto chunk_range = range.to_chunk_range();

   for (const auto chunk_position : chunk_range) {
      auto *chunk = m_chunk_system.chunk_at(chunk_position);
      world::ChunkSerializer serializer(*chunk);

      net::play::cb::UpdateLight update_light;
      serializer.write_update_light(update_light, game::LightType::Block, range.min_section(),
                                    range.max_section());

      this->send_raw_to_players_in_view_distance(center, update_light);
   }
}

void Dispatcher::send_chunk(game::PlayerId player_id, world::Chunk *chunk, bool is_initial)
{
   net::play::cb::UpdateChunk update_chunk;
   world::ChunkSerializer serializer(*chunk);
   serializer.write_chunk(update_chunk.chunk);
   this->send_raw_to_player(player_id, update_chunk);

   MCPP_TRACE(ChunkSentToPlayer, _.chunk_x = chunk->position().x(), _.chunk_z = chunk->position().z(),
              _.player_id = boost::uuids::to_string(player_id));
}

void Dispatcher::update_chunk_position(game::PlayerId player_id, const game::ChunkPosition &chunk_position)
{
   net::play::cb::UpdateChunkPosition update_chunk_position;
   update_chunk_position.chunk_position = chunk_position.position();

   this->send_raw_to_player(player_id, update_chunk_position);
}

void Dispatcher::synchronise_player_position_and_rotation(game::PlayerId player_id, math::Vector3 position,
                                                          math::Rotation rotation)
{
   net::play::cb::PlayerPositionLook player_position_look;
   player_position_look.position = position;
   player_position_look.yaw      = rotation.yaw_degrees();
   player_position_look.pitch    = rotation.pitch_degrees();

   this->send_raw_to_player(player_id, player_position_look);
}

void Dispatcher::set_spawn_position(game::PlayerId player_id, game::BlockPosition position, float angle)
{
   net::play::cb::SetDefaultSpawnPosition set_spawn_position;
   set_spawn_position.position = position.as_long();
   set_spawn_position.angle    = angle;

   this->send_raw_to_player(player_id, set_spawn_position);
}

void Dispatcher::set_player_equipment(game::PlayerId player_id, game::EntityId entity_id,
                                      game::EquipmentSlot slot, game::ItemSlot item)
{
   net::play::cb::SetEquipment set_equipment;
   set_equipment.entity_id = entity_id;
   set_equipment.slot_id   = static_cast<std::int8_t>(slot.index());
   set_equipment.slot      = net::Slot{item.item_id, static_cast<std::int8_t>(item.count), {}};

   auto entity = m_entity_system.entity(entity_id);
   if (not entity.has_component<entity::component::Location>())
      return;

   this->send_raw_to_players_in_view_distance_except(
           player_id, entity.component<entity::component::Location>().position(), set_equipment);
}

void Dispatcher::set_health_and_food(game::PlayerId player_id, float health, int food, float food_saturation)
{
   net::play::cb::SetHealth set_health;
   set_health.health          = health;
   set_health.food            = food;
   set_health.food_saturation = food_saturation;
   this->send_raw_to_player(player_id, set_health);
}

void Dispatcher::spawn_entity(game::EntityId entity_id)
{
   auto entity = m_entity_system.entity(entity_id);
   assert(entity.has_component<LocationComponent>());

   auto position = entity.component<LocationComponent>().position();

   if (entity.has_component<PlayerComponent>()) {
      auto player_id = entity.component<PlayerComponent>().id();

      game::NetworkPlayer net_player{};
      entity.serialize_to_net_player(&net_player);

      this->send_raw_to_players_in_view_distance_except(player_id, position, net_player.player_data);
      this->send_raw_to_players_in_view_distance_except(player_id, position, net_player.metadata);

      for (auto &equipment : net_player.equipment) {
         equipment.entity_id = net_player.player_data.entity_id;
         this->send_raw_to_players_in_view_distance_except(player_id, position, equipment);
      }
   } else {
      game::NetworkEntity net_entity{};
      entity.serialize_to_net(&net_entity);

      this->send_raw_to_players_in_view_distance(position, net_entity.entity_data);
      this->send_raw_to_players_in_view_distance(position, net_entity.metadata);

      for (auto &equipment : net_entity.equipment) {
         equipment.entity_id = net_entity.entity_data.entity_id;
         this->send_raw_to_players_in_view_distance(position, equipment);
      }
   }
}

void Dispatcher::collect_item(game::EntityId collected_entity, game::EntityId collector_entity,
                              const math::Vector3 &position, int count)
{
   net::play::cb::PickupItem pickup_item;
   pickup_item.collected_entity_id = collected_entity;
   pickup_item.collector_entity_id = collector_entity;
   pickup_item.count               = count;
   this->send_raw_to_players_in_view_distance(position, pickup_item);
}

void Dispatcher::remove_entity(game::EntityId entity_id)
{
   auto entity = m_entity_system.entity(entity_id);
   if (not entity.has_component<entity::component::Location>())
      return;

   net::play::cb::RemoveEntities remove_entities;
   remove_entities.entity_ids.push_back(entity_id);

   if (entity.has_component<entity::component::Player>()) {
      this->send_raw_to_players_in_view_distance_except(
              entity.component<entity::component::Player>().id(),
              entity.component<entity::component::Location>().position(), remove_entities);
   } else {
      this->send_raw_to_players_in_view_distance(entity.component<entity::component::Location>().position(),
                                                 remove_entities);
   }
}

void Dispatcher::set_entity_velocity(game::EntityId entity_id, const math::Vector3 &position,
                                     const math::Vector3s &velocity)
{
   net::play::cb::SetEntityVelocity set_entity_velocity;
   set_entity_velocity.entity_id = entity_id;
   set_entity_velocity.velocity  = velocity;
   this->send_raw_to_players_in_view_distance(position, set_entity_velocity);
}

void Dispatcher::remove_entity_for_player(game::PlayerId player_id, game::EntityId entity_id)
{
   net::play::cb::RemoveEntities remove_entities;
   remove_entities.entity_ids.push_back(entity_id);
   this->send_raw_to_player(player_id, remove_entities);
}

void Dispatcher::spawn_entity_for_player(game::PlayerId player_id, game::EntityId entity_id)
{
   auto entity = m_entity_system.entity(entity_id);

   if (entity.has_component<PlayerComponent>()) {
      // don't spawn yourself
      auto entity_player_id = entity.component<PlayerComponent>().id();
      if (entity_player_id == player_id)
         return;

      game::NetworkPlayer net_player;
      entity.serialize_to_net_player(&net_player);

      this->send_raw_to_player(player_id, net_player.player_data);
      this->send_raw_to_player(player_id, net_player.metadata);

      for (auto &equipment : net_player.equipment) {
         equipment.entity_id = net_player.player_data.entity_id;
         this->send_raw_to_player(player_id, equipment);
      }
   } else {
      game::NetworkEntity net_entity;
      entity.serialize_to_net(&net_entity);

      this->send_raw_to_player(player_id, net_entity.entity_data);
      this->send_raw_to_player(player_id, net_entity.metadata);

      for (auto &equipment : net_entity.equipment) {
         equipment.entity_id = net_entity.entity_data.entity_id;
         this->send_raw_to_player(player_id, equipment);
      }
   }
}

void Dispatcher::display_death_screen(game::PlayerId player_id, game::EntityId victim_entity_id,
                                      game::EntityId killer_entity_id, const std::string &message)
{
   net::play::cb::DisplayDeathScreen display_death_screen;
   display_death_screen.victim_entity_id = victim_entity_id;
   display_death_screen.message          = message;
   this->send_raw_to_player(player_id, display_death_screen);
}

void Dispatcher::respawn_player(game::PlayerId player_id)
{
   net::play::cb::Respawn respawn;
   respawn.dimension_codec      = "minecraft:overworld";
   respawn.dimension_name       = "overworld";
   respawn.seed                 = 0x12345;
   respawn.game_mode            = 0;
   respawn.previous_game_mode   = 0;
   respawn.is_debug             = false;
   respawn.is_flat              = false;
   respawn.should_copy_metadata = true;

   this->send_raw_to_player(player_id, respawn);
}

void Dispatcher::teleport_entity(game::EntityId entity_id, const math::Vector3 &position,
                                 const math::Rotation &rotation, bool is_on_ground)
{
   net::play::cb::TeleportEntity teleport_entity;
   teleport_entity.entity_id    = entity_id;
   teleport_entity.position     = position;
   teleport_entity.yaw          = rotation.yaw_degrees();
   teleport_entity.pitch        = rotation.pitch_degrees();
   teleport_entity.is_on_ground = is_on_ground;

   auto entity = m_entity_system.entity(entity_id);
   if (entity.has_component<PlayerComponent>()) {
      this->send_raw_to_player_visible_by(entity, teleport_entity);
   } else {
      this->send_raw_to_players_in_view_distance(position, teleport_entity);
   }
}

void Dispatcher::send_to_all(container::BufferView message) const
{
   m_events.send_to_all(message);
}

void Dispatcher::send_to_player(game::PlayerId player_id, container::BufferView message) const
{
   m_events.send_to(message, player_id);
}

void Dispatcher::send_to_players_visible_by(game::Entity &entity, container::BufferView message) const
{
   assert(entity.has_component<PlayerComponent>());

   const auto &visible_entities = entity.component<PlayerComponent>().visible_entities();

   std::vector<game::PlayerId> players;
   players.reserve(visible_entities.size());

   for (const auto visible_entity_id : visible_entities) {
      if (visible_entity_id == entity.id())
         continue;

      auto visible_entity = m_entity_system.entity(visible_entity_id);
      if (not visible_entity.has_component<PlayerComponent>())
         continue;

      players.emplace_back(visible_entity.component<PlayerComponent>().id());
   }

   m_events.send_to_many(message, players);
}

void Dispatcher::send_to_players_in_view_distance(const math::Vector3 &position,
                                                  container::BufferView message) const
{
   auto entities = m_entity_system.list_entities_in_view_distance(position);
   std::vector<game::PlayerId> players;
   players.reserve(entities.size());
   for (auto entity_id : entities) {
      auto entity = m_entity_system.entity(entity_id);
      if (not entity.has_component<entity::component::Player>())
         continue;

      const auto &player = entity.component<entity::component::Player>();
      players.push_back(player.id());
   }

   m_events.send_to_many(message, players);
}

void Dispatcher::send_to_players_in_view_distance_except(game::PlayerId player_id,
                                                         const math::Vector3 &position,
                                                         container::BufferView message) const
{
   auto entities = m_entity_system.list_entities_in_view_distance(position);
   std::vector<game::PlayerId> players;
   players.reserve(entities.size());
   for (auto entity_id : entities) {
      auto entity = m_entity_system.entity(entity_id);
      if (not entity.has_component<entity::component::Player>())
         continue;

      const auto &player = entity.component<entity::component::Player>();
      if (player.id() == player_id)
         continue;

      players.push_back(player.id());
   }

   m_events.send_to_many(message, players);
}

void Dispatcher::set_abilities(game::PlayerId player_id, const game::Abilities &abilities)
{
   net::play::cb::PlayerAbilities player_abilities;
   player_abilities.fly_speed     = abilities.fly_speed;
   player_abilities.field_of_view = abilities.field_of_view;
   player_abilities.flags         = abilities.flags();
   this->send_raw_to_player(player_id, player_abilities);
}

void Dispatcher::send_damage_event(game::EntityId target, int id,
                                   std::optional<game::EntityId> cause_entity_id,
                                   std::optional<game::EntityId> direct_entity_id,
                                   const math::Vector3 &position)
{
   net::play::cb::DamageEvent damage_event;
   damage_event.entity_id        = target;
   damage_event.type_id          = id;
   damage_event.entity_cause_id  = cause_entity_id.has_value() ? (cause_entity_id.value() + 1) : 0;
   damage_event.entity_direct_id = direct_entity_id.has_value() ? (direct_entity_id.value() + 1) : 0;
   damage_event.source_position  = position;

   this->send_raw_to_players_in_view_distance(position, damage_event);
}

}// namespace minecpp::service::engine
