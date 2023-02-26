#include <boost/uuid/random_generator.hpp>
#include <minecpp/entity/component/UniqueId.h>

namespace minecpp::entity::component {

boost::uuids::random_generator g_uuid_generator;

UniqueId::UniqueId() :
    m_id(g_uuid_generator())
{
}

void UniqueId::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   auto [lower, upper] = util::write_uuid(m_id);
   entity->mutable_uuid()->set_lower(lower);
   entity->mutable_uuid()->set_upper(upper);
}

}// namespace minecpp::entity::component