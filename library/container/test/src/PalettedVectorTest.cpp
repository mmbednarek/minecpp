#include <array>
#include <gtest/gtest.h>
#include <minecpp/container/PalettedVector.h>

using minecpp::container::PalettedVector;

TEST(PalettedVector, Values)
{
   std::array<int, 16> data{3, 1, 4, 1, 5, 9, 2, 1, 1, 2, 9, 5, 1, 4, 1, 3};
   PalettedVector<int> values{data.begin(), data.end()};

   for (std::size_t i{0}; i < data.size(); ++i) {
      ASSERT_EQ(data[i], values[i]);
   }

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = values.begin()](int value) mutable { return value == *(at++); }));
}