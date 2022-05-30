#include "service.h"
#include "protocol/protocol.h"
#include "server.h"
#include <boost/algorithm/string.hpp>
#include <boost/uuid/name_generator.hpp>
#include <fstream>
#include <minecpp/game/game.h>
#include <minecpp/game/player.h>
#include <minecpp/proto/event/serverbound/v1/serverbound.pb.h>
#include <minecpp/util/time.h>
#include <minecpp/util/uuid.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::front {

namespace serverbound_v1 = proto::event::serverbound::v1;

const char *internal_reason =
        R"({"extra":[{"color": "red", "bold": true, "text": "Disconnected"}, {"color":"gray", "text": " INTERNAL ERROR"}], "text": ""})";

Service::Service(Config &conf, ChunkService chunk_service) :
    m_chunk_service(std::move(chunk_service))
{
   std::ifstream recipe_st;
   recipe_st.open(conf.recipe_path);
   if (!recipe_st.is_open()) {
      throw std::runtime_error("could not open recipe file");
   }
   recipe_st.seekg(0, std::ios::end);
   cached_recipes_size = recipe_st.tellg();
   recipe_st.seekg(0, std::ios::beg);
   cached_recipes = new char[cached_recipes_size];
   recipe_st.read(cached_recipes, cached_recipes_size);

   std::ifstream tags_st;
   tags_st.open(conf.tags_path);
   if (!tags_st.is_open()) {
      throw std::runtime_error("could not open recipe file");
   }
   tags_st.seekg(0, std::ios::end);
   cached_tags_size = tags_st.tellg();
   tags_st.seekg(0, std::ios::beg);
   cached_tags = new char[cached_tags_size];
   tags_st.read(cached_tags, cached_tags_size);
}

Service::~Service()
{
   delete[] cached_recipes;
}

Service::LoginResponse Service::login_player(std::string &user_name)
{
   // TODO: Encryption authentication etc.
   boost::uuids::name_generator gen(g_player_uuid_namespace);

   return Service::LoginResponse{
           .accepted  = true,
           .user_name = user_name,
           .id        = gen(user_name),
   };
}

minecpp::network::message::Raw get_command_list();

void Service::init_player(const std::shared_ptr<Connection> &conn, uuid id, std::string_view name)
{
   using namespace minecpp::network::message;

   conn->set_state(Protocol::State::Play);
   conn->set_uuid(id);

   proto::event::serverbound::v1::AcceptPlayer accept_player;
   accept_player.set_challenge_id(0);
   accept_player.set_name(std::string(name));
   m_stream->send(accept_player, id);
}

void Service::on_player_disconnect(uuid engine_id, player::Id player_id)
{
   proto::event::serverbound::v1::RemovePlayer remove_player{};
   m_stream->send(remove_player, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::ClientSettings msg)
{
   spdlog::info("client {} language: {}", player::format_player_id(player_id), msg.lang);
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PlayerPosition msg)
{
   serverbound_v1::SetPlayerPosition player_position;
   player_position.mutable_position()->set_x(msg.x);
   player_position.mutable_position()->set_y(msg.y);
   player_position.mutable_position()->set_z(msg.z);
   m_stream->send(player_position, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id,
                         minecpp::network::message::PlayerPositionRotation msg)
{
   serverbound_v1::SetPlayerPosition player_position;
   player_position.mutable_position()->set_x(msg.x);
   player_position.mutable_position()->set_y(msg.y);
   player_position.mutable_position()->set_z(msg.z);
   m_stream->send(player_position, player_id);

   serverbound_v1::SetPlayerRotation player_rotation;
   player_rotation.mutable_rotation()->set_yaw(msg.yaw);
   player_rotation.mutable_rotation()->set_pitch(msg.pitch);
   m_stream->send(player_rotation, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PlayerRotation msg)
{
   serverbound_v1::SetPlayerRotation player_rotation;
   player_rotation.mutable_rotation()->set_yaw(msg.yaw);
   player_rotation.mutable_rotation()->set_pitch(msg.pitch);
   m_stream->send(player_rotation, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::ChatMessage msg)
{
   serverbound_v1::ChatMessage chat_message;
   chat_message.set_message(msg.message);
   m_stream->send(chat_message, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PlayerDigging msg)
{
   serverbound_v1::PlayerDigging player_digging;
   player_digging.set_state(static_cast<proto::common::v1::PlayerDiggingState>(msg.action));
   *player_digging.mutable_block_position() = game::BlockPosition(msg.position).to_proto();
   player_digging.set_face(static_cast<proto::common::v1::Face>(msg.facing));
   m_stream->send(player_digging, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::KeepAliveClient msg)
{
   serverbound_v1::UpdatePing update_ping;
   update_ping.set_ping(static_cast<int>(minecpp::util::now_milis() - msg.time));
   m_stream->send(update_ping, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id,
                         minecpp::network::message::AnimateHandClient msg)
{
   serverbound_v1::AnimateHand animate_hand;
   animate_hand.set_hand(static_cast<int>(msg.hand));
   m_stream->send(animate_hand, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id,
                         minecpp::network::message::PlayerBlockPlacement msg)
{
   serverbound_v1::BlockPlacement block_placement;
   block_placement.set_hand(static_cast<int32_t>(msg.hand));
   *block_placement.mutable_position() = game::BlockPosition(msg.position).to_proto();
   block_placement.set_face(static_cast<minecpp::proto::common::v1::Face>(msg.facing));
   block_placement.mutable_crosshair()->set_x(msg.x);
   block_placement.mutable_crosshair()->set_y(msg.y);
   block_placement.mutable_crosshair()->set_z(msg.z);
   block_placement.set_inside_block(msg.inside_block);
   m_stream->send(block_placement, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::ClickWindow msg)
{
   if (msg.window_id != 0)
      return;

   for (const auto &slot : msg.slots) {
      serverbound_v1::ChangeInventoryItem change_item;
      change_item.mutable_item_id()->set_id(static_cast<uint32_t>(slot.item_id));
      change_item.set_slot_id(slot.slot_id);
      change_item.set_item_count(slot.count);
      m_stream->send(change_item, player_id);
   }
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::HeldItemChange msg)
{
   serverbound_v1::ChangeHeldItem held_item;
   held_item.set_slot(msg.slot);
   m_stream->send(held_item, player_id);
}

void Service::on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PluginMessage msg)
{
   spdlog::info("received plugin message channel={}, data={}", msg.channel, msg.data);
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
