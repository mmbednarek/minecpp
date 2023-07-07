#pragma once
#include <boost/uuid/uuid_io.hpp>
#include <minecpp/game/Types.hpp>
#include <minecpp/proto/player/Player.pb.h>

namespace minecpp::game::player {

using Id = game::PlayerId;

inline Id read_id_from_proto(const proto::player::PlayerId &id)
{
   return util::read_uuid(id.lower(), id.upper());
}

inline proto::player::PlayerId write_id_to_proto(Id player_id)
{
   mb::u64 lower, upper;
   std::tie(lower, upper) = util::write_uuid(player_id);

   proto::player::PlayerId result;
   result.set_lower(lower);
   result.set_upper(upper);
   return result;
}

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