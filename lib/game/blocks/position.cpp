#include "position.h"

namespace Game::Block {

constexpr uint32_t num_x_bits = 26;
constexpr uint32_t num_y_bits = 64 - 26 - 26;
constexpr uint32_t num_z_bits = 26;

constexpr uint64_t mask_x = (1u << num_x_bits) - 1;
constexpr uint64_t mask_y = (1u << num_y_bits) - 1;
constexpr uint64_t mask_z = (1u << num_z_bits) - 1;

constexpr uint32_t bit_offset_x = num_y_bits + num_x_bits;
constexpr uint32_t bit_offset_z = num_y_bits;

Position::Position(int x, int y, int z) : x(x), y(y), z(z) {}

static_assert(-2 >> 1 == -1, "compiler does not support arithmetic shift");

Position::Position(int64_t value)
    : x(value >> (num_z_bits + num_y_bits)), y(value << (num_x_bits + num_z_bits) >> (num_x_bits + num_z_bits)),
      z(value << num_x_bits >> (num_x_bits + num_y_bits)) {}

uint64_t Position::as_long() const {
   return ((static_cast<uint64_t>(x) & mask_x) << bit_offset_x) | (static_cast<uint64_t>(y) & mask_y) |
          ((static_cast<uint64_t>(z) & mask_z) << bit_offset_z);
}

ChunkPos Position::chunk_pos() const {
   return ChunkPos(x >= 0 ? (x / 16) : ((x + 1) / 16 - 1), z >= 0 ? (z / 16) : ((z + 1) / 16 - 1));
}

uint16_t Position::offset() const { return offset_x() << 12 | y | offset_z() << 8; }

inline uint8_t Position::offset_x() const { return x & 15; }
inline uint8_t Position::offset_z() const { return z & 15; }

bool operator==(const ChunkPos &a, const ChunkPos &b) { return a.x == b.x && a.z == b.z; }

ChunkPos ChunkPos::operator+(ChunkPos &other) const { return ChunkPos{x + other.x, z + other.z}; }

ChunkPos::ChunkPos(int x, int z) : x(x), z(z) {}

ChunkPos::ChunkPos(Utils::Vec2 v) : x(v.x), z(v.z) {}

Position ChunkPos::block_at(int bx, int by, int bz) const {
   return Position(x * 16 + bx, by, z * 16 + bz);
}

bool ChunkPos::is_block_inside(int bx, int bz) const {
   auto left = 16 * x;
   auto right = 16 * (x + 1);
   auto bottom = 16 * z;
   auto top = 16 * (z + 1);
   return bx >= left && bx < right && bz >= bottom && bz < top;
}

} // namespace Game::Block
