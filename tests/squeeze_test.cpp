#include <gtest/gtest.h>
#include<squeeze/vector.h>

TEST(Squeeze, vec) {
   auto gen_vec = [](std::size_t size) -> std::vector<int> {
      std::vector<int> result(size);
      std::generate(result.begin(), result.end(), [i = 0]() mutable {
         return i++;
      });
      return result;
   };

   for (int s = 5; s < 20; ++s) {
      Squeeze::Vector vec(5, gen_vec(s));

      ASSERT_EQ(vec.size(), s);

      for (int bits = 5; bits < 17; ++bits) {
         for (int i = 0; i < s; ++i) {
            ASSERT_EQ(vec.at(i), i);
         }

         std::for_each(vec.begin(), vec.end(), [i = 0](std::int32_t val) mutable {
           ASSERT_EQ(val, i);
           i++;
         });

         vec.inc_bits();
      }
   }
}
TEST(Squeeze, set_test) {
   auto gen_vec = [](std::size_t size) -> std::vector<int> {
     std::vector<int> result(size);
     std::generate(result.begin(), result.end(), [i = 0]() mutable {
       return i++;
     });
     return result;
   };

   Squeeze::Vector vec(4, gen_vec(5));
   vec.set(2, 300);
   ASSERT_EQ(vec.bits(), 9);
}
