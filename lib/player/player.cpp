#include <minecpp/game/entity/entity.h>
#include <minecpp/nbt/player/v1/player.nbt.h>
#include <minecpp/player/player.h>
#include <minecpp/player/tracking.h>

namespace minecpp::player {

Player::Player(minecpp::player::Id id, std::string_view name, const util::Vec3 &pos) : m_id(id),
                                                                                       m_name(name),
                                                                                       m_tracking(std::make_unique<Tracking>(pos, 16)) {}

void Player::on_movement(game::World &w, util::Vec3 pos) {
   m_tracking->on_movement(w, *this, pos);
}

mb::result<mb::empty> Player::load_chunks(game::World &w) {
   return m_tracking->load_chunks(w, *this);
}

Abilities Abilities::from_proto(const proto::player::v1::Abilities &abilities) {
   Abilities result;
   result.fly_speed = abilities.fly_speed();
   result.walk_speed = abilities.walk_speed();
   result.flying = abilities.flying();
   result.instant_build = abilities.instant_build();
   result.may_fly = abilities.may_fly();
   result.may_build = abilities.may_build();
   result.invulnerable = abilities.invulnerable();
   return result;
}

minecpp::proto::player::v1::Abilities Abilities::to_proto() const {
   minecpp::proto::player::v1::Abilities result;
   result.set_fly_speed(fly_speed);
   result.set_walk_speed(walk_speed);
   result.set_flying(flying);
   result.set_instant_build(instant_build);
   result.set_may_fly(may_fly);
   result.set_may_build(may_build);
   result.set_invulnerable(invulnerable);
   return result;
}

Player Player::from_nbt(const nbt::player::v1::Player &player, const std::string &name) {
   Player result(read_id_from_nbt(player.uuid), name, util::Vec3::from_nbt(player.pos));
   result.m_xp_total = player.xp_total;
   result.m_xp_points = player.xp_p;
   result.m_xp_seed = player.xp_seed;
   result.m_xp_level = player.xp_level;
   result.m_food_level = player.food_level;
   result.m_food_saturation_level = player.food_saturation_level;
   result.m_food_exhaustion_level = player.food_exhaustion_level;
   result.m_food_tick_timer = player.food_tick_timer;
   result.m_abilities.invulnerable = player.abilities.invulnerable;
   result.m_abilities.may_build = player.abilities.may_build;
   result.m_abilities.instant_build = player.abilities.instabuild;
   result.m_abilities.flying = player.abilities.flying;
   result.m_abilities.may_fly = player.abilities.mayfly;
   result.m_abilities.walk_speed = player.abilities.walk_speed;
   result.m_abilities.fly_speed = player.abilities.fly_speed;
   return result;
}

proto::player::v1::Player Player::to_proto(const game::entity::Entity &entity) const {
   proto::player::v1::Player result{};
   result.set_entity_id(m_entity_id);
   result.set_name(m_name);
   result.set_game_mode(game::write_mode_to_proto(m_game_mode));
   auto pos = entity.get_pos();
   result.mutable_position()->set_x(pos.x);
   result.mutable_position()->set_y(pos.y);
   result.mutable_position()->set_z(pos.z);
   result.mutable_rotation()->set_yaw(entity.get_yaw());
   result.mutable_rotation()->set_pitch(entity.get_pitch());
   return result;
}

}// namespace minecpp::player