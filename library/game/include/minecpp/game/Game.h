#pragma once
#include <mb/enum.h>
#include <mb/int.h>
#include <minecpp/math/Vector2.h>
#include <minecpp/math/Vector3.h>
#include <minecpp/nbt/block/v1/BlockState.nbt.h>
#include <minecpp/nbt/common/v1/Common.nbt.h>
#include <minecpp/proto/common/v1/Common.pb.h>
#include <minecpp/proto/entity/v1/Entity.pb.h>
#include <minecpp/util/Uuid.h>
#include <optional>
#include <string_view>

namespace minecpp::game {

using ChunkHash    = mb::u64;
using SlotId       = mb::u32;
using PlayerId     = util::uuid;
using BlockId      = mb::i32;
using EntityId     = mb::u32;
using BlockStateId = mb::u32;
using StateOffset  = mb::i32;
using ItemId       = mb::i32;
using LightValue   = mb::u8;

constexpr ChunkHash g_chunk_max_z = 1875060;
constexpr ChunkHash g_chunk_max_x = 1875060;
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
struct ChunkSectionPosition;

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

enum class FaceMask : mb::u8
{
   None   = 0,
   Bottom = 1u << 0,
   Top    = 1u << 1,
   North  = 1u << 2,
   South  = 1u << 3,
   West   = 1u << 4,
   East   = 1u << 5,
   All    = 0x40u - 1u,
};

// TODO: Introduce common mask traits

inline FaceMask operator|(FaceMask lhs, FaceMask rhs)
{
   return static_cast<FaceMask>(static_cast<std::underlying_type_t<FaceMask>>(lhs) |
                                static_cast<std::underlying_type_t<FaceMask>>(rhs));
}

inline FaceMask operator~(FaceMask source)
{
   return static_cast<FaceMask>((~static_cast<std::underlying_type_t<FaceMask>>(source)) &
                                static_cast<std::underlying_type_t<FaceMask>>(FaceMask::All));
}

inline FaceMask &operator|=(FaceMask &lhs, FaceMask rhs)
{
   lhs = lhs | rhs;
   return lhs;
}

inline FaceMask operator-(FaceMask lhs, FaceMask rhs)
{
   return static_cast<FaceMask>(static_cast<std::underlying_type_t<FaceMask>>(lhs) &
                                static_cast<std::underlying_type_t<FaceMask>>(~rhs));
}

inline bool operator&(FaceMask lhs, FaceMask rhs)
{
   return (static_cast<std::underlying_type_t<FaceMask>>(lhs) &
           static_cast<std::underlying_type_t<FaceMask>>(rhs)) != 0u;
}

inline FaceMask face_mask_from_nbt(const nbt::common::v1::FaceMask &nbt_mask)
{
   FaceMask result{};
   result |= nbt_mask.down ? FaceMask::Bottom : FaceMask::None;
   result |= nbt_mask.up ? FaceMask::Top : FaceMask::None;
   result |= nbt_mask.north ? FaceMask::North : FaceMask::None;
   result |= nbt_mask.south ? FaceMask::South : FaceMask::None;
   result |= nbt_mask.west ? FaceMask::West : FaceMask::None;
   result |= nbt_mask.east ? FaceMask::East : FaceMask::None;
   return result;
}

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
      switch (value()) {
      case Face::Bottom: return Face::Top;
      case Face::Top: return Face::Bottom;
      case Face::North: return Face::South;
      case Face::South: return Face::North;
      case Face::West: return Face::East;
      case Face::East: return Face::West;
      }
      assert(false && "SHOULD NOT BE REACHED");
   }

   [[nodiscard]] constexpr FaceMask to_mask()
   {
      switch (value()) {
      case Face::Bottom: return FaceMask::Bottom;
      case Face::Top: return FaceMask::Top;
      case Face::North: return FaceMask::North;
      case Face::South: return FaceMask::South;
      case Face::West: return FaceMask::West;
      case Face::East: return FaceMask::East;
      }
      assert(false && "SHOULD NOT BE REACHED");
   }
};

inline bool operator&(FaceMask lhs, Face rhs)
{
   return lhs & rhs.to_mask();
}

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

   [[nodiscard]] constexpr ChunkSectionPosition chunk_section_position() const;

   [[nodiscard]] constexpr mb::u32 section_offset() const
   {
      return (y & 15) * 16 * 16 + (z & 15) * 16 + (x & 15);
   }

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

   [[nodiscard]] constexpr math::Vector3 to_vec3() const
   {
      return {static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)};
   }

   static BlockPosition from_vec3(const math::Vector3 &position)
   {
      return {
              static_cast<int>(position.x()),
              static_cast<int>(position.y()),
              static_cast<int>(position.z()),
      };
   }

   bool operator==(const BlockPosition &other) const
   {
      return this->x == other.x && this->y == other.y && this->z == other.z;
   }

   bool operator!=(const BlockPosition &other) const
   {
      return this->x != other.x || this->y != other.y || this->z != other.z;
   }

   BlockPosition operator-(const BlockPosition &other) const
   {
      return {x - other.x, y - other.y, z - other.z};
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
   math::Vector2i position;

   constexpr ChunkPosition() = default;

   constexpr ChunkPosition(int x, int z) :
       position{x, z}
   {
   }

   constexpr explicit ChunkPosition(math::Vector2i position) :
       position{position}
   {
   }

   [[nodiscard]] constexpr int x() const
   {
      return this->position.x();
   }

   [[nodiscard]] constexpr int z() const
   {
      return this->position.y();
   }

   [[nodiscard]] constexpr ChunkPosition operator+(const ChunkPosition &other) const
   {
      return ChunkPosition{this->position + other.position};
   }

   [[nodiscard]] constexpr ChunkHash hash() const
   {
      return static_cast<ChunkHash>(this->z()) + g_chunk_max_z * static_cast<ChunkHash>(this->x());
   }

   [[nodiscard]] constexpr BlockPosition block_at(int block_x, int block_y, int block_z) const
   {
      return {this->x() * g_chunk_width + block_x, block_y, this->z() * g_chunk_depth + block_z};
   }

   [[nodiscard]] constexpr bool is_block_inside(int block_x, int block_z) const
   {
      const auto left   = g_chunk_width * this->x();
      const auto right  = g_chunk_width * (this->x() + 1);
      const auto bottom = g_chunk_depth * this->z();
      const auto top    = g_chunk_depth * (this->z() + 1);
      return block_x >= left && block_x < right && block_z >= bottom && block_z < top;
   }

   static constexpr ChunkPosition from_position(const math::Vector3 &v)
   {
      return ChunkPosition{(v.flat() / math::Vector2{g_chunk_width, g_chunk_depth}).floor().cast<int>()};
   }

   [[nodiscard]] static inline ChunkPosition from_proto(const proto::common::v1::ChunkPosition &pos)
   {
      return {pos.x(), pos.z()};
   }

   [[nodiscard]] inline proto::common::v1::ChunkPosition to_proto() const
   {
      proto::common::v1::ChunkPosition result;
      result.set_x(this->x());
      result.set_z(this->z());
      return result;
   }

   [[nodiscard]] constexpr bool operator!=(const ChunkPosition &other) const
   {
      return this->x() != other.x() || this->z() != other.z();
   }
};

constexpr ChunkPosition BlockPosition::chunk_position() const
{
   return {x >= 0 ? (x / g_chunk_width) : ((x + 1) / g_chunk_width - 1),
           z >= 0 ? (z / g_chunk_depth) : ((z + 1) / g_chunk_depth - 1)};
}

struct ChunkSectionPosition
{
   math::Vector3i position{};

   constexpr ChunkSectionPosition() = default;

   constexpr ChunkSectionPosition(int x, int y, int z) :
       position{x, y, z}
   {
   }

   constexpr ChunkSectionPosition(ChunkPosition chunk_position, int y) :
       position{chunk_position.x(), y, chunk_position.z()}
   {
   }

   [[nodiscard]] constexpr int x() const
   {
      return this->position.x();
   }

   [[nodiscard]] constexpr int y() const
   {
      return this->position.y();
   }

   [[nodiscard]] constexpr int z() const
   {
      return this->position.z();
   }

   [[nodiscard]] constexpr ChunkPosition chunk_position() const
   {
      return {x(), z()};
   }

   [[nodiscard]] constexpr mb::u64 hash() const
   {
      auto lx = this->x() >= 0 ? static_cast<mb::u64>(this->x())
                               : static_cast<mb::u64>(static_cast<mb::i64>(this->x()) + (1 << 26));
      auto ly = this->y() >= 0 ? static_cast<mb::u64>(this->y())
                               : static_cast<mb::u64>(static_cast<mb::i64>(this->y()) + (1 << 12));
      auto lz = this->z() >= 0 ? static_cast<mb::u64>(this->z())
                               : static_cast<mb::u64>(static_cast<mb::i64>(this->z()) + (1 << 26));
      return ((lx & g_block_position_mask_x) << g_block_position_bit_offset_x) |
             (ly & g_block_position_mask_y) |
             ((lz & g_block_position_mask_z) << g_block_position_bit_offset_z);
   }

   [[nodiscard]] constexpr bool operator!=(const ChunkSectionPosition &other) const
   {
      return this->position != other.position;
   }

   [[nodiscard]] static inline ChunkSectionPosition
   from_proto(const proto::common::v1::ChunkSectionPosition &position)
   {
      return {
              ChunkPosition::from_proto(position.chunk_position()),
              position.y(),
      };
   }

   [[nodiscard]] inline proto::common::v1::ChunkSectionPosition to_proto() const
   {
      proto::common::v1::ChunkSectionPosition result;
      *result.mutable_chunk_position() = this->chunk_position().to_proto();
      result.set_y(this->y());
      return result;
   }
};

constexpr ChunkSectionPosition BlockPosition::chunk_section_position() const
{
   return {chunk_position(), y / 16};
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
         switch (value()) {
         case Direction::North: return Direction::West;
         case Direction::South: return Direction::East;
         case Direction::West: return Direction::South;
         case Direction::East: return Direction::North;
         }
      } else {
         switch (value()) {
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
      switch (value()) {
      case Direction::North: return Face::North;
      case Direction::South: return Face::South;
      case Direction::West: return Face::West;
      case Direction::East: return Face::East;
      }
      assert(false && "not reachable");
   }

   [[nodiscard]] static constexpr Direction from_vec2(const math::Vector2 &vec)
   {
      bool x_dominant = std::abs(vec.x()) > std::abs(vec.y());
      if (x_dominant) {
         if (vec.x() > 0.0)
            return Direction::East;
         return Direction::West;
      }

      if (vec.y() > 0.0)
         return Direction::South;
      return Direction::North;
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

enum class LightTypeValue
{
   Block,
   Sky
};

using LightType_Base = mb::enum_wrapper<LightTypeValue, "block", "sky">;

class LightType final : public LightType_Base
{
 public:
   MB_ENUM_TRAITS(LightType);

   MB_ENUM_FIELD(Block)
   MB_ENUM_FIELD(Sky)

   [[nodiscard]] static constexpr LightType from_proto(const proto::common::v1::LightType type)
   {
      return LightType{static_cast<LightTypeValue>(type)};
   }

   [[nodiscard]] constexpr proto::common::v1::LightType to_proto()
   {
      return static_cast<proto::common::v1::LightType>(index());
   }
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

struct SectionRange
{
   struct Iterator
   {
      SectionRange &range;
      ChunkSectionPosition at;

      constexpr Iterator &operator++()
      {
         if (at.x() < range.to.x()) {
            at.position.set_x(at.x() + 1);
            return *this;
         }
         at.position.set_x(range.from.x());

         if (at.z() < range.to.z()) {
            at.position.set_z(at.z() + 1);
            return *this;
         }
         at.position.set_z(range.from.z());

         if (at.y() <= range.to.y()) {
            at.position.set_y(at.y() + 1);
         }

         return *this;
      }

      [[nodiscard]] constexpr bool operator>(const Iterator &other) const
      {
         if (at.y() > other.at.y())
            return true;
         if (at.y() < other.at.y())
            return false;

         if (at.z() > other.at.z())
            return true;
         if (at.z() < other.at.z())
            return false;

         return at.x() > other.at.x();
      }

      [[nodiscard]] constexpr bool operator!=(const Iterator &other) const
      {
         return at != other.at;
      }

      [[nodiscard]] constexpr ChunkSectionPosition operator*() const
      {
         return at;
      }
   };

   ChunkSectionPosition from;
   ChunkSectionPosition to;

   [[nodiscard]] constexpr Iterator begin()
   {
      return Iterator{*this, from};
   }

   [[nodiscard]] constexpr Iterator end()
   {
      return Iterator{
              *this,
              {to.x(), to.y() + 1, to.z()}
      };
   }

   [[nodiscard]] static inline SectionRange from_proto(const proto::common::v1::SectionRange &range)
   {
      return SectionRange{
              .from = ChunkSectionPosition::from_proto(range.from()),
              .to   = ChunkSectionPosition::from_proto(range.to()),
      };
   }

   [[nodiscard]] inline proto::common::v1::SectionRange to_proto() const
   {
      proto::common::v1::SectionRange result;
      *result.mutable_from() = from.to_proto();
      *result.mutable_to()   = to.to_proto();
      return result;
   }

   [[nodiscard]] constexpr SectionRange grow(int amount) const
   {
      return SectionRange{
              .from{from.x() - amount, from.y() - amount, from.z() - amount},
              .to{  to.x() + amount,   to.y() + amount,   to.z() + amount},
      };
   }

   [[nodiscard]] constexpr bool is_in_range(ChunkSectionPosition position) const
   {
      if (position.x() < from.x())
         return false;
      if (position.z() < from.z())
         return false;
      if (position.y() < from.y())
         return false;

      if (position.x() > to.x())
         return false;
      if (position.z() > to.z())
         return false;
      if (position.y() > to.y())
         return false;

      return true;
   }
};

struct LightSource
{
   BlockPosition position{};
   mb::u8 strength{};

   LightSource() = default;

   LightSource(const BlockPosition &position, mb::u8 strength) :
       position(position),
       strength(strength)
   {
   }

   [[nodiscard]] static inline LightSource from_proto(const proto::common::v1::LightSource &source)
   {
      return {
              BlockPosition::from_proto(source.position()),
              static_cast<mb::u8>(source.strength()),
      };
   }

   [[nodiscard]] inline proto::common::v1::LightSource to_proto() const
   {
      proto::common::v1::LightSource result;
      *result.mutable_position() = position.to_proto();
      result.set_strength(strength);
      return result;
   }
};

enum class HeightTypeValues
{
   MotionBlocking,
   WorldSurface,
   LightBlocking
};

using HeightType_Base =
        mb::enum_wrapper<HeightTypeValues, "MOTION_BLOCKING", "WORLD_SURFACE", "LIGHT_BLOCKING">;

class HeightType final : public HeightType_Base
{
 public:
   MB_ENUM_TRAITS(HeightType);

   MB_ENUM_FIELD(MotionBlocking)
   MB_ENUM_FIELD(WorldSurface)
   MB_ENUM_FIELD(LightBlocking)
};

struct BlockRange
{
   BlockPosition min;
   BlockPosition max;

   struct Iterator
   {
      const BlockRange &range;
      BlockPosition at;

      Iterator &operator++()
      {
         if (at.x >= range.max.x) {
            if (at.y >= range.max.y) {
               ++at.z;
               at.y = range.min.y;
               at.x = range.min.x;
               return *this;
            }

            ++at.y;
            at.x = range.min.x;
            return *this;
         }

         ++at.x;
         return *this;
      }

      BlockPosition operator*() const
      {
         return at;
      }

      bool operator==(const Iterator &other) const
      {
         return at == other.at;
      }

      bool operator!=(const Iterator &other) const
      {
         return at != other.at;
      }
   };

   [[nodiscard]] constexpr int width() const
   {
      return 1 + max.x - min.x;
   }

   [[nodiscard]] constexpr int height() const
   {
      return 1 + max.y - min.y;
   }

   [[nodiscard]] constexpr int depth() const
   {
      return 1 + max.z - min.z;
   }

   [[nodiscard]] constexpr Iterator begin() const
   {
      return Iterator{*this, this->min};
   }

   [[nodiscard]] constexpr Iterator end() const
   {
      return Iterator{
              *this,
              {this->min.x, this->min.y, this->max.z + 1}
      };
   }

   [[nodiscard]] constexpr std::int64_t block_count() const
   {
      return static_cast<std::int64_t>(width()) * height() * depth();
   }

   [[nodiscard]] constexpr bool contains(BlockPosition position) const
   {
      if (position.x < min.x || position.x > max.x) {
         return false;
      }
      if (position.y < min.y || position.y > max.y) {
         return false;
      }
      if (position.z < min.z || position.z > max.z) {
         return false;
      }
      return true;
   }
};

struct BlockStateInfo
{
   LightValue luminance{};
   LightValue opacity{};
   bool blocks_movement{};
   FaceMask solid_faces{};

   static BlockStateInfo from_nbt(const nbt::block::v1::BlockState &state)
   {
      return {static_cast<LightValue>(state.luminance), static_cast<LightValue>(state.opacity),
              state.blocks_movement != 0, face_mask_from_nbt(state.solid_faces)};
   }
};

enum class EquipmentSlotValue
{
   MainHand,
   OffHand,
   Boots,
   Leggings,
   Chestplate,
   Helmet
};

using EquipmentSlot_Base = mb::enum_wrapper<EquipmentSlotValue, "MAIN_HAND", "OFF_HAND", "BOOTS", "LEGGINGS",
                                            "CHESTPLATE", "HELMET">;

class EquipmentSlot final : public EquipmentSlot_Base
{
 public:
   MB_ENUM_TRAITS(EquipmentSlot);

   MB_ENUM_FIELD(MainHand)
   MB_ENUM_FIELD(OffHand)
   MB_ENUM_FIELD(Boots)
   MB_ENUM_FIELD(Leggings)
   MB_ENUM_FIELD(Chestplate)
   MB_ENUM_FIELD(Helmet)

   [[nodiscard]] proto::entity::v1::EquipmentSlot to_proto() const
   {
      using proto::entity::v1::EquipmentSlot;

      switch (this->value()) {
      case EquipmentSlotValue::MainHand: return EquipmentSlot::MAIN_HAND;
      case EquipmentSlotValue::OffHand: return EquipmentSlot::OFF_HAND;
      case EquipmentSlotValue::Boots: return EquipmentSlot::BOOTS;
      case EquipmentSlotValue::Leggings: return EquipmentSlot::LEGGINGS;
      case EquipmentSlotValue::Chestplate: return EquipmentSlot::CHESTPLATE;
      case EquipmentSlotValue::Helmet: return EquipmentSlot::HELMET;
      }

      assert(false);
   }
};

struct ItemSlot
{
   ItemId item_id;
   int count;
};

enum EntityAnimationValue
{
   SwingMainArm,
   TakeDamage,
   LeaveBed,
   SwingOffHand,
   CriticalEffect,
   MagicCriticalEffect,
};

using EntityAnimation_Base = mb::enum_wrapper<EntityAnimationValue, "SwingMainArm", "TakeDamage", "LeaveBed",
                                              "SwingOffHand", "CriticalEffect", "MagicCriticalEffect">;

class EntityAnimation : public EntityAnimation_Base
{
 public:
   MB_ENUM_TRAITS(EntityAnimation)

   MB_ENUM_FIELD(SwingMainArm)
   MB_ENUM_FIELD(TakeDamage)
   MB_ENUM_FIELD(LeaveBed)
   MB_ENUM_FIELD(SwingOffHand)
   MB_ENUM_FIELD(CriticalEffect)
   MB_ENUM_FIELD(MagicCriticalEffect)

   proto::common::v1::EntityAnimation to_proto()
   {
      return static_cast<proto::common::v1::EntityAnimation>(index());
   }
};

}// namespace minecpp::game