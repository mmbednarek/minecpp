#pragma once

#include "SectionPosition.h"
#include <minecpp/proto/common/Common.pb.h>

namespace minecpp::game {

class ChunkRange;

class SectionRange
{
 public:
   class Iterator;

   SectionRange(const SectionPosition &from, const SectionPosition &to);

   [[nodiscard]] Iterator begin();
   [[nodiscard]] Iterator end();
   [[nodiscard]] bool is_in_range(SectionPosition position) const;
   [[nodiscard]] SectionRange grow(int amount) const;

   [[nodiscard]] proto::common::SectionRange to_proto() const;

   [[nodiscard]] static SectionRange from_proto(const proto::common::SectionRange &range);

   [[nodiscard]] ChunkRange to_chunk_range() const;

   class Iterator
   {
    public:
      friend SectionRange;

      Iterator &operator++();
      [[nodiscard]] bool operator>(const Iterator &other) const;
      [[nodiscard]] bool operator!=(const Iterator &other) const;
      [[nodiscard]] SectionPosition operator*() const;

    private:
      Iterator(SectionRange &range, const SectionPosition &at);

      SectionRange &m_range;
      SectionPosition m_at;
   };

 private:
   SectionPosition m_from;
   SectionPosition m_to;
};

}// namespace minecpp::game
