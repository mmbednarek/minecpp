#include <minecpp/entity/component/Abilities.h>

namespace minecpp::entity::component {

void Abilities::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
//   *entity->mutable_abilities() = this->abilities.to_proto();
}

}// namespace minecpp::entity::component
