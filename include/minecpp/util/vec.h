#pragma once
#include <vector>
#include <cmath>

namespace minecpp::util {

struct Vec2 {
   Vec2() = default;
   constexpr Vec2(double x, double z) : x(x), z(z) {}

   Vec2 operator*(double value) const;
   Vec2 operator/(double value) const;

   constexpr Vec2 operator/(const Vec2 &other) const {
      return Vec2(x / other.x, z / other.z);
   }

   Vec2 operator+(Vec2 other) const;
   Vec2 operator-(Vec2 other) const;
   [[nodiscard]] constexpr Vec2 truncate() const {
      return {std::floor(x), std::floor(z)};
   }

   double x{}, z{};
};

struct Vec3 {
   Vec3() = default;
   constexpr Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

   void mul(double x, double y, double z);

   Vec3 operator*(double value) const;
   Vec3 operator/(double value) const;
   Vec3 operator-(Vec3 value) const;

   constexpr Vec3 operator/(const Vec3 &other) const {
      return Vec3(x / other.x, y / other.y, z / other.z);
   }

   Vec2 flat() const;
   Vec3 truncate() const;

   double x{}, y{}, z{};

   [[nodiscard]] static inline Vec3 from_nbt(const std::vector<double> &vec) {
      if (vec.size() != 3)
         return Vec3();
      return Vec3(vec[0], vec[1], vec[2]);
   }
};

double distance(Vec2 a, Vec2 b);

}// namespace minecpp::util
