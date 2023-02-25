#include <minecpp/entity/component/Player.h>

namespace minecpp::entity::component {

void Player::serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const
{
   auto [lower, upper] = util::write_uuid(this->id);
   entity->mutable_uuid()->set_lower(lower);
   entity->mutable_uuid()->set_upper(upper);
}

}// namespace minecpp::entity::component