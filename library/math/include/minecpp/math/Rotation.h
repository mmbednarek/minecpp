#pragma once

#include <minecpp/proto/common/v1/Common.pb.h>

namespace minecpp::math {

using Radians = float;
using Degrees = float;

constexpr float g_pi = 3.14159265f;

[[nodiscard]] constexpr Radians degrees_to_radians(Degrees degrees)
{
   return degrees * g_pi / 180.0f;
}

[[nodiscard]] constexpr Degrees radians_to_degrees(Radians radians)
{
   return radians * 180.0f / g_pi;
}

struct Rotation
{
   Radians yaw;
   Radians pitch;

   [[nodiscard]] proto::common::v1::Rotation to_proto() const
   {
      proto::common::v1::Rotation out{};
      out.set_yaw(radians_to_degrees(yaw));
      out.set_pitch(radians_to_degrees(pitch));
      return out;
   }
};

}// namespace minecpp::math