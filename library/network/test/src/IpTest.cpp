#include <gtest/gtest.h>
#include <minecpp/network/Network.h>

TEST(Network, Ip_FromString)
{
   auto ip = minecpp::network::IpAddressV4::from_host("localhost");
   ASSERT_TRUE(ip.ok());
   ASSERT_EQ(ip->to_uint(), 2130706433);
}

TEST(Network, Endpoint_FromString)
{
   auto endpoint = minecpp::network::Endpoint::from_host("localhost");
   ASSERT_TRUE(endpoint.ok());
   ASSERT_EQ(endpoint->ip_address().to_uint(), 2130706433);
   ASSERT_EQ(endpoint->port(), 8080);
}

TEST(Network, Endpoint_FromStringWithPort)
{
   auto endpoint = minecpp::network::Endpoint::from_host("localhost:7800");
   ASSERT_TRUE(endpoint.ok());
   ASSERT_EQ(endpoint->ip_address().to_uint(), 2130706433);
   ASSERT_EQ(endpoint->port(), 7800);
}
