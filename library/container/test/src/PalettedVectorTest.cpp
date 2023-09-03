#include <array>
#include <gtest/gtest.h>
#include <minecpp/container/PalettedVector.h>

using minecpp::container::PalettedVector;

TEST(PalettedVector, BasicTest)
{
   std::array<int, 16> data{3, 1, 4, 1, 5, 9, 2, 1, 1, 2, 9, 5, 1, 4, 1, 3};
   PalettedVector<int, 8> values{data.begin(), data.end()};

   for (std::size_t i{0}; i < data.size(); ++i) {
      ASSERT_EQ(data[i], values[i]);
   }

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = values.begin()](int value) mutable { return value == *(at++); }));
}

TEST(PalettedVector, Setting)
{
   PalettedVector<int, 5> values;
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Empty);

   values.set(0, 5);
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::SingleValue);
   EXPECT_EQ(values.at(0), 5);

   for (std::size_t i = 0; i < 100; ++i) {
      values.set(i, 5);
   }

   EXPECT_EQ(values.type(), minecpp::container::PaletteType::SingleValue);
   for (std::size_t i = 0; i < 100; ++i) {
      EXPECT_EQ(values.at(i), 5);
   }

   values.set(0, 6);
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Indirect);
   EXPECT_EQ(values.at(0), 6);
   for (std::size_t i = 1; i < 100; ++i) {
      EXPECT_EQ(values.at(i), 5);
   }

   for (std::size_t i = 0; i < 32; ++i) {
      values.set(i, static_cast<int>(i));
   }

   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Indirect);
   for (std::size_t i = 1; i < 32; ++i) {
      EXPECT_EQ(values.at(i), i);
   }

   values.set(32, 32);
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Direct);
   EXPECT_EQ(values.at(32), 32);

   for (std::size_t i = 0; i < 100; ++i) {
      values.set(i, static_cast<int>(i));
   }

   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Direct);
   for (std::size_t i = 1; i < 100; ++i) {
      EXPECT_EQ(values.at(i), i);
   }
}

TEST(PalettedVector, ConstructSingle)
{
   std::array<int, 32> arr{};
   std::fill(arr.begin(), arr.end(), 13);

   PalettedVector<int, 5> values(arr.begin(), arr.end());
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::SingleValue);

   for (std::size_t i = 0; i < 32; ++i) {
      EXPECT_EQ(values.at(i), 13);
   }
}

TEST(PalettedVector, ConstructIndirect)
{
   std::array<int, 32> arr{};
   std::iota(arr.begin(), arr.end(), 0);

   PalettedVector<int, 5> values(arr.begin(), arr.end());
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Indirect);

   for (std::size_t i = 0; i < 32; ++i) {
      EXPECT_EQ(values.at(i), i);
   }
}

TEST(PalettedVector, ConstructDirect)
{
   std::array<int, 100> arr{};
   std::iota(arr.begin(), arr.end(), 0);

   PalettedVector<int, 5> values(arr.begin(), arr.end());
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Direct);

   for (std::size_t i = 0; i < 100; ++i) {
      EXPECT_EQ(values.at(i), i);
   }
}

TEST(PalettedVector, Huge)
{
   std::vector<int> norm;
   PalettedVector<int, 8> values;

   for (std::size_t i = 0; i < 10000; ++i) {
      auto rnd = rand() % 10000;
      values.set(i, rnd);
      norm.push_back(rnd);

      for (std::size_t j = 0; j <= i; ++j) {
         if (norm[j] != values[j]) {
            EXPECT_EQ(norm[j], values[j]);
         }
      }
   }
}

TEST(PalettedVector, SingleValueLoop)
{
   std::array<int, 100> arr{};
   std::fill(arr.begin(), arr.end(), 5);

   PalettedVector<int, 5> values(arr.begin(), arr.end());
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::SingleValue);

   int count = 0;
   for (auto value : values) {
      EXPECT_EQ(value, 5);
      ++count;
   }
   EXPECT_EQ(count, arr.size());
}

TEST(PalettedVector, IndirectLoop)
{
   std::array<int, 16> arr{};
   std::iota(arr.begin(), arr.end(), 0);

   PalettedVector<int, 5> values(arr.begin(), arr.end());
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Indirect);

   int count = 0;
   int num = 0;
   for (auto value : values) {
      EXPECT_EQ(value, num++);
      ++count;
   }
   EXPECT_EQ(count, arr.size());
}

TEST(PalettedVector, DirectLoop)
{
   std::array<int, 128> arr{};
   std::iota(arr.begin(), arr.end(), 0);

   PalettedVector<int, 5> values(arr.begin(), arr.end());
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Direct);

   int count = 0;
   int num = 0;
   for (auto value : values) {
      EXPECT_EQ(value, num++);
      ++count;
   }
   EXPECT_EQ(count, arr.size());
}

TEST(PalettedVector, VerifyRawCount)
{
   std::array<int, 4096> arr{};
   for (auto &value : arr) {
      value = rand() % 8;
   }

   PalettedVector<int, 9> values(arr.begin(), arr.end());
   EXPECT_EQ(values.type(), minecpp::container::PaletteType::Indirect);

   EXPECT_EQ(values.indices().raw().size(), 256);
}
