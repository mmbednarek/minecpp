#pragma once
#include <mb/int.h>
#include <minecpp/proto/common/v1/common.pb.h>
#include <minecpp/util/vec.h>

namespace minecpp::game {

using ChunkHash = mb::u64;

constexpr ChunkHash g_chunk_max_z = 1875060;
constexpr int g_chunk_width = 16;
constexpr int g_chunk_depth = 16;

constexpr mb::u32 g_block_position_x_bits = 26;
constexpr mb::u32 g_block_position_y_bits = 64 - 26 - 26;
constexpr mb::u32 g_block_position_z_bits = 26;

constexpr mb::u64 g_block_position_mask_x = (1u << g_block_position_x_bits) - 1;
constexpr mb::u64 g_block_position_mask_y = (1u << g_block_position_y_bits) - 1;
constexpr mb::u64 g_block_position_mask_z = (1u << g_block_position_z_bits) - 1;

constexpr mb::u32 g_block_position_bit_offset_x = g_block_position_y_bits + g_block_position_x_bits;
constexpr mb::u32 g_block_position_bit_offset_z = g_block_position_y_bits;

struct BlockPosition {
   int x{}, y{}, z{};

   constexpr BlockPosition() = default;

   constexpr BlockPosition(int x, int y, int z) : x(x), y(y), z(z) {}

   [[nodiscard]] constexpr mb::u64 as_long() const {
      return ((static_cast<mb::u64>(x) & g_block_position_mask_x) << g_block_position_bit_offset_x) | (static_cast<mb::u64>(y) & g_block_position_mask_y) |
             ((static_cast<mb::u64>(z) & g_block_position_mask_z) << g_block_position_bit_offset_z);
   }

   static constexpr BlockPosition from_proto(const proto::common::v1::BlockPosition &position) {
      return BlockPosition(position.x(), position.y(), position.z());
   }
};

using BlockState = mb::u32;

struct ChunkPosition {
   int x{}, z{};

   constexpr ChunkPosition() = default;

   constexpr ChunkPosition(int x, int z) : x(x), z(z) {}

   constexpr explicit ChunkPosition(const util::Vec2 &v) : x(static_cast<int>(v.x)),
                                                           z(static_cast<int>(v.z)) {}

   [[nodiscard]] constexpr ChunkPosition operator+(const ChunkPosition &other) const {
      return ChunkPosition(x + other.x, z + other.z);
   }

   [[nodiscard]] constexpr ChunkHash hash() const {
      return static_cast<ChunkHash>(z) + g_chunk_max_z * static_cast<ChunkHash>(x);
   }

   [[nodiscard]] constexpr BlockPosition block_at(int block_x, int block_y, int block_z) const {
      return BlockPosition(x * g_chunk_width + block_x, block_y, z * g_chunk_depth + block_z);
   }

   [[nodiscard]] constexpr bool is_block_inside(int block_x, int block_z) const {
      const auto left = g_chunk_width * x;
      const auto right = g_chunk_width * (x + 1);
      const auto bottom = g_chunk_depth * z;
      const auto top = g_chunk_depth * (z + 1);
      return block_x >= left && block_x < right && block_z >= bottom && block_z < top;
   }

   static constexpr ChunkPosition from_position(const util::Vec3 &v) {
      return ChunkPosition((v.flat() / util::Vec2(g_chunk_width, g_chunk_depth)).truncate());
   }
};

}// namespace minecpp::game