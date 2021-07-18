#ifndef MINECPP_PLAYER_H
#define MINECPP_PLAYER_H
#include <minecpp/util/uuid.h>
#include <minecpp/proto/player/v1/player.pb.h>

namespace minecpp::player {

using id = minecpp::util::uuid;

constexpr id read_id_from_proto(const proto::player::v1::PlayerId &id) {
   return util::read_uuid(id.lower(), id.upper());
}

inline proto::player::v1::PlayerId write_id_to_proto(id player_id) {
   mb::u64 lower, upper;
   std::tie(lower, upper) = util::write_uuid(player_id);

   proto::player::v1::PlayerId result;
   result.set_lower(lower);
   result.set_upper(upper);
   return result;
}

}

#endif//MINECPP_PLAYER_H
