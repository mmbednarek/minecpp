#include <minecpp/game/BlockRange.h>

namespace minecpp::game {

BlockRange::BlockRange(const BlockPosition &min, const BlockPosition &max) :
    m_min(min),
    m_max(max)
{
}

int BlockRange::width() const
{
   return 1 + m_max.x() - m_min.x();
}

int BlockRange::height() const
{
   return 1 + m_max.y() - m_min.y();
}

int BlockRange::depth() const
{
   return 1 + m_max.z() - m_min.z();
}

BlockRange::Iterator BlockRange::begin() const
{
   return Iterator{*this, m_min};
}

BlockRange::Iterator BlockRange::end() const
{
   return Iterator{
           *this,
           {m_min.x(), m_min.y(), m_max.z() + 1}
   };
}

std::int64_t BlockRange::block_count() const
{
   return static_cast<std::int64_t>(width()) * height() * depth();
}

bool BlockRange::contains(BlockPosition position) const
{
   if (position.x() < m_min.x() || position.x() > m_max.x()) {
      return false;
   }
   if (position.y() < m_min.y() || position.y() > m_max.y()) {
      return false;
   }
   if (position.z() < m_min.z() || position.z() > m_max.z()) {
      return false;
   }
   return true;
}

const BlockPosition &BlockRange::min() const
{
   return m_min;
}

const BlockPosition &BlockRange::max() const
{
   return m_max;
}

BlockRange::Iterator::Iterator(const BlockRange &range, const BlockPosition &at) :
    m_range(range),
    m_at(at)
{
}

BlockRange::Iterator &BlockRange::Iterator::operator++()
{
   if (m_at.x() >= m_range.m_max.x()) {
      if (m_at.y() >= m_range.m_max.y()) {
         m_at.set_z(m_at.z() + 1);
         m_at.set_y(m_range.m_min.y());
         m_at.set_x(m_range.m_min.x());
         return *this;
      }

      m_at.set_y(m_at.y() + 1);
      m_at.set_x(m_range.m_min.x());
      return *this;
   }

   m_at.set_x(m_at.x() + 1);
   return *this;
}

BlockPosition BlockRange::Iterator::operator*() const
{
   return m_at;
}

bool BlockRange::Iterator::operator==(const BlockRange::Iterator &other) const
{
   return m_at == other.m_at;
}

bool BlockRange::Iterator::operator!=(const BlockRange::Iterator &other) const
{
   return m_at != other.m_at;
}

}// namespace minecpp::game
