#include <minecpp/game/ChunkPosition.h>
#include <minecpp/game/SectionPosition.h>

namespace minecpp::game {

SectionPosition::SectionPosition() = default;

SectionPosition::SectionPosition(int x, int y, int z) :
    m_position{x, y, z}
{
}

SectionPosition::SectionPosition(ChunkPosition chunk_position, int y) :
    m_position{chunk_position.x(), y, chunk_position.z()}
{
}

int SectionPosition::x() const
{
   return m_position.x();
}

int SectionPosition::y() const
{
   return m_position.y();
}

int SectionPosition::z() const
{
   return m_position.z();
}

ChunkPosition SectionPosition::chunk_position() const
{
   return {x(), z()};
}

mb::u64 SectionPosition::hash() const
{
   auto lx = this->x() >= 0 ? static_cast<mb::u64>(this->x())
                            : static_cast<mb::u64>(static_cast<mb::i64>(this->x()) + (1 << 26));
   auto ly = this->y() >= 0 ? static_cast<mb::u64>(this->y())
                            : static_cast<mb::u64>(static_cast<mb::i64>(this->y()) + (1 << 12));
   auto lz = this->z() >= 0 ? static_cast<mb::u64>(this->z())
                            : static_cast<mb::u64>(static_cast<mb::i64>(this->z()) + (1 << 26));
   return ((lx & g_block_position_mask_x) << g_block_position_bit_offset_x) | (ly & g_block_position_mask_y) |
          ((lz & g_block_position_mask_z) << g_block_position_bit_offset_z);
}

bool SectionPosition::operator!=(const SectionPosition &other) const
{
   return m_position != other.m_position;
}

const math::Vector3i &SectionPosition::position() const
{
   return m_position;
}

math::Vector3i &SectionPosition::position()
{
   return m_position;
}

}// namespace minecpp::game
