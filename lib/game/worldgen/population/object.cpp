#include "object.h"
#include "game/blocks/registry.h"
#include <nbt/tag.h>

namespace Game::WorldGen::Population {

auto empty_nbt = NBT::CompoundContent{};
auto state_axis_y = NBT::CompoundContent{
        {"axis", NBT::make_string("y")},
};

auto upper_half_nbt = NBT::CompoundContent{
        {"half", NBT::make_string("upper")},
};
auto lower_half_nbt = NBT::CompoundContent{
        {"half", NBT::make_string("lower")},
};

int air_id = Block::encode_state("minecraft:air", empty_nbt);
int stone_id = Block::encode_state("minecraft:stone", empty_nbt);
int wood_id = Block::encode_state("minecraft:oak_wood", state_axis_y);
int leaves_id = Block::encode_state("minecraft:oak_leaves", empty_nbt);
int pumpkin_id = Block::encode_state("minecraft:pumpkin", empty_nbt);
int tall_grass_upper_id = Block::encode_state("minecraft:tall_grass", upper_half_nbt);
int tall_grass_lower_id = Block::encode_state("minecraft:tall_grass", lower_half_nbt);
int dendelion_id = Block::encode_state("minecraft:dandelion", empty_nbt);
int poppy_id = Block::encode_state("minecraft:poppy", empty_nbt);
int blue_orchid_id = Block::encode_state("minecraft:blue_orchid", empty_nbt);

const ShapedObject<5, 5, 7> tree0 {
         300, // per 10 000 elements
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

const ShapedObject<1, 1, 1> pumpkin {
        5, // per 10 000 elements
        {
            pumpkin_id
        },
};

const ShapedObject<1, 1, 1> tall_grass0 {
        1800, // per 10 000 elements
        {
                tall_grass_upper_id
        },
};

const ShapedObject<1, 1, 2> tall_grass1 {
        500, // per 10 000 elements
        {
                tall_grass_lower_id,
                tall_grass_upper_id,
        },
};

const ShapedObject<1, 1, 1> dandelion {
        100, // per 10 000 elements
        {
                dendelion_id
        },
};
const ShapedObject<1, 1, 1> poppy {
        100, // per 10 000 elements
        {
                poppy_id
        },
};
const ShapedObject<1, 1, 1> orchid {
        15, // per 10 000 elements
        {
                blue_orchid_id
        },
};

std::array<const PopObject *, 7> pop_objects {
       &tree0,
       &pumpkin,
       &tall_grass0,
       &tall_grass1,
       &dandelion,
       &poppy,
       &orchid
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
