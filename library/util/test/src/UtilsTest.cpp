#include <any>
#include <gtest/gtest.h>
#include <minecpp/util/Loop.h>
#include <minecpp/util/Packed.h>
#include <minecpp/util/StaticQueue.h>
#include <thread>

TEST(minecpp_util, PackingTest)
{
   std::uint32_t i{};
   auto data = minecpp::util::generate_packed(12, 4096, [&i]() -> uint32_t { return i++; });

   i = 0;
   minecpp::util::for_each_packed(data, 12, 4096, [&i](uint32_t v) { ASSERT_EQ(v, i++); });
}

TEST(minecpp_util, Around)
{
   char values[9];
   memset(values, 0, sizeof(char) * 9);

   minecpp::util::around(1, 1, [&values](int x, int z) { values[z * 3 + x] = 1; });

   ASSERT_EQ(values[4], 0);
   for (int x = 0; x < 4; ++x) {
      ASSERT_EQ(values[x], 1);
   }
   for (int x = 5; x < 9; ++x) {
      ASSERT_EQ(values[x], 1);
   }
}

TEST(minecpp_util, StaticQueue)
{
   minecpp::util::StaticQueue<int, 5> queue;

   std::thread t1([&queue]() {
      for (int i = 0; i < 100; ++i) {
         queue.push(i);
      }
   });

   for (int i = 0; i < 100; ++i) {
      ASSERT_EQ(queue.pop(), i);
   }

   t1.join();
}