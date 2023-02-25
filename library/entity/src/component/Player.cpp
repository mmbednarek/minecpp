#include <minecpp/entity/component/Player.h>
#include <minecpp/game/player/Id.h>

namespace minecpp::entity::component {

void Player::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   entity->set_entity_type(116);

   auto [lower, upper] = util::write_uuid(this->id);
   entity->mutable_uuid()->set_lower(lower);
   entity->mutable_uuid()->set_upper(upper);
}

}// namespace minecpp::entity::component