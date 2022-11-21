#include <array>
#include <gtest/gtest.h>
#include <minecpp/container/TightVector.h>

using minecpp::container::TightVector;

TEST(TightVector, MinBitsToEncode)
{
   ASSERT_EQ(TightVector::min_bits_to_encode(0), 1);
   ASSERT_EQ(TightVector::min_bits_to_encode(1), 1);
   ASSERT_EQ(TightVector::min_bits_to_encode(2), 2);
   ASSERT_EQ(TightVector::min_bits_to_encode(3), 2);
   ASSERT_EQ(TightVector::min_bits_to_encode(4), 3);
   ASSERT_EQ(TightVector::min_bits_to_encode(723), 10);
}

TEST(TightVector, EncodingRegular)
{
   std::array<int, 16> data{3, 1, 4, 1, 5, 9, 2, 1, 1, 2, 9, 5, 1, 4, 1, 3};
   TightVector encoded{8, data.begin(), data.end()};

   ASSERT_EQ(encoded.raw()[0], 0x0102090501040103);
   ASSERT_EQ(encoded.raw()[1], 0x0301040105090201);

   auto at = encoded.begin();
   for (mb::u32 i{0}; i < 16; ++i) {
      ASSERT_EQ(encoded[i], data[i]);
      ASSERT_EQ(*at, data[i]);
      ++at;
   }

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = encoded.begin()](int value) mutable { return value == *(at++); }));
}

TEST(TightVector, EncodingNonRegular)
{
   std::array<int, 16> data{3, 1, 4, 1, 5, 9, 2, 1, 1, 2, 9, 5, 1, 4, 1, 3};
   TightVector encoded(9, data.begin(), data.end());

   auto at = encoded.begin();
   for (mb::u32 i{0}; i < 16; ++i) {
      ASSERT_EQ(encoded[i], data[i]);
      ASSERT_EQ(*at, data[i]);
      ++at;
   }

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = encoded.begin()](int value) mutable { return value == *(at++); }));
}

TEST(TightVector, EncodingAuto)
{
   std::array<int, 16> data{3, 1, 4, 1, 5, 9, 2, 1, 1, 2, 9, 5, 1, 4, 1, 754};
   TightVector encoded{data.begin(), data.end()};

   ASSERT_EQ(encoded.bits(), 10);

   auto at = encoded.begin();
   for (mb::u32 i{0}; i < 16; ++i) {
      ASSERT_EQ(encoded[i], data[i]);
      ASSERT_EQ(*at, data[i]);
      ++at;
   }

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = encoded.begin()](int value) mutable { return value == *(at++); }));

   encoded.increase_bits();

   ASSERT_EQ(encoded.bits(), 11);

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = encoded.begin()](int value) mutable { return value == *(at++); }));
}

TEST(TightVector, PushBack)
{
   std::array<int, 16> data{3, 1, 4, 1, 5, 9, 2, 1, 1, 2, 9, 5, 1, 4, 1, 754};
   TightVector encoded{data.begin(), data.end() - 1};

   encoded.push_back(754);

   ASSERT_EQ(encoded.bits(), 10);

   auto at = encoded.begin();
   for (mb::u32 i{0}; i < 16; ++i) {
      ASSERT_EQ(encoded[i], data[i]);
      ASSERT_EQ(*at, data[i]);
      ++at;
   }

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = encoded.begin()](int value) mutable { return value == *(at++); }));

   encoded.increase_bits();

   ASSERT_EQ(encoded.bits(), 11);

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = encoded.begin()](int value) mutable { return value == *(at++); }));
}

TEST(TightVector, PushBack2)
{
   std::array<int, 16> data{3, 1, 4, 1, 5, 9, 2, 1, 1, 2, 9, 5, 1, 4, 1, 754};
   TightVector encoded{};

   for (auto value : data) {
      encoded.push_back(value);
   }

   ASSERT_EQ(encoded.bits(), 10);

   auto at = encoded.begin();
   for (mb::u32 i{0}; i < 16; ++i) {
      ASSERT_EQ(encoded[i], data[i]);
      ASSERT_EQ(*at, data[i]);
      ++at;
   }

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = encoded.begin()](int value) mutable { return value == *(at++); }));

   encoded.increase_bits();

   ASSERT_EQ(encoded.bits(), 11);

   ASSERT_TRUE(std::all_of(data.begin(), data.end(),
                           [at = encoded.begin()](int value) mutable { return value == *(at++); }));
}
