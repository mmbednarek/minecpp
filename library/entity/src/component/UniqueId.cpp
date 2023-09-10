#include <boost/uuid/random_generator.hpp>
#include <minecpp/entity/component/UniqueId.h>

namespace minecpp::entity::component {

boost::uuids::random_generator g_uuid_generator;

UniqueId::UniqueId() :
    m_id(g_uuid_generator())
{
}

void UniqueId::serialize_to_net(game::NetworkEntity *net_entity) const
{
   assert(net_entity);
   net_entity->entity_data.unique_id = m_id;
}

}// namespace minecpp::entity::component