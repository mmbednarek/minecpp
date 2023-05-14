#pragma once

#include <mb/int.h>
#include <minecpp/math/Vector3.h>
#include <minecpp/proto/common/v1/Common.pb.h>

namespace minecpp::game {

class ChunkPosition;

class SectionPosition
{
 public:
   SectionPosition();
   SectionPosition(int x, int y, int z);
   SectionPosition(ChunkPosition chunk_position, int y);

   [[nodiscard]] int x() const;
   [[nodiscard]] int y() const;
   [[nodiscard]] int z() const;

   [[nodiscard]] ChunkPosition chunk_position() const;
   [[nodiscard]] mb::u64 hash() const;
   [[nodiscard]] proto::common::v1::ChunkSectionPosition to_proto() const;
   [[nodiscard]] const math::Vector3i &position() const;
   [[nodiscard]] math::Vector3i &position();

   [[nodiscard]] static SectionPosition from_proto(const proto::common::v1::ChunkSectionPosition &position);

   [[nodiscard]] bool operator!=(const SectionPosition &other) const;

 private:
   math::Vector3i m_position{};
};

}// namespace minecpp::game
