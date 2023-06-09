#include "Network.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <charconv>

namespace minecpp::network {

IpAddressV4::IpAddressV4(std::uint32_t address) :
    m_address(address)
{
}

Result<IpAddressV4> IpAddressV4::from_host(const std::string &address)
{
   using boost::asio::ip::udp;

   boost::asio::io_service service;
   udp::resolver resolver(service);
   udp::resolver::query query(udp::v4(), address, "");
   udp::resolver::iterator endpoints = resolver.resolve(query);

   return IpAddressV4(endpoints->endpoint().address().to_v4().to_uint());
}

std::uint32_t IpAddressV4::to_uint() const
{
   return m_address;
}

Endpoint::Endpoint(const IpAddressV4 &ip, Port port) :
    m_ip(ip),
    m_port(port)
{
}

const IpAddressV4 &Endpoint::ip_address() const
{
   return m_ip;
}

Port Endpoint::port() const
{
   return m_port;
}

Result<Endpoint> Endpoint::from_host(const std::string &address, Port default_port)
{
   auto colon_at = address.find(':');

   if (colon_at == std::string::npos) {
      auto ip = IpAddressV4::from_host(address);
      if (ip.has_failed())
         return ip.err();

      return Endpoint(*ip, default_port);
   }

   auto ip = IpAddressV4::from_host(address.substr(0, colon_at));
   if (ip.has_failed())
      return ip.err();

   int port{};
   std::from_chars(address.data() + colon_at + 1, address.data() + address.size(), port);

   return Endpoint(*ip, static_cast<Port>(port));
}

}// namespace minecpp::network