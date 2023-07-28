#include "Service.h"

#include "EventHandler.h"

#include "minecpp/event/Serverbound.h"
#include "minecpp/game/BlockPosition.h"
#include "minecpp/game/property/Face.h"
#include "minecpp/net/play/Serverbound.schema.h"
#include "minecpp/proto/event/serverbound/Serverbound.pb.h"
#include "minecpp/util/Time.h"

#include <boost/uuid/name_generator.hpp>
#include <spdlog/spdlog.h>

using google::protobuf::Message;

namespace minecpp::service::engine {

namespace serverbound_v1 = proto::event::serverbound;

Service::Service(EventHandler &handler) :
    m_event_handler{handler}
{
}

void Service::handle_raw_message(game::PlayerId player_id, container::BufferView data)
{
   auto stream = data.make_stream();
   network::message::Reader reader(stream);
   net::play::sb::visit_message(*this, player_id, reader);
}

void Service::send(const google::protobuf::Message &message, game::PlayerId id)
{
   proto::event::serverbound::Event proto_event;
   proto_event.mutable_payload()->PackFrom(message);
   *proto_event.mutable_player_id() = game::player::write_id_to_proto(id);
   event::visit_serverbound(proto_event, m_event_handler);
}

void Service::on_chat_command(game::PlayerId player_id, const net::play::sb::ChatCommand &msg)
{
   serverbound_v1::IssueCommand command;
   command.set_command(msg.command);
   this->send(command, player_id);
}

void Service::on_chat_message(game::PlayerId player_id, const net::play::sb::ChatMessage &msg)
{
   serverbound_v1::ChatMessage chat_message;
   chat_message.set_message(msg.message);
   this->send(chat_message, player_id);
}

void Service::on_client_settings(game::PlayerId player_id, const net::play::sb::ClientSettings &msg)
{
   static_cast<void>(this);
   spdlog::info("service: client {} language: {}", game::player::format_player_id(player_id), msg.locale);
}

void Service::on_interact(game::PlayerId player_id, const net::play::sb::Interact &msg)
{
   serverbound_v1::Interact interact{};
   interact.set_entity_id(static_cast<mb::u32>(msg.entity_id));
   if (msg.target.has_value()) {
      interact.mutable_position()->set_x(msg.target->position.x);
      interact.mutable_position()->set_y(msg.target->position.y);
      interact.mutable_position()->set_z(msg.target->position.z);
      interact.set_hand_type(static_cast<proto::common::HandType>(msg.target.has_value()));
   }
   interact.set_is_sneaking(msg.is_sneaking);
   interact.set_interaction_type(static_cast<proto::common::InteractionType>(msg.type));
   this->send(interact, player_id);
}

void Service::on_set_player_position(game::PlayerId player_id, const net::play::sb::SetPlayerPosition &msg)
{
   serverbound_v1::SetPlayerPosition player_position;
   player_position.mutable_position()->set_x(msg.position.x);
   player_position.mutable_position()->set_y(msg.position.y);
   player_position.mutable_position()->set_z(msg.position.z);
   player_position.set_is_on_ground(msg.is_on_ground);
   this->send(player_position, player_id);
}

void Service::on_set_player_position_and_rotation(game::PlayerId player_id,
                                                  const net::play::sb::SetPlayerPositionAndRotation &msg)
{
   serverbound_v1::SetPlayerPositionRotation player_position_rotation;
   player_position_rotation.mutable_position()->set_x(msg.position.x);
   player_position_rotation.mutable_position()->set_y(msg.position.y);
   player_position_rotation.mutable_position()->set_z(msg.position.z);
   player_position_rotation.mutable_rotation()->set_yaw(msg.yaw);
   player_position_rotation.mutable_rotation()->set_pitch(msg.pitch);
   player_position_rotation.set_is_on_ground(msg.is_on_ground);
   this->send(player_position_rotation, player_id);
}

void Service::on_set_player_rotation(game::PlayerId player_id, const net::play::sb::SetPlayerRotation &msg)
{
   serverbound_v1::SetPlayerRotation player_rotation;
   player_rotation.mutable_rotation()->set_yaw(msg.yaw);
   player_rotation.mutable_rotation()->set_pitch(msg.pitch);
   player_rotation.set_is_on_ground(msg.is_on_ground);
   this->send(player_rotation, player_id);
}

void Service::on_set_is_player_on_ground(game::PlayerId player_id,
                                         const net::play::sb::SetIsPlayerOnGround &msg)
{
   serverbound_v1::SetPlayerOnGround player_on_ground;
   player_on_ground.set_is_on_ground(msg.is_on_ground);
   this->send(player_on_ground, player_id);
}

void Service::on_player_digging(game::PlayerId player_id, const net::play::sb::PlayerDigging &msg)
{
   serverbound_v1::PlayerDigging player_digging;
   player_digging.set_state(static_cast<proto::common::PlayerDiggingState>(msg.state));
   *player_digging.mutable_block_position() = game::BlockPosition(msg.position).to_proto();
   player_digging.set_face(game::Face(static_cast<game::FaceValue>(msg.facing)).to_proto());
   this->send(player_digging, player_id);
}

void Service::on_keep_alive(game::PlayerId player_id, const net::play::sb::KeepAlive &msg)
{
   serverbound_v1::UpdatePing update_ping;
   update_ping.set_ping(static_cast<int>(static_cast<std::uint64_t>(minecpp::util::now_milis()) - msg.time));
   this->send(update_ping, player_id);
}

void Service::on_animate_hand(game::PlayerId player_id, const net::play::sb::AnimateHand &msg)
{
   serverbound_v1::AnimateHand animate_hand;
   animate_hand.set_hand(static_cast<int>(msg.hand));
   this->send(animate_hand, player_id);
}

void Service::on_use_item_on(game::PlayerId player_id, const net::play::sb::UseItemOn &msg)
{
   serverbound_v1::BlockPlacement block_placement;
   block_placement.set_hand(static_cast<int32_t>(msg.hand));
   *block_placement.mutable_position() = game::BlockPosition(msg.position).to_proto();
   block_placement.set_face(game::Face(static_cast<game::FaceValue>(msg.facing)).to_proto());
   block_placement.mutable_crosshair()->set_x(msg.cursor_position.x);
   block_placement.mutable_crosshair()->set_y(msg.cursor_position.y);
   block_placement.mutable_crosshair()->set_z(msg.cursor_position.z);
   block_placement.set_inside_block(msg.is_inside_block);
   block_placement.set_sequence_id(msg.sequence_id);
   this->send(block_placement, player_id);
}

void Service::on_click_window(game::PlayerId player_id, const net::play::sb::ClickWindow &msg)
{
   if (msg.window_id != 0)
      return;

   if (msg.clicked_slot == -999 && msg.mode == 0) {
      serverbound_v1::DropInventoryItem drop_item;
      drop_item.set_full_stack(msg.button == 0);
      this->send(drop_item, player_id);
      return;
   }

   for (const auto &[slot_id, slot] : msg.slots) {
      serverbound_v1::ChangeInventoryItem change_item;
      if (slot.has_value()) {
         change_item.mutable_item_id()->set_id(static_cast<std::uint32_t>(slot->item_id));
         change_item.set_item_count(slot->item_count);
      } else {
         change_item.set_item_count(0);
      }
      change_item.set_slot_id(slot_id);
      this->send(change_item, player_id);
   }

   serverbound_v1::SetCarriedItem carried_item;
   if (msg.carried_item.has_value()) {
      carried_item.mutable_carried_item_id()->set_id(static_cast<std::uint32_t>(msg.carried_item->item_id));
      carried_item.set_carried_item_count(msg.carried_item->item_count);
   } else {
      carried_item.set_carried_item_count(0);
   }
   this->send(carried_item, player_id);
}

void Service::on_set_held_item(game::PlayerId player_id, const net::play::sb::SetHeldItem &msg)
{
   serverbound_v1::ChangeHeldItem held_item;
   held_item.set_slot(msg.slot_id);
   this->send(held_item, player_id);
}

void Service::on_plugin_message(game::PlayerId /*player_id*/, const net::play::sb::PluginMessage &msg)
{
   static_cast<void>(this);
   spdlog::info("received plugin message channel={}, data={}", msg.channel, msg.data);
}

void Service::on_use_item(game::PlayerId player_id, const net::play::sb::UseItem &msg)
{
   serverbound_v1::UseItem use_item;
   use_item.set_hand(static_cast<int32_t>(msg.hand));
   use_item.set_sequence_id(msg.sequence_id);
   this->send(use_item, player_id);
}

void Service::on_client_command(game::PlayerId player_id, const net::play::sb::ClientCommand &msg)
{
   if (msg.action_id == 0) {
      serverbound_v1::RequestRespawn request_respawn;
      this->send(request_respawn, player_id);
   }
}

void Service::on_failure(game::PlayerId player_id, std::uint8_t message_id)
{
   spdlog::warn("play-handler: unknown op {} received from player {}", message_id,
                boost::uuids::to_string(player_id));
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

}// namespace minecpp::service::engine
