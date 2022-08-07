#include <array>
#include <gtest/gtest.h>
#include <minecpp/container/TightArray.h>

using minecpp::container::TightArray;

TEST(TightArray, EncodingRegular)
{
   std::array<int, 16> data{3, 1, 4, 1, 5, 9, 2, 1, 1, 2, 9, 5, 1, 4, 1, 3};
   TightArray<int, 16, mb::u8, 4> encoded{data.begin(), data.end()};

   data[3] = 10;
   encoded.set(3, 10);

   for (mb::u32 i{0}; i < 16; ++i) {
      ASSERT_EQ(encoded.at(i), data[i]);
   }
}
