#include "utils.h"
#include <cassert>
#include <game/blocks/material.h>
#include <game/blocks/registry.h>
#include <mineutils/packed.h>

namespace Game {

int calculate_ref_count(const std::vector<std::int64_t> &data,
                        const std::vector<std::uint32_t> &palette) {
   if (data.empty()) {
      return 0;
   }
   int bits = Utils::log2(palette.size());
   if (bits < 4) {
      bits = 4;
   }
   int count = 0;
   Utils::for_each_packed(data, bits, 4096, [&count, palette](uint32_t value) {
      assert(value < palette.size());
      auto block = Block::block_by_tag(
          Block::tag_from_state_id(palette[value % palette.size()]));
      if (block.material != &Block::Material::Air) {
         ++count;
      }
   });
   return count;
}

} // namespace Game
