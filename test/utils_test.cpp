#include <any>
#include <gtest/gtest.h>
#include <minecpp/error/result.h>
#include <minecpp/util/format.h>
#include <minecpp/util/loop.h>
#include <minecpp/util/packed.h>
#include <minecpp/util/static_queue.h>
#include <thread>

TEST(minecpp_util, Format) {
   auto empty_format = minecpp::util::format("Hello!");
   ASSERT_EQ(empty_format, "Hello!");
   auto format_one = minecpp::util::format("Hello {}!", "World");
   ASSERT_EQ(format_one, "Hello World!");
   auto format_many = minecpp::util::format("Many values {}, {}, {}.", "something", 14, 23.567);
   ASSERT_EQ(format_many, "Many values something, 14, 23.567.");
}

TEST(minecpp_util, result) {
   auto do_stuff = [](int a, int b) -> result<int> {
      if (a == 0) {
         return error("a can't be zero");
      }
      return a * 3 - b * 2;
   };

   auto do_stuff_empty = [](int a) -> result<empty> {
      if (a == 0) {
         return error("a can't be zero");
      }
      return result_ok;
   };

   int c = 3;

   struct Test {
      int a;
      int b;
      int &c;
   };

   auto get_test = [do_stuff, &c](int a, int b) -> result<Test> {
      auto calc_a = tryget(do_stuff(a, b));
      if (b == 0) {
         return error("b can't be zero");
      }
      return Test{
              .a = calc_a,
              .b = b,
              .c = c,
      };
   };

   auto resultEmpty = do_stuff_empty(6);
   ASSERT_TRUE(resultEmpty.ok());
   ASSERT_FALSE(resultEmpty.err());

   auto resultEmptyErr = do_stuff_empty(0);
   ASSERT_FALSE(resultEmptyErr.ok());
   ASSERT_EQ(resultEmptyErr.msg(), "a can't be zero");

   auto result = do_stuff(6, 7);
   ASSERT_TRUE(result.ok());
   ASSERT_EQ(result.unwrap(), 4);
   ASSERT_FALSE(result.err());

   auto res2 = do_stuff(0, 4);
   ASSERT_FALSE(res2.ok());
   ASSERT_EQ(res2.msg(), "a can't be zero");

   auto resTest = get_test(4, 5);
   auto expectTest = Test{.a = 2, .b = 5, .c = c};
   ASSERT_TRUE(resTest.ok());
   auto gotTest = resTest.unwrap();
   ASSERT_EQ(gotTest.a, expectTest.a);
   ASSERT_EQ(gotTest.b, expectTest.b);
   ASSERT_FALSE(resTest.err());

   auto resTest2 = get_test(0, 4);
   ASSERT_FALSE(resTest2.ok());
   ASSERT_EQ(resTest2.msg(), "a can't be zero");

   auto resTest3 = get_test(4, 0);
   ASSERT_FALSE(resTest3.ok());
   ASSERT_EQ(resTest3.msg(), "b can't be zero");
}

TEST(minecpp_util, PackingTest) {
   int i = 0;
   auto data = minecpp::util::generate_packed(12, 4096, [&i]() -> uint32_t { return i++; });

   i = 0;
   minecpp::util::for_each_packed(data, 12, 4096, [&i](uint32_t v) {
      ASSERT_EQ(v, i++);
   });
}

TEST(minecpp_util, Around) {
   char values[9];
   memset(values, 0, sizeof(char) * 9);

   minecpp::util::around(1, 1, [&values](int x, int z) {
      values[z * 3 + x] = 1;
   });

   ASSERT_EQ(values[4], 0);
   for (int x = 0; x < 4; ++x) {
      ASSERT_EQ(values[x], 1);
   }
   for (int x = 5; x < 9; ++x) {
      ASSERT_EQ(values[x], 1);
   }
}

TEST(minecpp_util, StaticQueue) {
   minecpp::util::StaticQueue<int, 5> queue;

   std::thread t1([&queue]() {
      for (int i = 0; i < 100; ++i) {
         queue.push(std::move(i));
      }
   });

   for (int i = 0; i < 100; ++i) {
      ASSERT_EQ(queue.pop(), i);
   }

   t1.join();
}