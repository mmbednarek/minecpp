#pragma once

#include <mb/enum.h>
#include <mb/int.h>
#include <minecpp/proto/common/v1/Common.pb.h>

namespace minecpp::game {

enum class FaceMask : mb::u8;

enum class FaceValue
{
   Bottom = 0,
   Top    = 1,
   North  = 2,
   South  = 3,
   West   = 4,
   East   = 5,
};

using Face_Base = mb::enum_wrapper<FaceValue, "bottom", "top", "north", "south", "west", "east">;

class Face final : public Face_Base
{
 public:
   MB_ENUM_TRAITS(Face)

   MB_ENUM_FIELD(Bottom)
   MB_ENUM_FIELD(Top)
   MB_ENUM_FIELD(North)
   MB_ENUM_FIELD(South)
   MB_ENUM_FIELD(West)
   MB_ENUM_FIELD(East)

   static Face from_proto(proto::common::v1::Face face);
   proto::common::v1::Face to_proto();
   [[nodiscard]] Face opposite_face();
   [[nodiscard]] FaceMask to_mask();
};

bool operator&(FaceMask lhs, Face rhs);

}// namespace minecpp::game
