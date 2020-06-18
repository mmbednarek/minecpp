#include "vec.h"

namespace Utils {

Vec2::Vec2(double x, double z) : x(x), z(z) {}

Vec2::Vec2() : x(0.0), z(0.0) {}

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

void Vec3::mul(double x, double y, double z) {
   this->x *= x;
   this->y *= y;
   this->z *= z;
}

Vec3 Vec3::operator*(double value) const {
   return Vec3(x * value, y * value, z * value);
}

Vec3 Vec3::operator/(double value) const {
   return Vec3(x / value, y / value, z / value);
}

Vec3 Vec3::operator-(Vec3 v) const { return Vec3(x - v.x, y - v.y, z - v.z); }

} // namespace Utils
