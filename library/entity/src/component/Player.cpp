#include <minecpp/entity/component/Player.h>
#include <minecpp/game/player/Id.h>

namespace minecpp::entity::component {

void Player::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   *entity->mutable_player_id() = game::player::write_id_to_proto(this->id);
}

}// namespace minecpp::entity::component