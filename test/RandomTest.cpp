#include <gtest/gtest.h>
#include <minecpp/random/JavaRandom.h>
#include <minecpp/random/Perlin.h>
#include <minecpp/random/Perlin3d.h>

TEST(Rand, JavaRandom)
{
   minecpp::random::JavaRandom r(1234);
   int v;
   v = r.next_int(12);
   ASSERT_EQ(v, 8);
   v = r.next_int(34);
   ASSERT_EQ(v, 23);
   v = r.next_int(67);
   ASSERT_EQ(v, 29);
}

TEST(Rand, JavaRandomTwins)
{
   minecpp::random::JavaRandom a(2151901553968352745);
   minecpp::random::JavaRandom b(8091867987493326313);
   for (int i = 0; i < 256; ++i) {
      ASSERT_EQ(a.next_int(), b.next_int());
   }
}

static char level_to_char(double v)
{
   if (v >= 1.9) {
      return '@';
   }
   if (v > 1.75) {
      return '%';
   }
   if (v > 1.5) {
      return '#';
   }
   if (v > 1.25) {
      return '*';
   }
   if (v > 1.0) {
      return '+';
   }
   if (v > 0.75) {
      return '=';
   }
   if (v > 0.6) {
      return '-';
   }
   if (v > 0.4) {
      return ':';
   }
   if (v > 0.2) {
      return ':';
   }
   return ' ';
}

TEST(Rand, Perlin)
{
   minecpp::random::JavaRandom rand(8091867987493326313);
   minecpp::random::Perlin perlin(rand);

   double avg = 0.0;
   double min = 1000;
   double max = -1000;
   int count  = 0;

   for (double z = 0.0; z <= 16.0; z += 0.1) {
      for (double x = 0.0; x <= 16.0; x += 0.1) {
         auto value = perlin.at(minecpp::util::Vec2(z, x)) * 4 + 1;
         ++count;
         avg += value;
         if (value < min) {
            min = value;
         }
         if (value > max) {
            max = value;
         }
         std::cerr << level_to_char(value);
      }
      std::cerr << '\n';
   }

   avg /= count;

   std::cerr << "avg: " << avg << '\n';
   std::cerr << "min: " << min << '\n';
   std::cerr << "max: " << max << '\n';
}

TEST(Rand, Perlin3d)
{
   minecpp::random::JavaRandom rand(8091867987493326313);
   minecpp::random::Perlin3d perlin(rand);

   for (double z = 0.0; z <= 16.0; z += 0.1) {
      for (double x = 0.0; x <= 16.0; x += 0.1) {
         auto value = perlin.at(minecpp::util::Vec3(x, 0.2, z)) * 4 + 1;
         std::cerr << level_to_char(value);
      }
      std::cerr << '\n';
   }
}

TEST(Rand, DisplacedPerlin)
{
   minecpp::random::JavaRandom rand(8091867987493326313);
   minecpp::random::DisplacedPerlin perlin(rand, 2.0, 1.0);
   for (double z = 0.0; z <= 16.0; z += 0.1) {
      for (double x = 0.0; x <= 16.0; x += 0.1) {
         auto value = perlin.at(minecpp::util::Vec2(x, z) / 16.0) + 1;
         std::cerr << level_to_char(value);
      }
      std::cerr << '\n';
   }
}
