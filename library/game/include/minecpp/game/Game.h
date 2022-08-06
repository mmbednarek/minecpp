#pragma once
#include <mb/enum.h>
#include <mb/int.h>
#include <minecpp/proto/common/v1/Common.pb.h>
#include <minecpp/util/Uuid.h>
#include <minecpp/util/Vec.h>
#include <optional>
#include <string_view>

namespace minecpp::game {

using ChunkHash    = mb::u64;
using SlotId       = mb::u32;
using PlayerId     = util::uuid;
using BlockId      = mb::i32;
using EntityId     = mb::u32;
using BlockStateId = mb::u32;
using LightLevel   = mb::u8;
using StateOffset  = mb::i32;
using ItemId       = mb::i32;

constexpr ChunkHash g_chunk_max_z = 1875060;
constexpr int g_chunk_width       = 16;
constexpr int g_chunk_depth       = 16;
constexpr int g_section_height    = 16;

constexpr mb::u32 g_block_position_x_bits = 26;
constexpr mb::u32 g_block_position_y_bits = 64 - 26 - 26;
constexpr mb::u32 g_block_position_z_bits = 26;

constexpr mb::u64 g_block_position_mask_x = (1u << g_block_position_x_bits) - 1;
constexpr mb::u64 g_block_position_mask_y = (1u << g_block_position_y_bits) - 1;
constexpr mb::u64 g_block_position_mask_z = (1u << g_block_position_z_bits) - 1;

constexpr mb::u32 g_block_position_bit_offset_x = g_block_position_y_bits + g_block_position_x_bits;
constexpr mb::u32 g_block_position_bit_offset_z = g_block_position_y_bits;

struct ChunkPosition;

enum class PlayerDiggingState : int
{
   Digging         = 0,
   CanceledDigging = 1,
   FinishedDigging = 2,
   DropAllItems    = 3,
   DropItem        = 4,
   ReleaseUseItem  = 5,
   SwapHeldItems   = 6,
};

enum class FaceValue
{
   Bottom = 0,
   Top    = 1,
   North  = 2,
   South  = 3,
   West   = 4,
   East   = 5,
};

using Face_Base = mb::enum_wrapper<FaceValue, "bottom", "top", "north", "south", "west", "east">;

class Face final : public Face_Base
{
 public:
   MB_ENUM_TRAITS(Face)

   MB_ENUM_FIELD(Bottom)
   MB_ENUM_FIELD(Top)
   MB_ENUM_FIELD(North)
   MB_ENUM_FIELD(South)
   MB_ENUM_FIELD(West)
   MB_ENUM_FIELD(East)

   static constexpr Face from_proto(const proto::common::v1::Face face)
   {
      return Face{static_cast<FaceValue>(face)};
   }

   constexpr proto::common::v1::Face to_proto()
   {
      return static_cast<proto::common::v1::Face>(index());
   }

   [[nodiscard]] constexpr Face opposite_face()
   {
      switch (index()) {
      case Face::Bottom: return Face::Top;
      case Face::Top: return Face::Bottom;
      case Face::North: return Face::South;
      case Face::South: return Face::North;
      case Face::West: return Face::East;
      case Face::East: return Face::West;
      }
      assert(false && "SHOULD NOT BE REACHED");
   }
};

enum class SideValue
{
   Left,
   Right
};

using Side_Base = mb::enum_wrapper<SideValue, "left", "right">;

class Side final : public Side_Base
{
 public:
   MB_ENUM_TRAITS(Side);

   MB_ENUM_FIELD(Left)
   MB_ENUM_FIELD(Right)
};

[[nodiscard]] inline std::string to_string(Side side)
{
   switch (side) {
   case Side::Left: return "left";
   case Side::Right: return "right";
   }
   return "";
}

constexpr int decode_x(mb::u64 pos)
{
   auto x = pos >> 38;
   if (x >= (1u << 25)) {
      return static_cast<int>(static_cast<mb::i64>(x) - (1 << 26));
   }
   return static_cast<int>(x);
}

constexpr int decode_y(mb::u64 pos)
{
   auto y = pos & 0xFFF;
   if (y >= (1u << 11)) {
      return static_cast<int>(static_cast<mb::i64>(y) - (1 << 12));
   }
   return static_cast<int>(y);
}

constexpr int decode_z(mb::u64 pos)
{
   auto z = (pos >> 12) & 0x3FFFFFF;
   if (z >= (1u << 25)) {
      return static_cast<int>(static_cast<mb::i64>(z) - (1 << 26));
   }
   return static_cast<int>(z);
}

struct BlockPosition
{
   int x{}, y{}, z{};

   constexpr BlockPosition() = default;

   constexpr BlockPosition(int x, int y, int z) :
       x(x),
       y(y),
       z(z)
   {
   }

   constexpr explicit BlockPosition(mb::u64 encoded) :
       x(decode_x(encoded)),
       y(decode_y(encoded)),
       z(decode_z(encoded))
   {
      if (x > 33554431) {
         x = 67108862 - x;
      }
      if (z > 33554431) {
         z = 67108862 - z;
      }
   }

   [[nodiscard]] constexpr mb::u64 as_long() const
   {
      auto lx = x >= 0 ? static_cast<mb::u64>(x) : static_cast<mb::u64>(static_cast<mb::i64>(x) + (1 << 26));
      auto ly = y >= 0 ? static_cast<mb::u64>(y) : static_cast<mb::u64>(static_cast<mb::i64>(y) + (1 << 12));
      auto lz = z >= 0 ? static_cast<mb::u64>(z) : static_cast<mb::u64>(static_cast<mb::i64>(z) + (1 << 26));
      return ((lx & g_block_position_mask_x) << g_block_position_bit_offset_x) |
             (ly & g_block_position_mask_y) |
             ((lz & g_block_position_mask_z) << g_block_position_bit_offset_z);
   }

   static inline BlockPosition from_proto(const proto::common::v1::BlockPosition &position)
   {
      return {position.x(), position.y(), position.z()};
   }

   [[nodiscard]] constexpr ChunkPosition chunk_position() const;

   [[nodiscard]] constexpr mb::u8 offset_x() const
   {
      return x & (g_chunk_width - 1);
   }

   [[nodiscard]] constexpr mb::u8 section_offset_y() const
   {
      return y & (g_section_height - 1);
   }

   [[nodiscard]] constexpr mb::u8 offset_z() const
   {
      return z & (g_chunk_depth - 1);
   }

   [[nodiscard]] constexpr mb::u16 offset() const
   {
      return static_cast<mb::u16>(offset_x() << 12u | y | offset_z() << 8u);
   }

   [[nodiscard]] constexpr mb::u32 offset_within_section() const
   {
      return (static_cast<mb::u32>(section_offset_y()) << 8) | (static_cast<mb::u32>(offset_z()) << 4) |
             static_cast<mb::u32>(offset_x());
   }

   [[nodiscard]] inline proto::common::v1::BlockPosition to_proto() const
   {
      proto::common::v1::BlockPosition block_position;
      block_position.set_x(x);
      block_position.set_y(y);
      block_position.set_z(z);
      return block_position;
   }

   [[nodiscard]] constexpr BlockPosition neighbour_at(Face facing) const
   {
      switch (facing) {
      case Face::Bottom: return {x, y - 1, z};
      case Face::Top: return {x, y + 1, z};
      case Face::North: return {x, y, z - 1};
      case Face::South: return {x, y, z + 1};
      case Face::West: return {x - 1, y, z};
      case Face::East: return {x + 1, y, z};
      }
      return {x, y, z};
   }

   [[nodiscard]] constexpr util::Vec3 to_vec3()
   {
      return {static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)};
   }
};

[[nodiscard]] inline BlockStateId block_state_from_proto(const proto::common::v1::BlockState &state)
{
   return static_cast<BlockStateId>(state.block_state());
}

[[nodiscard]] inline proto::common::v1::BlockState block_state_to_proto(BlockStateId state)
{
   proto::common::v1::BlockState proto;
   proto.set_block_state(state);
   return proto;
}

struct ChunkPosition
{
   int x{}, z{};

   constexpr ChunkPosition() = default;

   constexpr ChunkPosition(int x, int z) :
       x(x),
       z(z)
   {
   }

   constexpr explicit ChunkPosition(const util::Vec2 &v) :
       x(static_cast<int>(v.x)),
       z(static_cast<int>(v.z))
   {
   }

   [[nodiscard]] constexpr ChunkPosition operator+(const ChunkPosition &other) const
   {
      return {x + other.x, z + other.z};
   }

   [[nodiscard]] constexpr ChunkHash hash() const
   {
      return static_cast<ChunkHash>(z) + g_chunk_max_z * static_cast<ChunkHash>(x);
   }

   [[nodiscard]] constexpr BlockPosition block_at(int block_x, int block_y, int block_z) const
   {
      return {x * g_chunk_width + block_x, block_y, z * g_chunk_depth + block_z};
   }

   [[nodiscard]] constexpr bool is_block_inside(int block_x, int block_z) const
   {
      const auto left   = g_chunk_width * x;
      const auto right  = g_chunk_width * (x + 1);
      const auto bottom = g_chunk_depth * z;
      const auto top    = g_chunk_depth * (z + 1);
      return block_x >= left && block_x < right && block_z >= bottom && block_z < top;
   }

   static inline ChunkPosition from_position(const util::Vec3 &v)
   {
      return ChunkPosition((v.flat() / util::Vec2(g_chunk_width, g_chunk_depth)).truncate());
   }

   [[nodiscard]] inline proto::common::v1::ChunkPosition to_proto() const
   {
      proto::common::v1::ChunkPosition result;
      result.set_x(x);
      result.set_z(z);
      return result;
   }
};

constexpr ChunkPosition BlockPosition::chunk_position() const
{
   return {x >= 0 ? (x / g_chunk_width) : ((x + 1) / g_chunk_width - 1),
           z >= 0 ? (z / g_chunk_depth) : ((z + 1) / g_chunk_depth - 1)};
}

enum class WoodType
{
   Oak,
   Spruce,
   Birch,
   Jungle,
   Acacia,
   DarkOak,
   Mangrove
};

constexpr std::array<WoodType, 7> g_wood_types{WoodType::Oak,     WoodType::Spruce, WoodType::Birch,
                                               WoodType::Jungle,  WoodType::Acacia, WoodType::DarkOak,
                                               WoodType::Mangrove};

[[nodiscard]] constexpr std::string_view to_string(WoodType wood_type)
{
   switch (wood_type) {
   case WoodType::Oak: return "oak";
   case WoodType::Spruce: return "spruce";
   case WoodType::Birch: return "birch";
   case WoodType::Jungle: return "jungle";
   case WoodType::Acacia: return "acacia";
   case WoodType::DarkOak: return "dark_oak";
   case WoodType::Mangrove: return "mangrove";
   }
   return "";
}

enum class DirectionValues
{
   East,
   West,
   South,
   North
};

using Direction_Base = mb::enum_wrapper<DirectionValues, "east", "west", "south", "north">;

class Direction final : public Direction_Base
{
 public:
   MB_ENUM_TRAITS(Direction);

   MB_ENUM_FIELD(East)
   MB_ENUM_FIELD(West)
   MB_ENUM_FIELD(South)
   MB_ENUM_FIELD(North)

   [[nodiscard]] constexpr Direction turn(Side side) const
   {
      if (side == Side::Left) {
         switch (index()) {
         case Direction::North: return Direction::West;
         case Direction::South: return Direction::East;
         case Direction::West: return Direction::South;
         case Direction::East: return Direction::North;
         }
      } else {
         switch (index()) {
         case Direction::North: return Direction::East;
         case Direction::South: return Direction::West;
         case Direction::West: return Direction::North;
         case Direction::East: return Direction::South;
         }
      }

      assert(false && "not reachable");
   }

   [[nodiscard]] constexpr Face to_face()
   {
      switch (index()) {
      case Direction::North: return Face::North;
      case Direction::South: return Face::South;
      case Direction::West: return Face::West;
      case Direction::East: return Face::East;
      }
      assert(false && "not reachable");
   }
};

[[nodiscard]] constexpr Direction opposite_direction(Direction direction)
{
   switch (direction) {
   case Direction::East: return Direction::West;
   case Direction::West: return Direction::East;
   case Direction::South: return Direction::North;
   case Direction::North: return Direction::South;
   }
   return Direction::West;
}

[[nodiscard]] constexpr std::optional<Face> direction_to_face(Direction direction)
{
   switch (direction) {
   case Direction::North: return Face::North;
   case Direction::South: return Face::South;
   case Direction::West: return Face::West;
   case Direction::East: return Face::East;
   }
   return std::nullopt;
}

[[nodiscard]] constexpr std::string_view to_string(Direction direction)
{
   switch (direction) {
   case Direction::West: return "west";
   case Direction::East: return "east";
   case Direction::South: return "south";
   case Direction::North: return "north";
   }
   return "";
}

[[nodiscard]] constexpr std::optional<Direction> direction_at(Direction dir, Side side)
{
   if (side == Side::Left) {
      switch (dir) {
      case Direction::North: return Direction::West;
      case Direction::South: return Direction::East;
      case Direction::West: return Direction::South;
      case Direction::East: return Direction::North;
      }

      return std::nullopt;
   }

   switch (dir) {
   case Direction::North: return Direction::East;
   case Direction::South: return Direction::West;
   case Direction::West: return Direction::North;
   case Direction::East: return Direction::South;
   }

   return std::nullopt;
}

[[nodiscard]] constexpr Direction direction_from_vec2(const util::Vec2 &vec)
{
   bool x_dominant = std::abs(vec.x) > std::abs(vec.z);
   if (x_dominant) {
      if (vec.x > 0.0)
         return Direction::East;
      return Direction::West;
   }

   if (vec.z > 0.0)
      return Direction::South;
   return Direction::North;
}

enum class LightType
{
   Block,
   Sky
};

enum class HalfValue
{
   Lower,
   Upper
};

using Half_Base = mb::enum_wrapper<HalfValue, "lower", "upper">;

class Half final : public Half_Base
{
 public:
   MB_ENUM_TRAITS(Half);

   MB_ENUM_FIELD(Lower)
   MB_ENUM_FIELD(Upper)
};

}// namespace minecpp::game
