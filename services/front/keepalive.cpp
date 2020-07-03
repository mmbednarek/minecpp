#include "keepalive.h"
#include <minenet/msg/clientbound.h>
#include <mineutils/time.h>

namespace Front {

static void keep_alive_process(Server &server) {
   server.for_each_connection([](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      send(conn, MineNet::Message::KeepAlive{
          .time = Utils::now_milis(),
      });
   });
}

constexpr int keep_alive_interval = 8;

void keepalive_update(Server &server) {
   uint64_t last_update = 0;
   for (;;) {
      if (Utils::now() - last_update < keep_alive_interval) {
         continue;
      }
      keep_alive_process(server);
      last_update = Utils::now();
   }
}

} // namespace Front
