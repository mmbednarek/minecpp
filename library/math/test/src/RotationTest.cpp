#include <gtest/gtest.h>
#include <minecpp/math/Vector3.h>

TEST(MathTest, Rotation_VectorFromYaw)
{
   auto vec1 = minecpp::math::Vector3::from_yaw_and_pitch(0, 0);
   EXPECT_EQ(vec1.x(), 0.0f);
   EXPECT_EQ(vec1.z(), 1.0f);

   auto vec2 = minecpp::math::Vector3::from_yaw_and_pitch(std::numbers::pi / 2.0, 0);
   EXPECT_EQ(vec2.x(), -1);
   EXPECT_LE(abs(vec2.z()), 0.00001f);

   auto vec3 = minecpp::math::Vector3::from_yaw_and_pitch(std::numbers::pi, 0);
   EXPECT_LE(abs(vec3.x()), 0.00001f);
   EXPECT_EQ(vec3.z(), -1);

   auto vec4 = minecpp::math::Vector3::from_yaw_and_pitch(3.0 * std::numbers::pi / 2.0, 0);
   EXPECT_EQ(vec4.x(), 1);
   EXPECT_LE(abs(vec4.z()), 0.00001f);
}

TEST(MathTest, Rotation_RadiansDegTest)
{
   EXPECT_LE(std::abs(minecpp::math::radians_to_degrees(std::numbers::pi) - 180.0f), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::radians_to_degrees(std::numbers::pi / 2.0) - 90.0f), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::radians_to_degrees(3.0 * std::numbers::pi / 2.0) - 270.0f), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::degrees_to_radians(180.0f) - std::numbers::pi), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::degrees_to_radians(90.0f) - std::numbers::pi / 2.0), 0.00001f);
   EXPECT_LE(std::abs(minecpp::math::degrees_to_radians(270.0f) - 3.0 * std::numbers::pi / 2.0), 0.00001f);
}
