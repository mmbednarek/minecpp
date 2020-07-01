#include "utils.h"
#include <cassert>
#include <game/blocks/material.h>
#include <game/blocks/registry.h>
#include <mineutils/packed.h>

namespace Game {

int calculate_ref_count(const std::vector<long long> &data,
                        const std::vector<int> &palette) {
   if(data.empty()) {
      return 0;
   }
   int count = 0;
   Utils::for_each_packed(data, [&count, palette](uint32_t value) {
//      assert(value < palette.size());
      auto block = Block::block_by_tag(Block::tag_from_state_id(palette[value % palette.size()]));
      if (block.material != &Block::Material::Air) {
         ++count;
      }
   });
   return count;
}

} // namespace Game
