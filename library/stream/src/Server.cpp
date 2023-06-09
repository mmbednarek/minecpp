#include "Server.h"

#include <enet/enet.h>

namespace minecpp::stream {

namespace {
ENetHost *initialize_server(Port port)
{
   enet_initialize();

   ENetAddress address;
   address.host = ENET_HOST_ANY;
   address.port = port;
   return enet_host_create(&address, 32, 2, 0, 0);
}
}// namespace

Server::Server(Port port) :
    Host(initialize_server(port))
{
}

std::shared_ptr<Peer> Server::new_connection_to_shared_ptr(_ENetPeer *raw_peer)
{
   auto peer = std::make_shared<Peer>(*this, raw_peer, false);
   this->add_peer(peer->id(), peer);
   return peer;
}

}// namespace minecpp::stream
