#include "population.h"
#include "popobject.h"
#include <game/blocks/position.h>
#include <minerandom/java_random.h>

namespace Game::WorldGen {

Population::Population(Rand::Random &rand) : rand(rand), coef1(rand.next_int()), coef2(rand.next_int()), coef3(rand.next_int()) {
}

void Population::prepare_chunk(std::array<short, 256> &heightmap, int x, int z) {
   Rand::JavaRandom rand(static_cast<uint64_t>(x) * coef1 + static_cast<uint64_t>(z) * coef2 + coef3);

   for (int _z = 0; _z < 16; ++_z) {
      for (int _x = 0; _x < 16; ++_x) {
         auto hash = Block::Position(16 * x + _x, 0, 16 * z + _z).as_long();
         auto curr_placement = placements.find(hash);
         if (curr_placement != placements.end()) {
            continue;
         }

         auto value = rand.next_int(10000);
         auto objid = find_object_id(value);
         if (objid >= 0) {
            put_object(heightmap, objid, 16 * x + _x, 16 * z + _z);
         }
      }
   }
}

void Population::put_object(std::array<short, 256> &heightmap, int id, int x, int z) {
   if (id >= pop_objects.size()) {
      return;
   }
   const auto &obj = pop_objects[id];
   auto center = obj->center();
   auto center_offset = (x % 16) + std::get<0>(center) + ((z % 16) + std::get<1>(center)) * 16;
   if (center_offset > 255) {
      return;
   }
   auto height = heightmap[center_offset] + 1;

   int offset = 0;
   for (int _z = 0; _z < obj->length(); ++_z) {
      for (int _x = 0; _x < obj->width(); ++_x) {
         auto hash = Block::Position(x + _x, 0, z + _z).as_long();
         auto curr_placement = placements.find(hash);
         if (curr_placement != placements.end()) {
            return;
         }
         placements[hash] = Placement{.object_id = id, .x = static_cast<short>(_x), .z = static_cast<short>(_z), .height = static_cast<short>(height)};
         ++offset;
      }
   }
}

Placement Population::get_placement(int x, int z) {
   auto p = placements.find(Block::Position(x, 0, z).as_long());
   if (p == placements.end()) {
      return Placement{
              .object_id = -1,
      };
   }
   return p->second;
}

}// namespace Game::WorldGen
