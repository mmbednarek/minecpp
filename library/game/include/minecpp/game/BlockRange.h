#pragma once

#include "BlockPosition.h"

namespace minecpp::game {

class BlockRange
{
 public:
   class Iterator;

   BlockRange(const BlockPosition &min, const BlockPosition &max);

   [[nodiscard]] const BlockPosition &min() const;
   [[nodiscard]] const BlockPosition &max() const;

   [[nodiscard]] int width() const;
   [[nodiscard]] int height() const;
   [[nodiscard]] int depth() const;
   [[nodiscard]] Iterator begin() const;
   [[nodiscard]] Iterator end() const;
   [[nodiscard]] std::int64_t block_count() const;
   [[nodiscard]] bool contains(BlockPosition position) const;

   class Iterator
   {
    public:
      friend BlockRange;

      Iterator(const BlockRange &range, const BlockPosition &at);

      Iterator &operator++();
      BlockPosition operator*() const;
      bool operator==(const Iterator &other) const;
      bool operator!=(const Iterator &other) const;

    private:
      const BlockRange &m_range;
      BlockPosition m_at;
   };

 private:
   BlockPosition m_min;
   BlockPosition m_max;
};

}// namespace minecpp::game