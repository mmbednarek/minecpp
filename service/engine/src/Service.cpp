#include "Service.h"

#include "service/PlayerInteraction.h"
#include "service/PlayerInterface.h"
#include "service/PlayerMovement.h"
#include "service/PlayerSession.h"

#include "minecpp/game/BlockPosition.h"
#include "minecpp/game/property/Face.h"
#include "minecpp/net/play/Serverbound.schema.h"
#include "minecpp/util/Time.h"

#include <boost/uuid/name_generator.hpp>
#include <spdlog/spdlog.h>

using google::protobuf::Message;

namespace minecpp::service::engine {

Service::Service(service::PlayerInteraction &interaction_service, service::PlayerInterface &interface_service,
                 service::PlayerMovement &movement_service, service::PlayerSession &session_service) :
    m_interaction_service(interaction_service),
    m_interface_service(interface_service),
    m_movement_service(movement_service),
    m_session_service(session_service)
{
}

void Service::handle_raw_message(game::PlayerId player_id, container::BufferView data)
{
   auto stream = data.make_stream();
   network::message::Reader reader(stream);
   net::play::sb::visit_message(*this, player_id, reader);
}

void Service::on_accept_player(game::PlayerId player_id, std::string_view name)
{
   m_session_service.handle_accept_player(player_id, name);
}

void Service::on_remove_player(game::PlayerId player_id)
{
   m_session_service.handle_remove_player(player_id);
}

void Service::on_pre_initial_chunks(game::PlayerId player_id)
{
   m_session_service.handle_pre_initial_chunks(player_id);
}

void Service::on_post_initial_chunks(game::PlayerId player_id)
{
   m_session_service.handle_post_initial_chunks(player_id);
}

void Service::on_chat_command(game::PlayerId player_id, const net::play::sb::ChatCommand &msg)
{
   m_interface_service.handle_issue_command(player_id, msg.command);
}

void Service::on_chat_message(game::PlayerId player_id, const net::play::sb::ChatMessage &msg)
{
   m_interface_service.handle_chat_message(player_id, msg.message);
}

void Service::on_client_settings(game::PlayerId player_id, const net::play::sb::ClientSettings &msg)
{
   static_cast<void>(this);
   spdlog::info("service: client {} language: {}", game::player::format_player_id(player_id), msg.locale);
}

void Service::on_interact(game::PlayerId player_id, const net::play::sb::Interact &msg)
{
   m_interaction_service.handle_interact(player_id, msg.entity_id,
                                         static_cast<game::InteractionTypeValue>(msg.type),
                                         msg.target.has_value() ? msg.target->position : math::Vector3f{},
                                         !msg.target.has_value() && (msg.target->hand == 1));
}

void Service::on_set_player_position(game::PlayerId player_id, const net::play::sb::SetPlayerPosition &msg)
{
   m_movement_service.handle_set_player_position(player_id, msg.position, msg.is_on_ground);
}

void Service::on_set_player_position_and_rotation(game::PlayerId player_id,
                                                  const net::play::sb::SetPlayerPositionAndRotation &msg)
{
   m_movement_service.handle_set_player_position(player_id, msg.position, msg.is_on_ground);
   m_movement_service.handle_set_player_rotation(player_id, math::Rotation::from_degrees(msg.yaw, msg.pitch));
}

void Service::on_set_player_rotation(game::PlayerId player_id, const net::play::sb::SetPlayerRotation &msg)
{
   m_movement_service.handle_set_player_rotation(player_id, math::Rotation::from_degrees(msg.yaw, msg.pitch));
   m_movement_service.handle_set_player_is_on_ground(player_id, msg.is_on_ground);
}

void Service::on_set_is_player_on_ground(game::PlayerId player_id,
                                         const net::play::sb::SetIsPlayerOnGround &msg)
{
   m_movement_service.handle_set_player_is_on_ground(player_id, msg.is_on_ground);
}

void Service::on_player_digging(game::PlayerId player_id, const net::play::sb::PlayerDigging &msg)
{
   auto operation = static_cast<game::ItemOperation>(msg.state);

   switch (operation) {
   case game::ItemOperation::Digging:
      m_interaction_service.handle_start_digging(player_id, msg.sequence_id,
                                                 game::BlockPosition(msg.position));
      break;
   case game::ItemOperation::CanceledDigging:
      m_interaction_service.handle_cancel_digging(player_id, msg.sequence_id,
                                                  game::BlockPosition(msg.position));
      break;
   case game::ItemOperation::FinishedDigging:
      m_interaction_service.handle_finish_digging(player_id, msg.sequence_id,
                                                  game::BlockPosition(msg.position));
      break;
   case game::ItemOperation::DropAllItems:
      m_interaction_service.handle_drop_active_item(player_id, true);
      break;
   case game::ItemOperation::DropItem: m_interaction_service.handle_drop_active_item(player_id, false); break;
   case game::ItemOperation::ReleaseUseItem: m_interaction_service.handle_release_used_item(player_id); break;
   case game::ItemOperation::SwapHeldItems: m_interaction_service.handle_swap_held_items(player_id); break;
   }
}

void Service::on_keep_alive(game::PlayerId player_id, const net::play::sb::KeepAlive &msg)
{
   m_session_service.handle_update_ping(
           player_id, static_cast<int>(static_cast<std::uint64_t>(minecpp::util::now_milis()) - msg.time));
}

void Service::on_animate_hand(game::PlayerId player_id, const net::play::sb::AnimateHand &msg)
{
   m_interaction_service.handle_animate_hand(player_id, static_cast<game::EntityAnimationValue>(msg.hand));
}

void Service::on_use_item_on(game::PlayerId player_id, const net::play::sb::UseItemOn &msg)
{
   m_interaction_service.handle_use_item_on(player_id, msg.sequence_id,
                                            static_cast<game::FaceValue>(msg.facing),
                                            game::BlockPosition(msg.position), msg.cursor_position);
}

void Service::on_click_window(game::PlayerId player_id, const net::play::sb::ClickWindow &msg)
{
   if (msg.window_id != 0)
      return;

   if (msg.clicked_slot == -999 && msg.mode == 0) {
      m_interface_service.handle_drop_carried_item(player_id, msg.button == 0);
      return;
   }

   for (const auto &[slot_id, slot] : msg.slots) {
      game::ItemSlot item_slot{};
      if (slot.has_value()) {
         item_slot.item_id = slot->item_id;
         item_slot.count   = static_cast<unsigned char>(slot->item_count);
      }
      m_interface_service.handle_change_inventory_item(player_id, slot_id, item_slot);
   }

   game::ItemSlot item_slot{};
   if (msg.carried_item.has_value()) {
      item_slot.item_id = msg.carried_item->item_id;
      item_slot.count   = static_cast<unsigned char>(msg.carried_item->item_id);
   }

   m_interface_service.handle_set_carried_item(player_id, item_slot);
}

void Service::on_set_held_item(game::PlayerId player_id, const net::play::sb::SetHeldItem &msg)
{
   m_interface_service.handle_change_held_item(player_id, msg.slot_id);
}

void Service::on_plugin_message(game::PlayerId /*player_id*/, const net::play::sb::PluginMessage &msg)
{
   static_cast<void>(this);
   spdlog::info("received plugin message channel={}, data={}", msg.channel, msg.data);
}

void Service::on_use_item(game::PlayerId player_id, const net::play::sb::UseItem &msg)
{
   m_interaction_service.handle_use_item(player_id, msg.sequence_id, msg.hand);
}

void Service::on_client_command(game::PlayerId player_id, const net::play::sb::ClientCommand &msg)
{
   if (msg.action_id == 0) {
      m_session_service.handle_request_respawn(player_id);
   }
}

void Service::on_confirm_teleport(game::PlayerId player_id, const net::play::sb::ConfirmTeleport &msg)
{
   static_cast<void>(this);
   spdlog::info("play-handler: player {} confirmed teleport {}", boost::uuids::to_string(player_id),
                msg.teleport_id);
}

void Service::on_player_command(game::PlayerId player_id, const net::play::sb::PlayerCommand &msg)
{
   static_cast<void>(this);
   spdlog::info("play-handler: player {} has committed action {}", boost::uuids::to_string(player_id),
                msg.action_id);
}

void Service::on_close_window(game::PlayerId player_id, const net::play::sb::CloseWindow &msg)
{
   static_cast<void>(this);
   spdlog::info("play-handler: player {} closed window {}", boost::uuids::to_string(player_id),
                msg.window_id);
}

void Service::on_failure(game::PlayerId player_id, std::uint8_t message_id)
{
   spdlog::warn("service: unknown op {} received from player {}", message_id,
                boost::uuids::to_string(player_id));
}

}// namespace minecpp::service::engine
