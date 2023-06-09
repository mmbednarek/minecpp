#pragma once

#include "Host.h"

namespace minecpp::stream {

class Server : public Host
{
 public:
   explicit Server(Port port);

 protected:
   std::shared_ptr<Peer> new_connection_to_shared_ptr(_ENetPeer *peer) override;
};

}// namespace minecpp::stream