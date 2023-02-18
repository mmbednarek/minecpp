#include <minecpp/game/entity/Entity.h>
#include <minecpp/game/player/Player.h>
#include <minecpp/game/player/Tracking.h>
#include <minecpp/nbt/player/v1/Player.nbt.h>

namespace minecpp::game::player {

Player::Player(Id id, std::string_view name, const math::Vector3 &pos, game::Notifier &notifier) :
    m_id(id),
    m_name(name),
    m_tracking(std::make_unique<Tracking>(pos, 16)),
    m_inventory(id, notifier)
{
}

void Player::on_movement(game::World &w, math::Vector3 pos)
{
   m_tracking->on_movement(w, *this, pos);
}

mb::result<mb::empty> Player::load_chunks(game::World &w)
{
   return m_tracking->load_chunks(w, *this);
}

Player Player::from_nbt(const nbt::player::v1::Location &player, const std::string &name,
                        game::Notifier &notifier)
{
   Player result(read_id_from_nbt(player.uuid), name,
                 math::Vector3{player.pos[0], player.pos[1], player.pos[2]}, notifier);
   result.m_xp_total                = player.xp_total;
   result.m_xp_points               = player.xp_p;
   result.m_xp_seed                 = player.xp_seed;
   result.m_xp_level                = player.xp_level;
   result.m_food_level              = player.food_level;
   result.m_food_saturation_level   = player.food_saturation_level;
   result.m_food_exhaustion_level   = player.food_exhaustion_level;
   result.m_food_tick_timer         = player.food_tick_timer;
   return result;
}

proto::player::v1::Player Player::to_proto() const
{
   proto::player::v1::Player result{};
   result.set_entity_id(m_entity_id);
   result.set_name(m_name);
   result.set_game_mode(game::write_mode_to_proto(m_game_mode));
   return result;
}

}// namespace minecpp::game::player

// namespace minecpp::game::player