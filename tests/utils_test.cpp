#include <any>
#include <error/result.h>
#include <gtest/gtest.h>
#include <mineutils/format.h>
#include <mineutils/random.h>

TEST(Utils, Format) {
   auto empty_format = Utils::format("Hello!");
   ASSERT_EQ(empty_format, "Hello!");
   auto format_one = Utils::format("Hello {}!", "World");
   ASSERT_EQ(format_one, "Hello World!");
   auto format_many = Utils::format("Many values {}, {}, {}.", "something", 14, 23.567);
   ASSERT_EQ(format_many, "Many values something, 14, 23.567.");
}

TEST(Utils, Random) {
   Utils::Random r(1234);
   int v;
   v = r.next_int(12);
   ASSERT_EQ(v, 8);
   v = r.next_int(34);
   ASSERT_EQ(v, 23);
   v = r.next_int(67);
   ASSERT_EQ(v, 29);
}


TEST(Utils, RandomTwins) {
   Utils::Random a(2151901553968352745);
   Utils::Random b(8091867987493326313);
   for (int i = 0; i < 256; ++i) {
      ASSERT_EQ(a.next_int(), b.next_int());
   }
}

TEST(Utils, result) {
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