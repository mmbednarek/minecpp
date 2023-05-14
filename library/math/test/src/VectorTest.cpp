#include <gtest/gtest.h>
#include <minecpp/math/Vector2.h>
#include <minecpp/math/Vector3.h>

TEST(MathTest, Vector2_Equal)
{
   using minecpp::math::Vector2;
   Vector2 vec1{3, 4};
   Vector2 vec2{3, 6};
   Vector2 vec3{4, 4};
   Vector2 vec4{5, 6};

   Vector2 vec5{3, 4};

   EXPECT_TRUE(vec1 != vec2);
   EXPECT_TRUE(vec1 != vec3);
   EXPECT_TRUE(vec1 != vec4);
   EXPECT_TRUE(vec1 == vec5);

   EXPECT_FALSE(vec1 == vec2);
   EXPECT_FALSE(vec1 == vec3);
   EXPECT_FALSE(vec1 == vec4);
   EXPECT_FALSE(vec1 != vec5);
}

TEST(MathTest, Math_Vector2)
{
   using minecpp::math::Vector2;
   Vector2 vec1{3, 4};
   EXPECT_EQ(vec1.x(), 3);
   EXPECT_EQ(vec1.y(), 4);

   Vector2 vec2{-1, 2};
   EXPECT_EQ(vec2.x(), -1);
   EXPECT_EQ(vec2.y(), 2);

   EXPECT_NE(vec1, vec2);

   auto sum = vec1 + vec2;
   Vector2 expected_sum{2, 6};
   EXPECT_EQ(sum, expected_sum);

   auto sum_val = vec1 + 2;
   Vector2 expected_sum_val{5, 6};
   EXPECT_EQ(sum_val, expected_sum_val);

   auto min = vec1 - vec2;
   Vector2 expected_min{4, 2};
   EXPECT_EQ(min, expected_min);

   auto min_val = vec1 - 2;
   Vector2 expected_min_val{1, 2};
   EXPECT_EQ(min_val, expected_min_val);

   auto mult = vec1 * vec2;
   Vector2 expected_mult{-3, 8};
   EXPECT_EQ(mult, expected_mult);

   auto mult_val = vec1 * 2;
   Vector2 expected_mult_val{6, 8};
   EXPECT_EQ(mult_val, expected_mult_val);

   auto div = vec1 / vec2;
   Vector2 expected_div{-3, 2};
   EXPECT_EQ(div, expected_div);

   auto div_val = vec1 / 2;
   Vector2 expected_div_val{1.5, 2};
   EXPECT_EQ(div_val, expected_div_val);

   auto floored = expected_div_val.floor();
   Vector2 floored_expected{1, 2};
   EXPECT_EQ(floored, floored_expected);

   auto vec_cp = vec1;
   vec_cp += vec2;
   EXPECT_EQ(vec_cp, expected_sum);

   vec_cp = vec1;
   vec_cp -= vec2;
   EXPECT_EQ(vec_cp, expected_min);

   vec_cp = vec1;
   vec_cp *= vec2;
   EXPECT_EQ(vec_cp, expected_mult);

   vec_cp = vec1;
   vec_cp /= vec2;
   EXPECT_EQ(vec_cp, expected_div);

   vec_cp = vec1;
   vec_cp += 2;
   EXPECT_EQ(vec_cp, expected_sum_val);

   vec_cp = vec1;
   vec_cp -= 2;
   EXPECT_EQ(vec_cp, expected_min_val);

   vec_cp = vec1;
   vec_cp *= 2;
   EXPECT_EQ(vec_cp, expected_mult_val);

   vec_cp = vec1;
   vec_cp /= 2;
   EXPECT_EQ(vec_cp, expected_div_val);
}

TEST(MathTest, Vector3_Equal)
{
   using minecpp::math::Vector3;
   Vector3 vec1{3, 4, 5};
   Vector3 vec2{3, 6, 5};
   Vector3 vec3{4, 4, 5};
   Vector3 vec4{5, 6, 5};
   Vector3 vec5{3, 4, 6};
   Vector3 vec6{4, 6, 6};

   Vector3 vec7{3, 4, 5};

   EXPECT_TRUE(vec1 != vec2);
   EXPECT_TRUE(vec1 != vec3);
   EXPECT_TRUE(vec1 != vec4);
   EXPECT_TRUE(vec1 != vec4);
   EXPECT_TRUE(vec1 != vec5);
   EXPECT_TRUE(vec1 != vec6);
   EXPECT_TRUE(vec1 == vec7);

   EXPECT_FALSE(vec1 == vec2);
   EXPECT_FALSE(vec1 == vec3);
   EXPECT_FALSE(vec1 == vec4);
   EXPECT_FALSE(vec1 == vec5);
   EXPECT_FALSE(vec1 == vec6);
   EXPECT_FALSE(vec1 != vec7);
}

TEST(MathTest, Math_Vector3)
{
   using minecpp::math::Vector3;
   Vector3 vec1{3, 4, 5};
   EXPECT_EQ(vec1.x(), 3);
   EXPECT_EQ(vec1.y(), 4);
   EXPECT_EQ(vec1.z(), 5);
   EXPECT_EQ(vec1[0], 3);
   EXPECT_EQ(vec1[1], 4);
   EXPECT_EQ(vec1[2], 5);
   EXPECT_EQ(vec1.sum(), 3 + 4 + 5);

   Vector3 vec2{-1, 2, 1};
   EXPECT_EQ(vec2.x(), -1);
   EXPECT_EQ(vec2.y(), 2);

   EXPECT_NE(vec1, vec2);

   auto sum = vec1 + vec2;
   Vector3 expected_sum{2, 6, 6};
   EXPECT_EQ(sum, expected_sum);

   auto sum_val = vec1 + 2;
   Vector3 expected_sum_val{5, 6, 7};
   EXPECT_EQ(sum_val, expected_sum_val);

   auto min = vec1 - vec2;
   Vector3 expected_min{4, 2, 4};
   EXPECT_EQ(min, expected_min);

   auto min_val = vec1 - 2;
   Vector3 expected_min_val{1, 2, 3};
   EXPECT_EQ(min_val, expected_min_val);

   auto mult = vec1 * vec2;
   Vector3 expected_mult{-3, 8, 5};
   EXPECT_EQ(mult, expected_mult);

   auto mult_val = vec1 * 2;
   Vector3 expected_mult_val{6, 8, 10};
   EXPECT_EQ(mult_val, expected_mult_val);

   auto div = vec1 / vec2;
   Vector3 expected_div{-3, 2, 5};
   EXPECT_EQ(div, expected_div);

   auto div_val = vec1 / 2;
   Vector3 expected_div_val{1.5, 2, 2.5};
   EXPECT_EQ(div_val, expected_div_val);

   auto vec_cp = vec1;
   vec_cp += vec2;
   EXPECT_EQ(vec_cp, expected_sum);

   vec_cp = vec1;
   vec_cp -= vec2;
   EXPECT_EQ(vec_cp, expected_min);

   vec_cp = vec1;
   vec_cp *= vec2;
   EXPECT_EQ(vec_cp, expected_mult);

   vec_cp = vec1;
   vec_cp /= vec2;
   EXPECT_EQ(vec_cp, expected_div);

   vec_cp = vec1;
   vec_cp += 2;
   EXPECT_EQ(vec_cp, expected_sum_val);

   vec_cp = vec1;
   vec_cp -= 2;
   EXPECT_EQ(vec_cp, expected_min_val);

   vec_cp = vec1;
   vec_cp *= 2;
   EXPECT_EQ(vec_cp, expected_mult_val);

   vec_cp = vec1;
   vec_cp /= 2;
   EXPECT_EQ(vec_cp, expected_div_val);
}
