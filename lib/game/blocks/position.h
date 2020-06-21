#pragma once
#include <cstdint>

namespace Game::Block {

struct Position {
   int x = 0, y = 0, z = 0;

   Position() = default;
   Position(int x, int y, int z);
   Position(int64_t value);
   uint64_t as_long();
};

}