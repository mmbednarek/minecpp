#pragma once

#include "Math.h"
#include "Vector3.h"

#include <minecpp/proto/common/Common.pb.h>

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

[[nodiscard]] constexpr Radians find_angle(float x, float y)
{
   if (y > 0.0f) {
      return math::fmod(-std::asin(x), 2 * g_pi);
   }
   return g_pi + std::asin(x);
}

struct Rotation
{
   Radians yaw;
   Radians pitch;

   [[nodiscard]] static Rotation from_degrees(Degrees yaw, Degrees pitch)
   {
      return {math::fmod(degrees_to_radians(yaw), 2 * g_pi), math::fmod(degrees_to_radians(pitch), 2 * g_pi)};
   }

   [[nodiscard]] static Rotation from_vector3(const math::Vector3f &vector)
   {
      const auto norm  = vector.normalize();
      const auto abs_y = std::abs(norm.y());

      if (abs_y < 0.001f) {
         return {find_angle(norm.x(), norm.z()), 0.0f};
      }
      if (abs_y > 0.999f) {
         return {0.0f, norm.y() > 0.0f ? (0.5f * g_pi) : (1.5f * g_pi)};
      }

      const auto pitch     = std::asin(norm.y());
      const auto cos_pitch = std::cos(pitch);
      const auto yaw       = find_angle(norm.x() / cos_pitch, norm.z() / cos_pitch);
      return {static_cast<float>(yaw), static_cast<float>(pitch)};
   }

   [[nodiscard]] static Rotation from_proto(const proto::common::Rotation &proto_rot)
   {
      return Rotation::from_degrees(proto_rot.yaw(), proto_rot.pitch());
   }

   [[nodiscard]] proto::common::Rotation to_proto() const
   {
      proto::common::Rotation out{};
      out.set_yaw(radians_to_degrees(yaw));
      out.set_pitch(radians_to_degrees(pitch));
      return out;
   }

   template<typename TValue = float>
   [[nodiscard]] math::BaseVector<TValue, 3> vector3() const
   {
      const auto cos_pitch = std::cos(pitch);
      return {static_cast<TValue>(-std::sin(yaw) * cos_pitch), static_cast<TValue>(-std::sin(pitch)),
              static_cast<TValue>(std::cos(yaw) * cos_pitch)};
   }

   [[nodiscard]] Rotation reverse() const
   {
      return {
              math::fmod(-yaw, 2 * g_pi),
              math::fmod(-pitch, 2 * g_pi),
      };
   }

   [[nodiscard]] Rotation reverse_yaw() const
   {
      return {
              math::fmod(-yaw, 2 * g_pi),
              pitch,
      };
   }

    [[nodiscard]] Degrees yaw_degrees() const
    {
        return radians_to_degrees(yaw);
    }

    [[nodiscard]] Degrees pitch_degrees() const
    {
        return radians_to_degrees(pitch);
    }
};

}// namespace minecpp::math