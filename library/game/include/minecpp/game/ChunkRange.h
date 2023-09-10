#pragma once

#include "ChunkPosition.h"

namespace minecpp::game {

class ChunkRange
{
 public:
   class Iterator;

   ChunkRange(const ChunkPosition &from, const ChunkPosition &to);

   [[nodiscard]] Iterator begin();
   [[nodiscard]] Iterator end();
   [[nodiscard]] bool is_in_range(ChunkPosition position) const;

   class Iterator
   {
    public:
      friend ChunkRange;

      Iterator &operator++();
      [[nodiscard]] bool operator>(const Iterator &other) const;
      [[nodiscard]] bool operator!=(const Iterator &other) const;
      [[nodiscard]] ChunkPosition operator*() const;

    private:
      Iterator(ChunkRange &range, const ChunkPosition &at);

      ChunkRange &m_range;
      ChunkPosition m_at;
   };

 private:
   ChunkPosition m_from;
   ChunkPosition m_to;
};

}// namespace minecpp::game

template<>
struct std::iterator_traits<minecpp::game::ChunkRange::Iterator>
{
   using iterator_category = std::forward_iterator_tag;
   using value_type        = minecpp::game::ChunkPosition;
   using pointer           = minecpp::game::ChunkPosition *;
   using reference         = minecpp::game::ChunkPosition &;
};