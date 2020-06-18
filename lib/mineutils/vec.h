#pragma once

namespace Utils {

class Vec2 {
public:
	Vec2();
	Vec2(double x, double z);

	double x, z;
};

class Vec3 {
 public:
   Vec3();
   Vec3(double x, double y, double z);

   void mul(double x, double y, double z);

   Vec3 operator *(double value) const;
   Vec3 operator /(double value) const;
   Vec3 operator -(Vec3 value) const;

   double x, y, z;
};

}
