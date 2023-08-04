#include "SectionRange.h"
#include "ChunkRange.h"

namespace minecpp::game {

SectionRange::SectionRange(const SectionPosition &from, const SectionPosition &to) :
    m_from(from),
    m_to(to)
{
}

SectionRange::Iterator SectionRange::begin()
{
   return Iterator{*this, m_from};
}

SectionRange::Iterator SectionRange::end()
{
   return Iterator{
           *this,
           {m_to.x(), m_to.y() + 1, m_to.z()}
   };
}

SectionRange SectionRange::from_proto(const proto::common::SectionRange &range)
{
   return SectionRange{
           SectionPosition::from_proto(range.from()),
           SectionPosition::from_proto(range.to()),
   };
}

proto::common::SectionRange SectionRange::to_proto() const
{
   proto::common::SectionRange result;
   *result.mutable_from() = m_from.to_proto();
   *result.mutable_to()   = m_to.to_proto();
   return result;
}

SectionRange SectionRange::grow(int amount) const
{
   return SectionRange{
           {m_from.x() - amount, m_from.y() - amount, m_from.z() - amount},
           {  m_to.x() + amount,   m_to.y() + amount,   m_to.z() + amount},
   };
}

bool SectionRange::is_in_range(SectionPosition position) const
{
   if (position.x() < m_from.x())
      return false;
   if (position.z() < m_from.z())
      return false;
   if (position.y() < m_from.y())
      return false;

   if (position.x() > m_to.x())
      return false;
   if (position.z() > m_to.z())
      return false;
   if (position.y() > m_to.y())
      return false;

   return true;
}

ChunkRange SectionRange::to_chunk_range() const
{
   return {m_from.chunk_position(), m_to.chunk_position()};
}

SectionRange::Iterator::Iterator(SectionRange &range, const SectionPosition &at) :
    m_range(range),
    m_at(at)
{
}

SectionRange::Iterator &SectionRange::Iterator::operator++()
{
   if (m_at.x() < m_range.m_to.x()) {
      m_at.position().set_x(m_at.x() + 1);
      return *this;
   }
   m_at.position().set_x(m_range.m_from.x());

   if (m_at.z() < m_range.m_to.z()) {
      m_at.position().set_z(m_at.z() + 1);
      return *this;
   }
   m_at.position().set_z(m_range.m_from.z());

   if (m_at.y() <= m_range.m_to.y()) {
      m_at.position().set_y(m_at.y() + 1);
   }

   return *this;
}

bool SectionRange::Iterator::operator>(const SectionRange::Iterator &other) const
{
   if (m_at.y() > other.m_at.y())
      return true;
   if (m_at.y() < other.m_at.y())
      return false;

   if (m_at.z() > other.m_at.z())
      return true;
   if (m_at.z() < other.m_at.z())
      return false;

   return m_at.x() > other.m_at.x();
}

bool SectionRange::Iterator::operator!=(const SectionRange::Iterator &other) const
{
   return m_at != other.m_at;
}

SectionPosition SectionRange::Iterator::operator*() const
{
   return m_at;
}

}// namespace minecpp::game
