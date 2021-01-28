#pragma once

namespace Utils {

class Vec2 {
 public:
   Vec2();
   Vec2(double x, double z);

   Vec2 operator*(double value) const;
   Vec2 operator/(double value) const;
   Vec2 operator+(Vec2 other) const;
   Vec2 operator-(Vec2 other) const;
   Vec2 truncate() const;

   double x, z;
};

class Vec3 {
 public:
   Vec3();
   Vec3(double x, double y, double z);

   void mul(double x, double y, double z);

   Vec3 operator*(double value) const;
   Vec3 operator/(double value) const;
   Vec3 operator-(Vec3 value) const;

   Vec2 flat() const;
   Vec3 truncate() const;

   double x, y, z;
};

double distance(Vec2 a, Vec2 b);

} // namespace Utils
