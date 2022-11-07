#include "ApiHandler.h"
#include "EventHandler.h"
#include "EventManager.h"
#include <minecpp/event/Serverbound.h>
#include <spdlog/spdlog.h>

using minecpp::proto::event::clientbound::v1::Event;

namespace minecpp::service::engine {

Connection::Connection(EventHandler &event_handler, BidiStream stream) :
    m_event_handler{event_handler},
    m_stream{std::move(stream)}
{
   m_stream.bind_read_callback(this, &Connection::on_read);
}

void Connection::on_read(const proto::event::serverbound::v1::Event &event)
{
   try {
      event::visit_serverbound(event, m_event_handler);
   } catch (std::runtime_error &err) {
      spdlog::error("error while handling request: {}", err.what());
   }
}

void Connection::send_to_player(const google::protobuf::Message &message, game::PlayerId player_id)
{
   Event proto_event;
   *proto_event.mutable_single_player()->mutable_player_id() = game::player::write_id_to_proto(player_id);
   proto_event.mutable_payload()->PackFrom(message);
   m_stream.write(proto_event);
}

void Connection::send_to_all(const google::protobuf::Message &message)
{
   Event proto_event;
   *proto_event.mutable_all_players() = proto::event::clientbound::v1::RecipientAllPlayers();
   proto_event.mutable_payload()->PackFrom(message);
   m_stream.write(proto_event);
}

ApiHandler::ApiHandler(EventHandler &event_handler, EventManager &event_manager, const std::string &address) :
    m_event_handler{event_handler},
    m_event_manager{event_manager},
    m_server{address, this, &ApiHandler::on_connected, 8}
{
}

void ApiHandler::on_connected(BidiStream stream)
{
   spdlog::info("received connection from front");
   m_event_manager.add_client(std::make_unique<Connection>(m_event_handler, std::move(stream)));
}

mb::emptyres ApiHandler::wait()
{
   m_server.accept();
   return m_server.wait();
}

}// namespace minecpp::service::engine