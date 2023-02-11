#pragma once
#include <mb/result.h>
#include <minecpp/game/Game.h>
#include <minecpp/math/Vector3.h>
#include <mutex>

namespace minecpp::game {
class World;
}

namespace minecpp::game::player {

class Player;

class Tracking
{
   std::mutex m_mutex{};
   game::ChunkPosition m_chunk_pos{};
   int m_radius_sq{};
   int m_radius{};

 public:
   explicit Tracking(const math::Vector3 &position, int radius);

   mb::result<mb::empty> load_chunks(game::World &world, Player &player);
   void on_movement(game::World &world, Player &player, math::Vector3 position);
};

}// namespace minecpp::game::player