#include <cmath>
#include <minecpp/util/Vec.h>

namespace minecpp::util {

Vec2 Vec2::operator*(double value) const
{
   return Vec2(x * value, z * value);
}

Vec2 Vec2::operator/(double value) const
{
   return Vec2(x / value, z / value);
}

Vec2 Vec2::operator+(Vec2 other) const
{
   return Vec2(x + other.x, z + other.z);
}

Vec2 Vec2::operator-(Vec2 other) const
{
   return {x - other.x, z - other.z};
}

void Vec3::mul(double x, double y, double z)
{
   this->x *= x;
   this->y *= y;
   this->z *= z;
}

Vec3 Vec3::operator*(double value) const
{
   return {x * value, y * value, z * value};
}

Vec3 Vec3::operator/(double value) const
{
   return {x / value, y / value, z / value};
}

Vec3 Vec3::operator-(Vec3 v) const
{
   return {x - v.x, y - v.y, z - v.z};
}

Vec2 Vec3::flat() const
{
   return {x, z};
}

Vec3 Vec3::truncate() const
{
   return Vec3(std::floor(x), std::floor(y), std::floor(z));
}

double distance(Vec2 a, Vec2 b)
{
   return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.z - b.z, 2));
}

}// namespace minecpp::util
