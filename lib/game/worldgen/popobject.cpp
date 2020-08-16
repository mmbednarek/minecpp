#include "popobject.h"
#include "game/blocks/registry.h"
#include <nbt/tag.h>

namespace Game::WorldGen {

auto empty_nbt = NBT::CompoundContent{};
auto state_axis_y = NBT::CompoundContent{
        {"axis", NBT::make_string("y")},
};

int air_id = Block::encode_state("minecraft:air", empty_nbt);
int wood_id = Block::encode_state("minecraft:oak_wood", state_axis_y);
int leaves_id = Block::encode_state("minecraft:oak_leaves", empty_nbt);

const ShapedObject<5, 5, 7> tree0 {
         600, // per 10 000 elements
        {
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, wood_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, wood_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, wood_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                leaves_id, leaves_id,  wood_id, leaves_id, leaves_id,
                leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                air_id, leaves_id, leaves_id, leaves_id, leaves_id,
                leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                leaves_id, leaves_id,  wood_id, leaves_id, leaves_id,
                leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                leaves_id, leaves_id, leaves_id, leaves_id, leaves_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, leaves_id, leaves_id, leaves_id, air_id,
                air_id, leaves_id,  leaves_id, leaves_id, air_id,
                air_id, leaves_id, leaves_id, leaves_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
                air_id, air_id, leaves_id, air_id, air_id,
                air_id, leaves_id,  leaves_id, leaves_id, air_id,
                air_id, air_id, leaves_id, air_id, air_id,
                air_id, air_id, air_id, air_id, air_id,
        },
};

std::array<const PopObject *, 1> pop_objects {
       &tree0,
};

int find_object_id(int value) {
   if (value == 0) {
      return 0;
   }
   int i = 0;
   for (const auto *e : pop_objects) {
      value -= e->occurrence();
      if (value <= 0) {
         break;
      }
      ++i;
   }

   if (i == pop_objects.size()) {
      return -1;
   }

   return i;
}


}
