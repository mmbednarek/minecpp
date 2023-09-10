#include "ChunkRange.h"

namespace minecpp::game {

ChunkRange::ChunkRange(const ChunkPosition &from, const ChunkPosition &to) :
    m_from(from),
    m_to(to)
{
}

ChunkRange::Iterator ChunkRange::begin()
{
   return Iterator{*this, m_from};
}

ChunkRange::Iterator ChunkRange::end()
{
   return Iterator{
           *this,
           {m_from.x(), m_to.z() + 1}
   };
}

bool ChunkRange::is_in_range(ChunkPosition position) const
{
   if (position.x() < m_from.x())
      return false;
   if (position.z() < m_from.z())
      return false;

   if (position.x() > m_to.x())
      return false;
   if (position.z() > m_to.z())
      return false;

   return true;
}

ChunkRange::Iterator::Iterator(ChunkRange &range, const ChunkPosition &at) :
    m_range{range},
    m_at{at}
{
}

ChunkRange::Iterator &ChunkRange::Iterator::operator++()
{
   if (m_at.x() < m_range.m_to.x()) {
      m_at.position().set_x(m_at.x() + 1);
      return *this;
   }
   m_at.position().set_x(m_range.m_from.x());

   if (m_at.z() <= m_range.m_to.z()) {
      m_at.position().set_y(m_at.z() + 1);
   }
   return *this;
}

bool ChunkRange::Iterator::operator>(const ChunkRange::Iterator &other) const
{
   if (m_at.z() > other.m_at.z())
      return true;
   if (m_at.z() < other.m_at.z())
      return false;

   return m_at.x() > other.m_at.x();
}

bool ChunkRange::Iterator::operator!=(const ChunkRange::Iterator &other) const
{
   return m_at != other.m_at;
}

ChunkPosition ChunkRange::Iterator::operator*() const
{
   return m_at;
}

}// namespace minecpp::game
