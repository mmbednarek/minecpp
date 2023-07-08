#include <minecpp/game/player/Player.h>
#include <minecpp/nbt/player/Player.schema.h>

namespace minecpp::game::player {

Player::Player(Id id, std::string_view name) :
    m_id(id),
    m_name(name)
{
}

Player Player::from_nbt(const nbt::player::Player &player, const std::string_view name)
{
   Player result(read_id_from_nbt(player.uuid), name);
   return result;
}

proto::player::Player Player::to_proto() const
{
   proto::player::Player result{};
   result.set_entity_id(m_entity_id);
   result.set_name(m_name);
   result.set_game_mode(game::write_mode_to_proto(m_game_mode));
   return result;
}

}// namespace minecpp::game::player

// namespace minecpp::game::player