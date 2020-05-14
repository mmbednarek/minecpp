#include "play_handler.h"
#include "../connection.h"

namespace Front::Protocol {

PlayHandler::PlayHandler() = default;

void PlayHandler::handle(Connection &conn, MineNet::Message::Reader &r) {}

} // namespace Front::Protocol
