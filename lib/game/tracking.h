#pragma once
#include "blocks/position.h"
#include "world.h"
#include <mineutils/vec.h>

namespace Game {

using Utils::Vec3;
using Utils::Vec2;
class Player;

class Tracking {
   Vec2 last_chunk_pos;
   int radius_sq;
   int radius;
   int move_dist_sq;

 public:
   explicit Tracking(Vec3 position, int radius);

   void load_chunks(World &w, Player &p);
   void on_movement(World &w, Player &p, Vec3 position);
};

} // namespace Game
