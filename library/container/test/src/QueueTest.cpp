#include <future>
#include <gtest/gtest.h>
#include <iostream>
#include <minecpp/container/Queue.h>

TEST(Queue, NoRace_int) {
   using minecpp::container::Queue;

   Queue<int> queue;

   auto producer = [](Queue<int> *queue) {
      for (int i = 1; i <= 1000; ++i) {
         queue->push(i);
      }
   };

   auto consumer = [](Queue<int> *queue) -> int {
      int sum = 0;
      for(;;) {
         using namespace std::chrono_literals;

         auto consumed = queue->try_pop();
         if (not consumed.has_value())
            break;

         sum += *consumed;
         std::this_thread::sleep_for(5ms);
      }

      return sum;
   };

   auto fut_res1 = std::async(std::launch::async, consumer, &queue);
   auto fut_res2 = std::async(std::launch::async, consumer, &queue);

   producer(&queue);

   auto res1 = fut_res1.get();
   auto res2 = fut_res2.get();

   EXPECT_EQ(res1 + res2, (1000 + 1) * 500);
   EXPECT_LE(abs(res2 - res1), 1000);
}

TEST(Queue, NoRace_unique_ptr) {
   using minecpp::container::Queue;

   Queue<std::unique_ptr<int>> queue;

   auto producer = [](Queue<std::unique_ptr<int>> *queue) {
     for (int i = 1; i <= 1000; ++i) {
        queue->push(std::make_unique<int>(i));
     }
   };

   auto consumer = [](Queue<std::unique_ptr<int>> *queue) -> int {
     int sum = 0;
     for(;;) {
        using namespace std::chrono_literals;

        auto consumed = queue->try_pop();
        if (not consumed.has_value())
           break;

        sum += **consumed;
        std::this_thread::sleep_for(5ms);
     }

     return sum;
   };

   auto fut_res1 = std::async(std::launch::async, consumer, &queue);
   auto fut_res2 = std::async(std::launch::async, consumer, &queue);

   producer(&queue);

   auto res1 = fut_res1.get();
   auto res2 = fut_res2.get();

   EXPECT_EQ(res1 + res2, (1000 + 1) * 500);
   EXPECT_LE(abs(res2 - res1), 1000);
}
