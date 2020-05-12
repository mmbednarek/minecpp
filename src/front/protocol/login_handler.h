#pragma once
#include "../../common/packet/reader.h"
#include "../../common/packet/writer.h"
#include "../service.h"
#include "handler.h"
#include "play_handler.h"

namespace Front::Protocol {

class LoginHandler : public Handler {
 public:
   explicit LoginHandler(Service &service);

   void handle(Connection &conn, Packet::Reader &r) override;
   void handle_login_start(Connection &conn, Packet::Reader &r);

   void reject(Connection &conn, std::string_view message);

 private:
   Service &service;
};

} // namespace Front::Protocol
