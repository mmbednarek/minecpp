#pragma once

#include "Server.h"

#include "minecpp/game/player/Id.h"
#include "minecpp/nbt/repository/Registry.schema.h"
#include "minecpp/proto/event/clientbound/Clientbound.pb.h"
#include "minecpp/service/engine/Api.h"

#include <string>
#include <vector>

namespace minecpp::service::front {

namespace clientbound_v1 = proto::event::clientbound;

class EventHandler : public engine::IVisitor
{
 public:
   explicit EventHandler(Server &server, nbt::repository::Registry &registry);

   void set_client(engine::Client *client);

   void handle_add_player(const clientbound_v1::AddPlayer &msg, const event::RecipientList &recipient_list);
   void handle_spawn_player(const clientbound_v1::SpawnPlayer &spawn,
                            const event::RecipientList &recipient_list);
   void handle_spawn_entity(const clientbound_v1::SpawnEntity &pos,
                            const event::RecipientList &recipient_list);
   void handle_entity_move(const clientbound_v1::EntityMove &pos, const event::RecipientList &recipient_list);
   void handle_entity_look(const clientbound_v1::EntityLook &pos, const event::RecipientList &recipient_list);
   void handle_chat(const clientbound_v1::Chat &chat_msg, const event::RecipientList &recipient_list);
   void handle_remove_player(const clientbound_v1::RemovePlayer &msg,
                             const event::RecipientList &recipient_list);
   void handle_update_block(const clientbound_v1::UpdateBlock &msg,
                            const event::RecipientList &recipient_list);
   void handle_animate_entity(const clientbound_v1::AnimateEntity &msg,
                              const event::RecipientList &recipient_list);
   void handle_acknowledge_block_change(const clientbound_v1::AcknowledgeBlockChange &msg,
                                        const event::RecipientList &recipient_list);
   void handle_load_terrain(const clientbound_v1::LoadTerrain &msg,
                            const event::RecipientList &recipient_list);
   void handle_unload_chunk(const clientbound_v1::UnloadChunk &msg,
                            const event::RecipientList &recipient_list);
   void handle_accept_player(const clientbound_v1::AcceptPlayer &msg,
                             const event::RecipientList &recipient_list);
   void handle_deny_player(const clientbound_v1::DenyPlayer &msg, const event::RecipientList &recipient_list);
   void handle_player_list(const clientbound_v1::PlayerList &msg, const event::RecipientList &recipient_list);
   void handle_entity_list(const clientbound_v1::EntityList &msg, const event::RecipientList &recipient_list);
   void handle_set_inventory_slot(const clientbound_v1::SetInventorySlot &msg,
                                  const event::RecipientList &recipient_list);
   void handle_update_block_light(const clientbound_v1::UpdateBlockLight &msg,
                                  const event::RecipientList &recipient_list);
   void handle_chunk_data(const clientbound_v1::ChunkData &msg, const event::RecipientList &recipient_list);
   void handle_set_center_chunk(const clientbound_v1::SetCenterChunk &msg,
                                const event::RecipientList &recipient_list);
   void handle_player_position_rotation(const clientbound_v1::PlayerPositionRotation &msg,
                                        const event::RecipientList &recipient_list);
   void handle_set_spawn_position(const clientbound_v1::SetSpawnPosition &msg,
                                  const event::RecipientList &recipient_list);
   void handle_set_entity_equipment(const clientbound_v1::SetEntityEquipment &msg,
                                    const event::RecipientList &recipient_list);
   void handle_set_health(const clientbound_v1::SetHealth &msg, const event::RecipientList &recipient_list);
   void handle_collect_item(const clientbound_v1::CollectItem &msg,
                            const event::RecipientList &recipient_list);
   void handle_remove_entity(const clientbound_v1::RemoveEntity &msg,
                             const event::RecipientList &recipient_list);
   void handle_set_entity_velocity(const clientbound_v1::SetEntityVelocity &msg,
                                   const event::RecipientList &recipient_list);
   void handle_display_death_screen(const clientbound_v1::DisplayDeathScreen &msg,
                                    const event::RecipientList &recipient_list);
   void handle_respawn(const clientbound_v1::Respawn &msg, const event::RecipientList &recipient_list);
   void handle_teleport_entity(const clientbound_v1::TeleportEntity &msg,
                               const event::RecipientList &recipient_list);
   void handle_set_abilities(const clientbound_v1::SetAbilities &msg,
                             const event::RecipientList &recipient_list);
   void handle_raw_message(const clientbound_v1::RawMessage &msg, const event::RecipientList &recipient_list);
   void visit_event(const proto::event::clientbound::Event &event) override;

   template<typename T>
   void send_message_to_all_players(const T &msg)
   {
      for (auto &[_, conn] : m_server) {
         if (conn.get() == nullptr)
            continue;
         conn->send_message(msg);
      }
   }

   template<typename T>
   void send_message_to_players(const T &msg, std::span<game::PlayerId> players)
   {
      for (auto player_id : players) {
         auto conn = m_server.connection_by_player_id(player_id);
         if (not conn) {
            spdlog::error("connection {} is null", game::player::format_player_id(player_id));
            continue;
         }

         conn->send_message(msg);
      }
   }

   template<typename T>
   void send_message_excluding(const T &msg, game::PlayerId excluded)
   {
      for (auto &[_, conn] : m_server) {
         if (conn.get() == nullptr)
            continue;
         if (conn->uuid() == excluded)
            continue;
         conn->send_message(msg);
      }
   }

   template<typename T>
   void send_message(const T &msg, const event::RecipientList &recipient_list)
   {
      switch (recipient_list.type) {
      case event::RecipientType::All: send_message_to_all_players(msg); break;
      case event::RecipientType::Some: send_message_to_players(msg, recipient_list.list); break;
      case event::RecipientType::Excluding: send_message_excluding(msg, recipient_list.list.front()); break;
      }
   }

   void send_entity(const event::RecipientList &recipient_list, const proto::entity::Entity &entity);

 private:
   Server &m_server;
   engine::Client *m_client{};
   nbt::repository::Registry &m_registry;
   std::unique_ptr<std::future<bool>> m_player_list{};
};

}// namespace minecpp::service::front
