#include "config.h"
#include "players.h"
#include "protocol/login_handler.h"
#include "protocol/play_handler.h"
#include "protocol/status_handler.h"
#include "server.h"
#include <boost/log/trivial.hpp>

using namespace Front;

auto main() -> int {
   auto conf = get_config();
   Service service(conf);

   Protocol::StatusHandler status_handler;
   Protocol::PlayHandler play_handler;
   Protocol::LoginHandler login_handler(service);

   BOOST_LOG_TRIVIAL(info) << "starting server on port " << conf.port;

   try {
      boost::asio::io_context ctx;
      Server svr(ctx, conf.port,
                 dynamic_cast<Protocol::Handler *>(&play_handler),
                 dynamic_cast<Protocol::Handler *>(&status_handler),
                 dynamic_cast<Protocol::Handler *>(&login_handler));
      ctx.run();
   } catch (std::exception &e) {
      BOOST_LOG_TRIVIAL(error) << "server crash " << e.what();
   }
}