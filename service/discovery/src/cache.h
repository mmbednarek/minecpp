#ifndef MINECPP_CACHE_H
#define MINECPP_CACHE_H
#include <map>
#include <mb/int.h>
#include <minecpp/service/discovery/api.h>
#include <vector>

namespace minecpp::service::discovery {

class Cache
{
   std::vector<Endpoint> m_endpoints;
   std::unordered_multimap<std::string, mb::size> m_services;
   std::atomic<ResourceVersion> m_resource_version = 1;

 public:
   std::vector<Endpoint> lookup(const std::string &service_name) const;
   void add(const std::string &service_name, const Endpoint &endpoint);

   inline ResourceVersion resource_version() const
   {
      return m_resource_version;
   }
};

}// namespace minecpp::service::discovery


#endif//MINECPP_CACHE_H
