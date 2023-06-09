#include "Client.h"

#include <enet/enet.h>
#include <boost/endian.hpp>

namespace minecpp::stream {

namespace {
ENetHost *initialize_client()
{
   enet_initialize();
   return enet_host_create(nullptr, 1, 2, 0, 0);
}
}// namespace

Client::Client() :
    Host(initialize_client())
{
}

std::shared_ptr<Peer> Client::create_peer(const network::Endpoint &endpoint)
{

   ENetAddress enet_address;
   enet_address.host = boost::endian::big_to_native(endpoint.ip_address().to_uint());
   enet_address.port = endpoint.port();

   auto ptr = std::make_shared<Peer>(*this, enet_host_connect(this->host(), &enet_address, 2, 0), true);
   this->add_peer(ptr->id(), ptr);

   return ptr;
}

std::shared_ptr<Peer> Client::new_connection_to_shared_ptr(_ENetPeer *raw_peer)
{
   Peer *peer = static_cast<Peer*>(raw_peer->data);
   peer->set_is_connected(true);
   return this->peer_at(peer->id());
}

}// namespace minecpp::stream