#include <minecpp/util/vec.h>
#include <cmath>

namespace Utils {

Vec2::Vec2(double x, double z) : x(x), z(z) {}

Vec2::Vec2() : x(0.0), z(0.0) {}

Vec2 Vec2::operator*(double value) const { return Vec2(x * value, z * value); }

Vec2 Vec2::operator/(double value) const { return Vec2(x / value, z / value); }

Vec2 Vec2::operator+(Vec2 other) const { return Vec2(x + other.x, z + other.z); }

Vec2 Vec2::truncate() const { return Vec2(std::floor(x), std::floor(z)); }

Vec2 Vec2::operator-(Vec2 other) const {
   return Vec2(x - other.x, z - other.z);
}

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

void Vec3::mul(double x, double y, double z) {
   this->x *= x;
   this->y *= y;
   this->z *= z;
}

Vec3 Vec3::operator*(double value) const { return Vec3(x * value, y * value, z * value); }

Vec3 Vec3::operator/(double value) const { return Vec3(x / value, y / value, z / value); }

Vec3 Vec3::operator-(Vec3 v) const { return Vec3(x - v.x, y - v.y, z - v.z); }

Vec2 Vec3::flat() const { return Vec2(x, z); }

Vec3 Vec3::truncate() const {
   return Vec3(std::floor(x), std::floor(y), std::floor(z));
}

double distance(Vec2 a, Vec2 b) { return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.z - b.z, 2)); }

}// namespace Utils
