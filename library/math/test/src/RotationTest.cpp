#include <gtest/gtest.h>
#include <minecpp/math/Rotation.h>
#include <minecpp/math/Vector3.h>

using minecpp::math::g_pi;
using minecpp::math::Rotation;
using minecpp::math::Vector3;

constexpr auto is_zero(float value)
{
   return std::abs(value) < 0.0001f;
}

TEST(MathTest, Rotation_VectorFromYaw)
{
   auto vec1 = Rotation{0.0f, 0.0f}.vector3();
   EXPECT_TRUE(is_zero(vec1.x()));
   EXPECT_FLOAT_EQ(vec1.z(), 1.0f);
   auto rot1 = Rotation::from_vector3(vec1);
   EXPECT_TRUE(is_zero(rot1.yaw));
   EXPECT_TRUE(is_zero(rot1.pitch));

   auto vec2 = Rotation{g_pi / 2.0f, 0.0f}.vector3();
   EXPECT_FLOAT_EQ(vec2.x(), -1.0f);
   EXPECT_TRUE(is_zero(vec2.z()));
   auto rot2 = Rotation::from_vector3(vec2);
   EXPECT_FLOAT_EQ(rot2.yaw, g_pi / 2.0f);
   EXPECT_TRUE(is_zero(rot2.pitch));

   auto vec3 = Rotation{g_pi, 0.0f}.vector3();
   EXPECT_TRUE(is_zero(vec3.x()));
   EXPECT_FLOAT_EQ(vec3.z(), -1.0f);
   auto rot3 = Rotation::from_vector3(vec3);
   EXPECT_FLOAT_EQ(rot3.yaw, g_pi);
   EXPECT_TRUE(is_zero(rot3.pitch));

   auto vec4 = Rotation{1.5f * g_pi, 0.0f}.vector3();
   EXPECT_FLOAT_EQ(vec4.x(), 1.0f);
   EXPECT_TRUE(is_zero(vec4.z()));
   auto rot4 = Rotation::from_vector3(vec4);
   EXPECT_FLOAT_EQ(rot4.yaw, 1.5f * g_pi);
   EXPECT_TRUE(is_zero(rot4.pitch));
}

TEST(MathTest, Rotation_RadiansDegTest)
{
   EXPECT_LE(std::abs(minecpp::math::radians_to_degrees(g_pi) - 180.0f), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::radians_to_degrees(g_pi / 2.0f) - 90.0f), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::radians_to_degrees(3.0f * g_pi / 2.0f) - 270.0f), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::degrees_to_radians(180.0f) - g_pi), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::degrees_to_radians(90.0f) - g_pi / 2.0f), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::degrees_to_radians(270.0f) - 3.0f * g_pi / 2.0f), 0.00001f);
}
