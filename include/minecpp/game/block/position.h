#pragma once
#include <cstdint>
#include <mb/int.h>
#include <minecpp/util/vec.h>

namespace minecpp::game::block {

constexpr int64_t chunk_max_z = 1875060;

struct Position;

struct ChunkPos
{
   int x = 0, z = 0;
   ChunkPos() = default;
   ChunkPos(int x, int z);
   explicit ChunkPos(minecpp::util::Vec2 v);
   ChunkPos operator+(ChunkPos &other) const;
   [[nodiscard]] constexpr std::uint64_t hash() const
   {
      return static_cast<int64_t>(z) + chunk_max_z * static_cast<int64_t>(x);
   }
   [[nodiscard]] Position block_at(int bx, int by, int bz) const;
   [[nodiscard]] bool is_block_inside(int bx, int bz) const;
};

bool operator==(const ChunkPos &a, const ChunkPos &b);

struct Position
{
   int x = 0, y = 0, z = 0;

   Position() = default;
   Position(int x, int y, int z);
   explicit Position(int64_t value);
   uint64_t as_long() const;
   [[nodiscard]] ChunkPos chunk_pos() const;
   [[nodiscard]] uint16_t offset() const;
   [[nodiscard]] constexpr mb::u8 offset_x() const { return x & 15; }
   [[nodiscard]] constexpr mb::u8 offset_z() const { return z & 15; }
};

}// namespace minecpp::game::block