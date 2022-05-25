#include <cmath>
#include <minecpp/random/java_random.h>
#include <minecpp/random/perlin3d.h>

namespace minecpp::random {

using minecpp::util::Vec3;

Perlin3d::Perlin3d(Random &rand) :
    rand(rand),
    coef1(rand.next_int()),
    coef2(rand.next_int()),
    coef3(rand.next_int()),
    coef4(rand.next_int())
{
}

[[nodiscard]] static double smooth(const double t) { return t * t * t * (t * (t * 6 - 15) + 10); }

double Perlin3d::at(minecpp::util::Vec3 pos)
{
   Vec3 floored_pos(pos.truncate());
   auto left = static_cast<int>(floored_pos.x);
   auto top  = static_cast<int>(floored_pos.y);
   auto far  = static_cast<int>(floored_pos.z);
   int right = left + 1, bot = top + 1, close = far + 1;

   Vec3 weight(smooth(pos.x - floored_pos.x), smooth(pos.y - floored_pos.y), smooth(pos.z - floored_pos.z));

   auto top_left_far  = dot_grad(left, top, far, pos);
   auto top_right_far = dot_grad(right, top, far, pos);
   auto inter_top_far = std::lerp(top_left_far, top_right_far, weight.x);

   auto bot_left_far  = dot_grad(left, bot, far, pos);
   auto bot_right_far = dot_grad(right, bot, far, pos);
   auto inter_bot_far = std::lerp(bot_left_far, bot_right_far, weight.x);

   auto inter_far = std::lerp(inter_top_far, inter_bot_far, weight.y);

   auto top_left_close  = dot_grad(left, top, close, pos);
   auto top_right_close = dot_grad(right, top, close, pos);
   auto inter_top_close = std::lerp(top_left_close, top_right_close, weight.x);

   auto bot_left_close  = dot_grad(left, bot, close, pos);
   auto bot_right_close = dot_grad(right, bot, close, pos);
   auto inter_bot_close = std::lerp(bot_left_close, bot_right_close, weight.x);

   auto inter_close = std::lerp(inter_top_close, inter_bot_close, weight.y);

   return std::lerp(inter_far, inter_close, weight.z);
}

minecpp::util::Vec3 Perlin3d::grad(int x, int y, int z)
{
   random::JavaRandom r(x * coef1 + y * coef2 + z * coef3 + coef4);
   return minecpp::util::Vec3(r.next_double(), r.next_double(), r.next_double());
}

double Perlin3d::dot_grad(int x, int y, int z, minecpp::util::Vec3 pos)
{
   auto g = grad(x, y, z);
   auto d = pos - Vec3(x, y, z);
   return (g.x * d.x) + (g.y * d.y) + (g.z * d.z);
}

}// namespace minecpp::random
