#include <minecpp/entity/component/Location.h>

namespace minecpp::entity::component {

void Location::serialize_to_proto(proto::entity::v1::Entity *entity) const {
   *entity->mutable_position() = this->position.to_proto();
}

void Rotation::serialize_to_proto(proto::entity::v1::Entity *entity) const {
   entity->mutable_rotation()->set_yaw(this->yaw);
   entity->mutable_rotation()->set_pitch(this->pitch);
}
}
