#pragma once
#include <cstdint>
#include <minecpp/random/mersenne.h>
#include <minecpp/random/perlin.h>

namespace Game::WorldGen::Terrain {

class HeightGenerator {
   Rand::Mersenne rand;
   Rand::Perlin base_perlin;
   Rand::Perlin perlin_det_amp;
   Rand::DisplacedPerlin perlin_detail0;
   Rand::DisplacedPerlin perlin_detail1;

 public:
   explicit HeightGenerator(uint64_t seed);

   short at(int x, int z);
};

}// namespace Game::WorldGen