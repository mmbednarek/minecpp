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

TEST(TightArray, HeightContainer)
{
   auto raw_size = TightArray<int, 256, std::uint64_t, 9>::raw_size;
   ASSERT_EQ(raw_size, 37);
   TightArray<int, 256, uint64_t, 9> test{};

   for (int i = 0; i < 256; ++i) {
      ASSERT_EQ(test.at(static_cast<size_t>(i)), 0);
   }

   for (int i = 0; i < 256; ++i) {
      test.set(static_cast<unsigned long>(i), i);
   }

   for (int i = 0; i < 256; ++i) {
      ASSERT_EQ(test.at(static_cast<size_t>(i)), i);
   }
}
