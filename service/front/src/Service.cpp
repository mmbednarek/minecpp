#include "Service.h"
#include "protocol/Protocol.h"
#include "Server.h"
#include <boost/algorithm/string.hpp>
#include <boost/uuid/name_generator.hpp>
#include <minecpp/game/BlockPosition.h>
#include <minecpp/network/message/Clientbound.h>
#include <minecpp/proto/event/serverbound/Serverbound.pb.h>
#include <minecpp/util/Time.h>
#include <minecpp/util/Uuid.h>
#include <spdlog/spdlog.h>

using google::protobuf::Message;

namespace minecpp::service::front {

namespace serverbound_v1 = proto::event::serverbound;

Service::Service(Config & /*config*/) {}

Service::LoginResponse Service::login_player(std::string &user_name)
{
   // TODO: Encryption authentication etc.
   boost::uuids::name_generator gen(g_player_uuid_namespace);

   return Service::LoginResponse{
           .accepted = true,
           .refusal_reason{},
           .user_name = user_name,
           .id        = gen(user_name),
   };
}

void Service::init_player(const std::shared_ptr<Connection> &conn, uuid id, std::string_view name)
{
   using namespace minecpp::network::message;

   assert(m_client != nullptr);

   conn->set_state(protocol::State::Play);
   conn->set_uuid(id);

   proto::event::serverbound::AcceptPlayer accept_player;
   accept_player.set_challenge_id(0);
   accept_player.set_name(std::string(name));
   this->send(accept_player, id);
}

void Service::on_player_disconnect(uuid /*engine_id*/, game::PlayerId player_id)
{
   assert(m_client != nullptr);

   proto::event::serverbound::RemovePlayer remove_player{};
   this->send(remove_player, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::ClientSettings msg)
{
   assert(this);
   spdlog::info("client {} language: {}", game::player::format_player_id(player_id), msg.lang);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::PlayerPosition msg)
{
   serverbound_v1::SetPlayerPosition player_position;
   player_position.mutable_position()->set_x(msg.x);
   player_position.mutable_position()->set_y(msg.y);
   player_position.mutable_position()->set_z(msg.z);
   player_position.set_is_on_ground(msg.on_ground);
   this->send(player_position, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::PlayerPositionRotation msg)
{
   serverbound_v1::SetPlayerPositionRotation player_position_rotation;
   player_position_rotation.mutable_position()->set_x(msg.x);
   player_position_rotation.mutable_position()->set_y(msg.y);
   player_position_rotation.mutable_position()->set_z(msg.z);
   player_position_rotation.mutable_rotation()->set_yaw(msg.yaw);
   player_position_rotation.mutable_rotation()->set_pitch(msg.pitch);
   player_position_rotation.set_is_on_ground(msg.on_ground);
   this->send(player_position_rotation, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::PlayerRotation msg)
{
   serverbound_v1::SetPlayerRotation player_rotation;
   player_rotation.mutable_rotation()->set_yaw(msg.yaw);
   player_rotation.mutable_rotation()->set_pitch(msg.pitch);
   this->send(player_rotation, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::PlayerOnGround msg)
{
   serverbound_v1::SetPlayerOnGround player_on_ground;
   player_on_ground.set_is_on_ground(msg.is_on_ground);
   this->send(player_on_ground, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::Interact msg)
{
   serverbound_v1::Interact interact;
   interact.set_entity_id(static_cast<mb::u32>(msg.entity_id));
   interact.mutable_position()->set_x(msg.x);
   interact.mutable_position()->set_y(msg.y);
   interact.mutable_position()->set_z(msg.z);
   interact.set_is_sneaking(msg.is_sneaking);
   interact.set_interaction_type(static_cast<proto::common::InteractionType>(msg.type));
   interact.set_hand_type(static_cast<proto::common::HandType>(msg.hand));
   this->send(interact, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::ChatMessage msg)
{
   serverbound_v1::ChatMessage chat_message;
   chat_message.set_message(msg.message);
   this->send(chat_message, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::PlayerDigging msg)
{
   serverbound_v1::PlayerDigging player_digging;
   player_digging.set_state(static_cast<proto::common::PlayerDiggingState>(msg.action));
   *player_digging.mutable_block_position() = game::BlockPosition(msg.position).to_proto();
   player_digging.set_face(msg.facing.to_proto());
   this->send(player_digging, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::KeepAliveClient msg)
{
   serverbound_v1::UpdatePing update_ping;
   update_ping.set_ping(static_cast<int>(static_cast<std::uint64_t>(minecpp::util::now_milis()) - msg.time));
   this->send(update_ping, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::AnimateHandClient msg)
{
   serverbound_v1::AnimateHand animate_hand;
   animate_hand.set_hand(static_cast<int>(msg.hand));
   this->send(animate_hand, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::PlayerBlockPlacement msg)
{
   serverbound_v1::BlockPlacement block_placement;
   block_placement.set_hand(static_cast<int32_t>(msg.hand));
   *block_placement.mutable_position() = game::BlockPosition(msg.position).to_proto();
   block_placement.set_face(msg.facing.to_proto());
   block_placement.mutable_crosshair()->set_x(msg.x);
   block_placement.mutable_crosshair()->set_y(msg.y);
   block_placement.mutable_crosshair()->set_z(msg.z);
   block_placement.set_inside_block(msg.inside_block);
   block_placement.set_sequence_id(msg.sequence_id);
   this->send(block_placement, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         const minecpp::network::message::ClickWindow &msg)
{
   if (msg.window_id != 0)
      return;

   if (msg.slot == -999 && msg.mode == 0) {
      serverbound_v1::DropInventoryItem drop_item;
      drop_item.set_full_stack(msg.button == 0);
      this->send(drop_item, player_id);
      return;
   }

   for (const auto &slot : msg.slots) {
      serverbound_v1::ChangeInventoryItem change_item;
      change_item.mutable_item_id()->set_id(static_cast<uint32_t>(slot.item_id));
      change_item.set_slot_id(slot.slot_id);
      change_item.set_item_count(slot.count);
      this->send(change_item, player_id);
   }

   serverbound_v1::SetCarriedItem carried_item;
   carried_item.mutable_carried_item_id()->set_id(static_cast<std::uint32_t>(msg.carried_item_id));
   carried_item.set_carried_item_count(msg.carried_count);
   this->send(carried_item, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::HeldItemChange msg)
{
   serverbound_v1::ChangeHeldItem held_item;
   held_item.set_slot(msg.slot);
   this->send(held_item, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId /*player_id*/,
                         minecpp::network::message::PluginMessage msg)
{
   assert(this);
   spdlog::info("received plugin message channel={}, data={}", msg.channel, msg.data);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         const minecpp::network::message::ChatCommand &msg)
{
   serverbound_v1::IssueCommand command;
   command.set_command(msg.command);
   this->send(command, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id, minecpp::network::message::UseItem msg)
{
   serverbound_v1::UseItem use_item;
   use_item.set_hand(static_cast<int32_t>(msg.hand));
   use_item.set_sequence_id(msg.sequence_id);
   this->send(use_item, player_id);
}

void Service::on_message(uuid /*engine_id*/, game::PlayerId player_id,
                         minecpp::network::message::ClientCommand msg)
{
   if (msg.action_id == 0) {
      serverbound_v1::RequestRespawn request_respawn;
      this->send(request_respawn, player_id);
   }
}

void Service::send(const google::protobuf::Message &message, game::PlayerId id)
{
   if (m_client == nullptr)
      throw std::runtime_error("no available engine connection");

   m_client->send(message, id);
}

void Service::set_client(engine::Client *client)
{
   m_client = client;
}

const char command_list[]{
        0x11, 0x14, 0x00, 0x09, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x05, 0x01, 0x0a, 0x04,
        0x68, 0x65, 0x6c, 0x70, 0x05, 0x01, 0x0b, 0x04, 0x6c, 0x69, 0x73, 0x74, 0x01, 0x01, 0x0c, 0x02, 0x6d,
        0x65, 0x01, 0x01, 0x0d, 0x03, 0x6d, 0x73, 0x67, 0x01, 0x01, 0x0e, 0x07, 0x74, 0x65, 0x61, 0x6d, 0x6d,
        0x73, 0x67, 0x09, 0x00, 0x04, 0x04, 0x74, 0x65, 0x6c, 0x6c, 0x09, 0x00, 0x05, 0x02, 0x74, 0x6d, 0x01,
        0x01, 0x0f, 0x07, 0x74, 0x72, 0x69, 0x67, 0x67, 0x65, 0x72, 0x09, 0x00, 0x04, 0x01, 0x77, 0x06, 0x00,
        0x07, 0x63, 0x6f, 0x6d, 0x6d, 0x61, 0x6e, 0x64, 0x10, 0x62, 0x72, 0x69, 0x67, 0x61, 0x64, 0x69, 0x65,
        0x72, 0x3a, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x02, 0x05, 0x00, 0x05, 0x75, 0x75, 0x69, 0x64, 0x73,
        0x06, 0x00, 0x06, 0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x10, 0x62, 0x72, 0x69, 0x67, 0x61, 0x64, 0x69,
        0x65, 0x72, 0x3a, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x02, 0x02, 0x01, 0x10, 0x07, 0x74, 0x61, 0x72,
        0x67, 0x65, 0x74, 0x73, 0x10, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x65, 0x6e,
        0x74, 0x69, 0x74, 0x79, 0x02, 0x06, 0x00, 0x07, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x11, 0x6d,
        0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x16,
        0x02, 0x11, 0x12, 0x09, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x13, 0x6d, 0x69, 0x6e,
        0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x14,
        0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x61, 0x73, 0x6b, 0x5f, 0x73, 0x65, 0x72,
        0x76, 0x65, 0x72, 0x06, 0x00, 0x07, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x11, 0x6d, 0x69, 0x6e,
        0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x01, 0x01, 0x13,
        0x03, 0x61, 0x64, 0x64, 0x01, 0x01, 0x13, 0x03, 0x73, 0x65, 0x74, 0x06, 0x00, 0x05, 0x76, 0x61, 0x6c,
        0x75, 0x65, 0x11, 0x62, 0x72, 0x69, 0x67, 0x61, 0x64, 0x69, 0x65, 0x72, 0x3a, 0x69, 0x6e, 0x74, 0x65,
        0x67, 0x65, 0x72, 0x00, 0x00};

minecpp::network::message::Raw get_command_list()
{
   return minecpp::network::message::Raw{
           .size = sizeof(command_list),
           .data = command_list,
   };
}

}// namespace minecpp::service::front
