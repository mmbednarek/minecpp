#include "Server.h"
#include <spdlog/spdlog.h>

namespace minecpp::service::storage {

Connection::Connection(ConnectionId id, Stream stream, IHandler *handler) :
    m_id(id),
    m_stream(std::move(stream)),
    m_handler(handler)
{
   m_stream.bind_read_callback(this, &Connection::on_read);
}

void Connection::send(const storage_v1::Response &response)
{
   m_stream.write(response);
}

void Connection::on_read(const storage_v1::Request &request)
{
   if (m_handler == nullptr) {
      spdlog::error("connection: handler is null");
      return;
   }

   m_handler->handle_request(m_id, request);
}

Server::Server(const std::string &bind_address) :
    m_server(bind_address, this, &Server::on_connection, 1)
{
}

void Server::on_connection(Stream stream)
{
   spdlog::info("received connection");
   std::unique_lock lock{m_mutex};
   m_connections.emplace(m_top_connection_id,
                         std::make_unique<Connection>(m_top_connection_id, std::move(stream), m_handler));
   ++m_top_connection_id;
}

void Server::send(ConnectionId id, const storage_v1::Response &response)
{
   auto it = m_connections.find(id);
   if (it == m_connections.end()) {
      spdlog::error("could not find connection {}", id);
      return;
   }
   it->second->send(response);
}

void Server::wait()
{
   m_server.accept();
   m_server.wait();
}

void Server::set_handler(IHandler *handler)
{
   m_handler = handler;
}

}// namespace minecpp::service::storage
