#pragma once
#include <boost/uuid/uuid_io.hpp>
#include <minecpp/game/Types.hpp>

namespace minecpp::game::player {

using Id = game::PlayerId;

inline Id read_id_from_nbt(const std::vector<int> &id)
{
   if (id.size() != 4)
      return {};
   return util::read_uuid4(id[0], id[1], id[2], id[3]);
}

inline std::vector<int> write_id_to_nbt(Id id)
{
   auto [a, b, c, d] = util::write_uuid4(id);
   return std::vector<int>{a, b, c, d};
}

inline std::string format_player_id(Id player_id)
{
   return boost::uuids::to_string(player_id);
}

}// namespace minecpp::game::player