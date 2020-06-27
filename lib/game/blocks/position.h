#pragma once
#include <cstdint>

namespace Game::Block {

struct ChunkPos {
   int x = 0, z = 0;
};

struct Position {
   int x = 0, y = 0, z = 0;

   Position() = default;
   Position(int x, int y, int z);
   explicit Position(int64_t value);
   uint64_t as_long();
   [[nodiscard]] ChunkPos chunk_pos() const;
   [[nodiscard]] uint16_t offset() const;
   [[nodiscard]] uint8_t offset_x() const;
   [[nodiscard]] uint8_t offset_z() const;
};

} // namespace Game::Block