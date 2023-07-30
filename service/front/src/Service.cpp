#include "Service.h"
#include "protocol/Protocol.h"
#include "Server.h"

#include "minecpp/proto/event/serverbound/Serverbound.pb.h"

#include <boost/uuid/name_generator.hpp>
#include <spdlog/spdlog.h>

using google::protobuf::Message;

namespace minecpp::service::front {

namespace serverbound_v1 = proto::event::serverbound;

Service::Service(Config & /*config*/) {}

Service::LoginResponse Service::login_player(std::string &user_name)
{
   // TODO: authentication
   boost::uuids::name_generator gen(g_player_uuid_namespace);

   return Service::LoginResponse{
           .accepted = true,
           .refusal_reason{},
           .user_name = user_name,
           .id        = gen(user_name),
   };
}

void Service::init_player(Connection &connection, uuid id, std::string_view name)
{
   assert(m_client != nullptr);

   connection.set_state(protocol::State::Play);
   connection.set_uuid(id);

   serverbound_v1::AcceptPlayer accept_player;
   accept_player.set_challenge_id(0);
   accept_player.set_name(std::string(name));
   this->send(accept_player, id);
}

void Service::on_player_disconnect(uuid /*engine_id*/, game::PlayerId player_id)
{
   assert(m_client != nullptr);

   serverbound_v1::RemovePlayer remove_player{};
   this->send(remove_player, player_id);
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

void Service::send_raw_message(game::PlayerId id, container::BufferView data)
{
   serverbound_v1::RawMessage raw_message;
   raw_message.set_data(data.to_string());
   this->send(raw_message, id);
}

}// namespace minecpp::service::front
