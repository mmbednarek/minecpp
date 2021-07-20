#pragma once
#include <mb/result.h>
#include <minecpp/game/game.h>
#include <minecpp/util/vec.h>
#include <mutex>

namespace minecpp::game {
class World;
}

namespace minecpp::player {

class Player;

class Tracking {
   std::mutex m_mutex{};
   game::ChunkPosition m_chunk_pos{};
   int m_radius_sq{};
   int m_radius{};

 public:
   explicit Tracking(const util::Vec3 &position, int radius);

   mb::result<mb::empty> load_chunks(game::World &w, Player &p);
   void on_movement(game::World &w, Player &p, util::Vec3 position);
};

}// namespace minecpp::player