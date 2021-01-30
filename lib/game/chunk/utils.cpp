#include <cassert>
#include <minecpp/game/block/material.h>
#include <minecpp/game/block/registry.h>
#include <minecpp/game/chunk/utils.h>
#include <minecpp/util/packed.h>

namespace minecpp::game {

int calculate_ref_count(const std::vector<std::int64_t> &data,
                        const std::vector<std::uint32_t> &palette) {
   if (data.empty()) {
      return 0;
   }
   int bits = minecpp::util::log2(palette.size());
   if (bits < 4) {
      bits = 4;
   }
   int count = 0;
   minecpp::util::for_each_packed(data, bits, 4096, [&count, palette](uint32_t value) {
      assert(value < palette.size());
      auto block = block::block_by_tag(
              block::tag_from_state_id(palette[value % palette.size()]));
      if (block.material != &block::Material::Air) {
         ++count;
      }
   });
   return count;
}

}// namespace minecpp::game
