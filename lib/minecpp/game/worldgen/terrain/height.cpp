#include <minecpp/game/worldgen/terrain/height.h>

namespace Game::WorldGen::Terrain {

HeightGenerator::HeightGenerator(uint64_t seed) : rand(seed), base_perlin(rand), perlin_det_amp(rand), perlin_detail0(rand, 0.8, 1.3), perlin_detail1(rand, 0.9, 1.5) {
}

short HeightGenerator::at(int x, int z) {
   double result = 70.0;
   auto perlin_pos = Utils::Vec2(x, z);

   result += base_perlin.at(perlin_pos / 128.0) * 64;
   result += perlin_detail0.at(perlin_pos / 80.0 + Utils::Vec2(0.1, 0.3)) * 120;
   result += perlin_detail1.at(perlin_pos / 20.0 + Utils::Vec2(0.6, 0.32)) * 28;

   return static_cast<short>(result);
}

}// namespace Game::WorldGen
