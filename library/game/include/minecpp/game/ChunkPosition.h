#pragma once

#include "Constants.hpp"
#include "Types.hpp"
#include <minecpp/math/Vector2.h>
#include <minecpp/math/Vector3.h>
#include <minecpp/proto/common/Common.pb.h>

namespace minecpp::game {

class BlockPosition;

class ChunkPosition
{
 public:
   ChunkPosition();
   ChunkPosition(int x, int z);
   explicit ChunkPosition(const math::Vector2i &position);

   [[nodiscard]] int x() const;
   [[nodiscard]] int z() const;

   [[nodiscard]] const math::Vector2i &position() const;
   [[nodiscard]] ChunkHash hash() const;
   [[nodiscard]] BlockPosition block_at(int block_x, int block_y, int block_z) const;
   [[nodiscard]] bool is_block_inside(int block_x, int block_z) const;

   [[nodiscard]] proto::common::ChunkPosition to_proto() const;

   [[nodiscard]] static ChunkPosition from_position(const math::Vector3 &v);
   [[nodiscard]] static ChunkPosition from_proto(const proto::common::ChunkPosition &pos);

   [[nodiscard]] ChunkPosition operator+(const ChunkPosition &other) const;
   [[nodiscard]] bool operator==(const ChunkPosition &other) const;
   [[nodiscard]] bool operator!=(const ChunkPosition &other) const;

 private:
   math::Vector2i m_position{};
};

}// namespace minecpp::game
