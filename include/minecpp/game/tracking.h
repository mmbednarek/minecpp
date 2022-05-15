#pragma once
#include "world.h"
#include <mb/result.h>
#include <minecpp/game/game.h>
#include <minecpp/util/vec.h>
#include <mutex>

namespace minecpp::game {

using minecpp::util::Vec2;
using minecpp::util::Vec3;
class Player;

class Tracking
{
   std::mutex m_mutex{};
   ChunkPosition m_chunk_pos;
   int m_radius_sq;
   int m_radius;

 public:
   explicit Tracking(Vec3 position, int radius);

   mb::result<mb::empty> load_chunks(World &w, Player &p);
   void on_movement(World &w, Player &p, Vec3 position);
};

}// namespace minecpp::game
