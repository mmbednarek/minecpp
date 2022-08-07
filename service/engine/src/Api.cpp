#include "Api.h"
#include "EventHandler.h"
#include <minecpp/event/Serverbound.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

ApiHandler::ApiHandler(EventHandler &event_handler, EventManager<BidiStream> &event_manager) :
    m_event_handler(event_handler),
    m_event_manager(event_manager)
{
}

void ApiHandler::on_connected(BidiStream stream)
{
   const auto tag = "front";
   stream.set_tag(tag);
   stream.read();
   m_event_manager.add_client(stream);
   spdlog::info("front connection");
}

void ApiHandler::on_finish_read(BidiStream stream, const proto::event::serverbound::v1::Event &event)
{
   stream.read();
   try {
      event::visit_serverbound(event, m_event_handler);
   } catch (std::runtime_error &err) {
      spdlog::error("visit error: {}", err.what());
   }

   spdlog::info("on finish read");
}

void ApiHandler::on_finish_write(BidiStream stream)
{
   auto client = m_event_manager.client(stream.tag());
   if (client == nullptr)
      return;

   if (client->queue.empty()) {
      client->mutex.unlock();
      return;
   }
   stream.write(client->queue.pop());

   spdlog::info("on finish write");
}

}// namespace minecpp::service::engine