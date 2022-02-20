#include "api.h"
#include "event_handler.h"
#include <minecpp/event/serverbound.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

ApiHandler::ApiHandler(EventHandler &event_handler, EventManager<BidiStream> &event_manager) : m_event_handler(event_handler), m_event_manager(event_manager) {}

void ApiHandler::on_connected(BidiStream stream) {
   const auto tag = "front";
   stream.set_tag(tag);
   stream.read();
   m_event_manager.add_client(stream);
   spdlog::info("api handler: front connection");
}

void ApiHandler::on_finish_read(BidiStream stream, const proto::event::serverbound::v1::Event &event) {
   spdlog::info("api handler: received message");
   stream.read();
   try {
      event::visit_serverbound(event, m_event_handler);
   } catch (std::runtime_error &err) {
      spdlog::error("visit error: {}", err.what());
   }
}

void ApiHandler::on_finish_write(BidiStream stream) {
//   spdlog::info("api handler: wrote message");
   auto client = m_event_manager.client(stream.tag());
   if (client == nullptr) {
      return;
   }

   std::unique_lock<std::mutex> lock(client->mutex);
   --client->writing_count;

   if (client->queue.empty()) {
      client->writing = false;
      spdlog::info("setting writing to false, counting: {}", client->writing_count);
      return;
   }
   ++client->writing_count;
   auto msg = client->queue.pop();
   spdlog::info("writing next message, size: {}", msg.ByteSizeLong());
   stream.write(msg);
}

}// namespace minecpp::service::engine