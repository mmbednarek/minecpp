#pragma once
#include <boost/uuid/uuid_io.hpp>
#include <minecpp/proto/player/v1/player.pb.h>
#include <minecpp/util/uuid.h>

namespace minecpp::player {

using Id = minecpp::util::uuid;

constexpr Id read_id_from_proto(const proto::player::v1::PlayerId &id) {
   return util::read_uuid(id.lower(), id.upper());
}

inline proto::player::v1::PlayerId write_id_to_proto(Id player_id) {
   mb::u64 lower, upper;
   std::tie(lower, upper) = util::write_uuid(player_id);

   proto::player::v1::PlayerId result;
   result.set_lower(lower);
   result.set_upper(upper);
   return result;
}

constexpr Id read_id_from_nbt(const std::vector<int> &id) {
   if (id.size() != 4)
      return Id();
   return util::read_uuid4(id[0], id[1], id[2], id[3]);
}

inline std::string format_player_id(Id player_id) {
   return boost::uuids::to_string(player_id);
}

}// namespace minecpp::player