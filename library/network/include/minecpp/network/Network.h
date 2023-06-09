#pragma once

#include "Result.hpp"

#include <cstdint>
#include <mb/result.h>
#include <string_view>

namespace minecpp::network {

class IpAddressV4
{
 public:
   explicit IpAddressV4(std::uint32_t address);

   [[nodiscard]] static Result<IpAddressV4> from_host(const std::string &address);

   [[nodiscard]] std::uint32_t to_uint() const;

 private:
   std::uint32_t m_address;
};

using Port = std::uint16_t;

class Endpoint
{
 public:
   Endpoint(const IpAddressV4 &ip, Port port);

   [[nodiscard]] static Result<Endpoint> from_host(const std::string &address, Port default_port = 8080);

   [[nodiscard]] const IpAddressV4 &ip_address() const;
   [[nodiscard]] Port port() const;

 private:
   IpAddressV4 m_ip;
   Port m_port;
};

}// namespace minecpp::network