#include <minecpp/entity/component/Projectile.h>

namespace minecpp::entity::component {

void Projectile::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   entity->set_entity_type(m_entity_type_id);
}

}// namespace minecpp::entity::component
