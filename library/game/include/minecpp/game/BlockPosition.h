#pragma once

#include <mb/int.h>
#include <minecpp/math/Vector3.h>
#include <minecpp/proto/common/v1/Common.pb.h>

namespace minecpp::game {

class ChunkPosition;
class SectionPosition;
class Face;

class BlockPosition
{
 public:
   BlockPosition();
   BlockPosition(int x, int y, int z);
   explicit BlockPosition(const math::Vector3i &position);
   explicit BlockPosition(mb::u64 encoded);

   [[nodiscard]] int x() const;
   [[nodiscard]] int y() const;
   [[nodiscard]] int z() const;
   [[nodiscard]] ChunkPosition chunk_position() const;
   [[nodiscard]] SectionPosition chunk_section_position() const;
   [[nodiscard]] BlockPosition neighbour_at(Face facing) const;
   [[nodiscard]] mb::u32 section_offset() const;
   [[nodiscard]] mb::u8 section_offset_y() const;
   [[nodiscard]] mb::u8 offset_x() const;
   [[nodiscard]] mb::u8 offset_z() const;
   [[nodiscard]] mb::u16 offset() const;
   [[nodiscard]] mb::u32 offset_within_section() const;

   [[nodiscard]] math::Vector3 to_vector3() const;
   [[nodiscard]] mb::u64 as_long() const;
   [[nodiscard]] proto::common::v1::BlockPosition to_proto() const;

   void set_x(int x);
   void set_y(int y);
   void set_z(int z);

   static BlockPosition from_proto(const proto::common::v1::BlockPosition &position);
   static BlockPosition from_vector3(const math::Vector3 &position);

   bool operator==(const BlockPosition &other) const;
   bool operator!=(const BlockPosition &other) const;
   BlockPosition operator-(const BlockPosition &other) const;

 private:
   math::Vector3i m_position{};
};

}// namespace minecpp::game
