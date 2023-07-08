#include <minecpp/game/BlockPosition.h>
#include <minecpp/game/ChunkPosition.h>
#include <minecpp/game/Constants.hpp>
#include <minecpp/game/property/Face.h>
#include <minecpp/game/SectionPosition.h>

namespace {

[[nodiscard]] int decode_x(mb::u64 pos)
{
   auto x = pos >> 38;
   if (x >= (1u << 25)) {
      return static_cast<int>(static_cast<mb::i64>(x) - (1 << 26));
   }
   return static_cast<int>(x);
}

[[nodiscard]] int decode_y(mb::u64 pos)
{
   auto y = pos & 0xFFF;
   if (y >= (1u << 11)) {
      return static_cast<int>(static_cast<mb::i64>(y) - (1 << 12));
   }
   return static_cast<int>(y);
}

[[nodiscard]] int decode_z(mb::u64 pos)
{
   auto z = (pos >> 12) & 0x3FFFFFF;
   if (z >= (1u << 25)) {
      return static_cast<int>(static_cast<mb::i64>(z) - (1 << 26));
   }
   return static_cast<int>(z);
}

}// namespace

namespace minecpp::game {

namespace pb_common = minecpp::proto::common;

BlockPosition::BlockPosition() = default;

BlockPosition::BlockPosition(int x, int y, int z) :
    m_position{x, y, z}
{
}

BlockPosition::BlockPosition(const math::Vector3i &position) :
    m_position(position)
{
}

BlockPosition::BlockPosition(mb::u64 encoded) :
    m_position{decode_x(encoded), decode_y(encoded), decode_z(encoded)}
{
   if (x() > 33554431) {
      m_position.set_x(67108862 - x());
   }
   if (z() > 33554431) {
      m_position.set_z(67108862 - z());
   }
}

mb::u64 BlockPosition::as_long() const
{
   auto lx =
           x() >= 0 ? static_cast<mb::u64>(x()) : static_cast<mb::u64>(static_cast<mb::i64>(x()) + (1 << 26));
   auto ly =
           y() >= 0 ? static_cast<mb::u64>(y()) : static_cast<mb::u64>(static_cast<mb::i64>(y()) + (1 << 12));
   auto lz =
           z() >= 0 ? static_cast<mb::u64>(z()) : static_cast<mb::u64>(static_cast<mb::i64>(z()) + (1 << 26));
   return ((lx & g_block_position_mask_x) << g_block_position_bit_offset_x) | (ly & g_block_position_mask_y) |
          ((lz & g_block_position_mask_z) << g_block_position_bit_offset_z);
}

BlockPosition BlockPosition::from_proto(const pb_common::BlockPosition &position)
{
   return {position.x(), position.y(), position.z()};
}

int BlockPosition::x() const
{
   return m_position.x();
}

int BlockPosition::y() const
{
   return m_position.y();
}

int BlockPosition::z() const
{
   return m_position.z();
}

mb::u32 BlockPosition::section_offset() const
{
   return (y() & 15) * 16 * 16 + (z() & 15) * 16 + (x() & 15);
}

mb::u8 BlockPosition::offset_x() const
{
   return x() & (g_chunk_width - 1);
}

mb::u8 BlockPosition::section_offset_y() const
{
   return y() & (g_section_height - 1);
}

mb::u8 BlockPosition::offset_z() const
{
   return z() & (g_chunk_depth - 1);
}

mb::u16 BlockPosition::offset() const
{
   return static_cast<mb::u16>(offset_x() << 12u | y() | offset_z() << 8u);
}

mb::u32 BlockPosition::offset_within_section() const
{
   return (static_cast<mb::u32>(section_offset_y()) << 8) | (static_cast<mb::u32>(offset_z()) << 4) |
          static_cast<mb::u32>(offset_x());
}

pb_common::BlockPosition BlockPosition::to_proto() const
{
   pb_common::BlockPosition block_position;
   block_position.set_x(x());
   block_position.set_y(y());
   block_position.set_z(z());
   return block_position;
}

BlockPosition BlockPosition::neighbour_at(Face facing) const
{
   switch (facing) {
   case Face::Bottom: return {x(), y() - 1, z()};
   case Face::Top: return {x(), y() + 1, z()};
   case Face::North: return {x(), y(), z() - 1};
   case Face::South: return {x(), y(), z() + 1};
   case Face::West: return {x() - 1, y(), z()};
   case Face::East: return {x() + 1, y(), z()};
   }
   return *this;
}

math::Vector3 BlockPosition::to_vector3() const
{
   return m_position.cast<double>();
}

BlockPosition BlockPosition::from_vector3(const math::Vector3 &position)
{
   return BlockPosition{position.floor().cast<int>()};
}

bool BlockPosition::operator==(const BlockPosition &other) const
{
   return m_position == other.m_position;
}

bool BlockPosition::operator!=(const BlockPosition &other) const
{
   return m_position != other.m_position;
}

BlockPosition BlockPosition::operator-(const BlockPosition &other) const
{
   return BlockPosition{m_position - other.m_position};
}

ChunkPosition BlockPosition::chunk_position() const
{
   return {x() >= 0 ? (x() / g_chunk_width) : ((x() + 1) / g_chunk_width - 1),
           z() >= 0 ? (z() / g_chunk_depth) : ((z() + 1) / g_chunk_depth - 1)};
}

SectionPosition BlockPosition::chunk_section_position() const
{
   return {chunk_position(), y() / 16};
}

void BlockPosition::set_x(int x)
{
   m_position.set_x(x);
}

void BlockPosition::set_y(int y)
{
   m_position.set_y(y);
}

void BlockPosition::set_z(int z)
{
   m_position.set_z(z);
}

}// namespace minecpp::game
