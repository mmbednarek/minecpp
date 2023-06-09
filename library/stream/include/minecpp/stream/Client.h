#pragma once

#include "Host.h"

#include "minecpp/network/Network.h"

namespace minecpp::stream {

class Client : public Host
{
 public:
   Client();

   std::shared_ptr<Peer> create_peer(const network::Endpoint &endpoint);

 protected:
   std::shared_ptr<Peer> new_connection_to_shared_ptr(_ENetPeer *peer) override;
};

}// namespace minecpp::stream