#include "PlayHandler.h"
#include "../Connection.h"
#include "../Service.h"

#include "minecpp/net/play/Serverbound.schema.h"

namespace minecpp::service::front::protocol {

PlayHandler::PlayHandler(Service &service) :
    service(service)
{
}

void PlayHandler::handle(Connection &connection, Reader &reader)
{
   connection.async_read_packet(*this);
   net::play::sb::visit_message(service, connection.uuid(), reader);
}

void PlayHandler::handle_disconnect(Connection &conn)
{
   service.on_player_disconnect(conn.service_id(), conn.uuid());
}

}// namespace minecpp::service::front::protocol
