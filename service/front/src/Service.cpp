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

   net::engine::sb::AcceptPlayer accept_player;
   accept_player.name = name;
   accept_player.player_id = id;

   network::message::Writer writer;
   accept_player.serialize(writer);
   m_client->send(writer.buffer_view());
}

void Service::on_player_disconnect(uuid /*engine_id*/, game::PlayerId player_id)
{
   assert(m_client != nullptr);

   network::message::Writer writer;
   net::engine::sb::RemovePlayer remove_player;
   remove_player.player_id = player_id;
   remove_player.serialize(writer);
   m_client->send(writer.buffer_view());
}

void Service::send(container::BufferView message, game::PlayerId id)
{
   if (m_client == nullptr)
      throw std::runtime_error("no available engine connection");

   network::message::Writer writer;
   net::engine::sb::PlayerMessage player_message;
   player_message.player_id = id;
   player_message.data.resize(message.size());
   std::copy(message.begin(), message.end(), player_message.data.begin());

   player_message.serialize(writer);
   m_client->send(writer.buffer_view());
}

void Service::set_client(engine::Client *client)
{
   m_client = client;
}

}// namespace minecpp::service::front
