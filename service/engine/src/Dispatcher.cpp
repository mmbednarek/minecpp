#include "Dispatcher.h"

#include "ChunkSystem.h"
#include "EventManager.h"

#include "minecpp/chat/Chat.h"
#include "minecpp/entity/Aliases.hpp"
#include "minecpp/entity/component/Abilities.h"
#include "minecpp/entity/component/Location.h"
#include "minecpp/entity/component/Player.h"
#include "minecpp/entity/EntitySystem.h"
#include "minecpp/game/ChunkPosition.h"
#include "minecpp/game/ChunkRange.h"
#include "minecpp/game/player/Player.h"
#include "minecpp/net/play/Clientbound.schema.h"
#include "minecpp/proto/event/clientbound/Clientbound.pb.h"
#include "minecpp/util/Uuid.h"
#include "minecpp/world/ChunkSerializer.h"
#include "minecpp/world/SectionSlice.h"

namespace minecpp::service::engine {

namespace clientbound_v1 = proto::event::clientbound;

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

void Dispatcher::spawn_player(game::PlayerId player_id, game::EntityId entity_id,
                              const math::Vector3 &position)
{
   auto entity = m_entity_system.entity(entity_id);

   auto spawn_player = net::play::cb::SpawnPlayer{
           .entity_id = entity_id,
           .player_id = player_id,
           .position  = position,
           .yaw       = entity.component<RotationComponent>().yaw_degrees(),
           .pitch     = entity.component<RotationComponent>().pitch_degrees(),
   };

   this->send_raw_to_players_in_view_distance_except(player_id, position, spawn_player);
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
   clientbound_v1::EntityList list;

   list.mutable_player_entities()->Reserve(static_cast<int>(entities.size()));
   list.mutable_entities()->Reserve(static_cast<int>(entities.size()));

   for (const auto &entity_id : entities) {
      auto entity = m_entity_system.entity(entity_id);
      if (entity.has_component<entity::component::Player>()) {
         if (entity.component<entity::component::Player>().id() == player_id)
            continue;

         entity.serialize_player_to_proto(list.add_player_entities());
      } else {
         entity.serialize_to_proto(list.add_entities());
      }
   }

   m_events.send_to(list, player_id);

   for (const auto entity_id : entities) {
      auto entity = m_entity_system.entity(entity_id);
      if (entity.has_component<entity::component::Player>()) {
         if (entity.component<entity::component::Player>().id() == player_id)
            continue;

         this->send_raw_to_player(player_id,
                                  net::play::cb::SpawnPlayer{
                                          .entity_id = entity_id,
                                          .player_id = entity.component<PlayerComponent>().id(),
                                          .position  = entity.component<LocationComponent>().position(),
                                          .yaw       = entity.component<RotationComponent>().yaw_degrees(),
                                          .pitch     = entity.component<RotationComponent>().pitch_degrees(),
                                  });
      } else {
         this->spawn_entity(entity_id, entity.component<LocationComponent>().position());
      }
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

   spdlog::info("dispatcher: sending chunk {} {}", update_chunk.chunk.position.x(),
                update_chunk.chunk.position.y());
}

void Dispatcher::update_chunk_position(game::PlayerId player_id, const game::ChunkPosition &chunk_position)
{
   clientbound_v1::SetCenterChunk center_chunk;
   *center_chunk.mutable_position() = chunk_position.to_proto();

   m_events.send_to(center_chunk, player_id);
}

void Dispatcher::synchronise_player_position_and_rotation(game::PlayerId player_id, math::Vector3 position,
                                                          math::Rotation rotation)
{
   clientbound_v1::PlayerPositionRotation player_pos_rot;
   *player_pos_rot.mutable_position() = position.to_proto();
   *player_pos_rot.mutable_rotation() = rotation.to_proto();
   m_events.send_to(player_pos_rot, player_id);
}

void Dispatcher::set_spawn_position(game::PlayerId player_id, game::BlockPosition position, float angle)
{
   clientbound_v1::SetSpawnPosition set_spawn;
   set_spawn.set_position(position.as_long());
   set_spawn.set_angle(angle);

   m_events.send_to(set_spawn, player_id);
}

void Dispatcher::set_player_equipment(game::PlayerId player_id, game::EntityId entity_id,
                                      game::EquipmentSlot slot, game::ItemSlot item)
{
   clientbound_v1::SetEntityEquipment equipment;
   equipment.set_entity_id(entity_id);
   equipment.set_equipment_slot(slot.to_proto());
   equipment.mutable_item()->mutable_item_id()->set_id(static_cast<uint32_t>(item.item_id));
   equipment.mutable_item()->set_count(static_cast<uint32_t>(item.count));

   auto entity = m_entity_system.entity(entity_id);
   if (not entity.has_component<entity::component::Location>())
      return;

   this->send_to_players_in_view_distance_except(
           player_id, entity.component<entity::component::Location>().position(), equipment);
}

void Dispatcher::set_health_and_food(game::PlayerId player_id, float health, int food, float food_saturation)
{
   clientbound_v1::SetHealth equipment;
   equipment.set_health(health);
   equipment.set_food(food);
   equipment.set_food_saturation(food_saturation);

   m_events.send_to(equipment, player_id);
}

void Dispatcher::spawn_entity(game::EntityId entity_id, const math::Vector3 &position)
{
   auto entity = m_entity_system.entity(entity_id);

   clientbound_v1::SpawnEntity spawn_entity;
   entity.serialize_to_proto(spawn_entity.mutable_entity());

   this->send_to_players_in_view_distance(position, spawn_entity);
}

void Dispatcher::collect_item(game::EntityId collected_entity, game::EntityId collector_entity,
                              const math::Vector3 &position, int count)
{
   clientbound_v1::CollectItem collect_item;
   collect_item.set_collected_entity_id(collected_entity);
   collect_item.set_collector_entity_id(collector_entity);
   collect_item.set_count(static_cast<std::uint32_t>(count));

   this->send_to_players_in_view_distance(position, collect_item);
}

void Dispatcher::remove_entity(game::EntityId entity_id)
{
   clientbound_v1::RemoveEntity remove_entity;
   remove_entity.set_entity_id(entity_id);

   auto entity = m_entity_system.entity(entity_id);
   if (not entity.has_component<entity::component::Location>())
      return;

   if (entity.has_component<entity::component::Player>()) {
      this->send_to_players_in_view_distance_except(
              entity.component<entity::component::Player>().id(),
              entity.component<entity::component::Location>().position(), remove_entity);
      return;
   }

   this->send_to_players_in_view_distance(entity.component<entity::component::Location>().position(),
                                          remove_entity);
}

void Dispatcher::set_entity_velocity(game::EntityId entity_id, const math::Vector3 &position,
                                     const math::Vector3s &velocity)
{
   clientbound_v1::SetEntityVelocity update_velocity;
   update_velocity.set_entity_id(entity_id);
   *update_velocity.mutable_velocity() = velocity.to_proto();

   this->send_to_players_in_view_distance(position, update_velocity);
}

void Dispatcher::remove_entity_for_player(game::PlayerId player_id, game::EntityId entity_id)
{
   clientbound_v1::RemoveEntity remove_entity;
   remove_entity.set_entity_id(entity_id);
   m_events.send_to(remove_entity, player_id);
}

void Dispatcher::spawn_entity_for_player(game::PlayerId player_id, game::EntityId entity_id)
{
   auto entity = m_entity_system.entity(entity_id);

   clientbound_v1::SpawnEntity spawn_entity;
   entity.serialize_to_proto(spawn_entity.mutable_entity());

   m_events.send_to(spawn_entity, player_id);
}

void Dispatcher::spawn_player_for_player(game::PlayerId receiver, game::PlayerId spawned_player,
                                         game::EntityId entity_id)
{
   auto entity = m_entity_system.entity(entity_id);

   clientbound_v1::SpawnPlayer spawn_player;
   *spawn_player.mutable_player_id() = game::player::write_id_to_proto(spawned_player);
   entity.serialize_player_to_proto(spawn_player.mutable_entity());

   m_events.send_to(spawn_player, receiver);
}

void Dispatcher::display_death_screen(game::PlayerId player_id, game::EntityId victim_entity_id,
                                      game::EntityId killer_entity_id, const std::string &message)
{
   clientbound_v1::DisplayDeathScreen display_death_screen;
   display_death_screen.set_victim_entity_id(victim_entity_id);
   display_death_screen.set_killer_entity_id(killer_entity_id);
   display_death_screen.set_death_message(message);
   m_events.send_to(display_death_screen, player_id);
}

void Dispatcher::respawn_player(game::PlayerId player_id)
{
   clientbound_v1::Respawn respawn;
   respawn.set_dimension_type("minecraft:overworld");
   respawn.set_dimension_name("overworld");
   respawn.set_hashed_seed(0x12345);
   respawn.set_game_mode(proto::common::GameMode::Survival);
   respawn.set_previous_game_mode(proto::common::GameMode::Survival);
   respawn.set_is_debug(false);
   respawn.set_is_flat(false);
   respawn.set_copy_metadata(true);
   respawn.set_has_death_location(false);
   m_events.send_to(respawn, player_id);
}

void Dispatcher::teleport_entity(game::EntityId entity_id, const math::Vector3 &position,
                                 const math::Rotation &rotation, bool is_on_ground)
{
   clientbound_v1::TeleportEntity teleport_entity;
   teleport_entity.set_entity_id(entity_id);
   *teleport_entity.mutable_position() = position.to_proto();
   *teleport_entity.mutable_rotation() = rotation.to_proto();
   teleport_entity.set_is_on_ground(is_on_ground);

   auto entity = m_entity_system.entity(entity_id);
   if (entity.has_component<PlayerComponent>()) {
      this->send_to_players_visible_by(entity, teleport_entity);
   } else {
      this->send_to_players_in_view_distance(position, teleport_entity);
   }
}

void Dispatcher::send_to_all(const google::protobuf::Message &message) const
{
   m_events.send_to_all(message);
}

void Dispatcher::send_to_player(game::PlayerId player_id, const google::protobuf::Message &message) const
{
   m_events.send_to(message, player_id);
}

void Dispatcher::send_to_players_visible_by(game::Entity &entity,
                                            const google::protobuf::Message &message) const
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
                                                  const google::protobuf::Message &message) const
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
                                                         const google::protobuf::Message &message) const
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

clientbound_v1::RawMessage Dispatcher::make_raw_message(const network::message::Writer &writer)
{
   clientbound_v1::RawMessage raw_msg;
   raw_msg.mutable_message_data()->resize(writer.view().size());
   std::copy(writer.view().begin(), writer.view().end(), raw_msg.mutable_message_data()->begin());
   return raw_msg;
}

void Dispatcher::set_abilities(game::PlayerId player_id, const game::Abilities &abilities)
{
   clientbound_v1::SetAbilities set_abilities;
   *set_abilities.mutable_abilities() = abilities.to_proto();
   m_events.send_to(set_abilities, player_id);
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
