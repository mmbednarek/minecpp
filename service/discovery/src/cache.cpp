#include "cache.h"

namespace minecpp::service::discovery {

std::vector<Endpoint> Cache::lookup(const std::string &service_name) const
{
   auto count = m_services.count(service_name);
   if (count == 0) {
      return std::vector<Endpoint>();
   }

   auto iterator = m_services.equal_range(service_name);
   std::vector<Endpoint> result(count);
   std::transform(iterator.first, iterator.second, result.begin(),
                  [this](const std::pair<std::string, mb::size> &pair) { return m_endpoints[pair.second]; });
   return result;
}

void Cache::add(const std::string &service_name, const Endpoint &endpoint)
{
   ++m_resource_version;

   auto id = m_endpoints.size();
   m_endpoints.push_back(endpoint);
   m_services.insert(std::make_pair(service_name, id));
}

}// namespace minecpp::service::discovery