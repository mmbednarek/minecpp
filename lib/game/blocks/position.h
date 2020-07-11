#pragma once
#include <cstdint>
#include <mineutils/vec.h>

namespace Game::Block {

struct ChunkPos {
   int x = 0, z = 0;
   ChunkPos() = default;
   ChunkPos(int x, int z);
   explicit ChunkPos(Utils::Vec2 v);
   ChunkPos operator+(ChunkPos &other) const;
};

bool operator==(const ChunkPos &a, const ChunkPos &b);

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