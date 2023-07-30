#include "PlayHandler.h"
#include "../Connection.h"
#include "../Service.h"

namespace minecpp::service::front::protocol {

PlayHandler::PlayHandler(Service &service) :
    service(service)
{
}

void PlayHandler::handle(Connection &connection, Reader &reader)
{
   connection.async_read_packet(*this);
   auto buffer = container::Buffer::from_istream(reader.raw_stream());
   service.send_raw_message(connection.uuid(), buffer.as_view());
}

void PlayHandler::handle_disconnect(Connection &conn)
{
   service.on_player_disconnect(conn.service_id(), conn.uuid());
}

}// namespace minecpp::service::front::protocol
