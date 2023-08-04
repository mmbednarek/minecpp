#include <minecpp/game/BlockPosition.h>
#include <minecpp/game/ChunkPosition.h>

namespace minecpp::game {

ChunkPosition::ChunkPosition() = default;

ChunkPosition::ChunkPosition(int x, int z) :
    m_position{x, z}
{
}

ChunkPosition::ChunkPosition(const math::Vector2i &position) :
    m_position{position}
{
}

const math::Vector2i &ChunkPosition::position() const
{
   return m_position;
}

math::Vector2i &ChunkPosition::position()
{
   return m_position;
}

int ChunkPosition::x() const
{
   return m_position.x();
}

int ChunkPosition::z() const
{
   return m_position.y();
}

ChunkPosition ChunkPosition::operator+(const ChunkPosition &other) const
{
   return ChunkPosition{m_position + other.m_position};
}

ChunkHash ChunkPosition::hash() const
{
   return static_cast<ChunkHash>(this->z()) + g_chunk_max_z * static_cast<ChunkHash>(this->x());
}

BlockPosition ChunkPosition::block_at(int block_x, int block_y, int block_z) const
{
   return {this->x() * g_chunk_width + block_x, block_y, this->z() * g_chunk_depth + block_z};
}

bool ChunkPosition::is_block_inside(int block_x, int block_z) const
{
   const auto left   = g_chunk_width * this->x();
   const auto right  = g_chunk_width * (this->x() + 1);
   const auto bottom = g_chunk_depth * this->z();
   const auto top    = g_chunk_depth * (this->z() + 1);
   return block_x >= left && block_x < right && block_z >= bottom && block_z < top;
}

ChunkPosition ChunkPosition::from_position(const math::Vector3 &v)
{
   return ChunkPosition{(v.flat() / math::Vector2{g_chunk_width, g_chunk_depth}).floor().cast<int>()};
}

ChunkPosition ChunkPosition::from_proto(const proto::common::ChunkPosition &pos)
{
   return {pos.x(), pos.z()};
}

proto::common::ChunkPosition ChunkPosition::to_proto() const
{
   proto::common::ChunkPosition result;
   result.set_x(this->x());
   result.set_z(this->z());
   return result;
}

bool ChunkPosition::operator==(const ChunkPosition &other) const
{
   return m_position == other.m_position;
}

bool ChunkPosition::operator!=(const ChunkPosition &other) const
{
   return m_position != other.m_position;
}

}// namespace minecpp::game
