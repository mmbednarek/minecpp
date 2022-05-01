#include <cassert>
#include <minecpp/game/block/material.h>
#include <minecpp/game/chunk/utils.h>
#include <minecpp/repository/state.h>
#include <minecpp/repository/block.h>
#include <minecpp/util/packed.h>

namespace minecpp::game {

int calculate_ref_count(const std::vector<std::int64_t> &data,
                        const std::vector<std::uint32_t> &palette) {
   if (data.empty()) {
      return 0;
   }
   int bits = static_cast<int>(minecpp::util::log2(palette.size()));
   if (bits < 4) {
      bits = 4;
   }
   int count = 0;
   minecpp::util::for_each_packed(data, bits, 4096, [&count, palette](uint32_t value) {
      assert(value < palette.size());
      auto [block_id, state_value] =  repository::StateManager::the().parse_block_id(static_cast<int>(palette[value % palette.size()]));

      auto res = repository::Block::the().get_by_id(block_id);
      if (!res.ok())
         return;

      auto &block = res.unwrap();
      if (block.stats().material != &block::Material::Air) {
         ++count;
      }
   });
   return count;
}

}// namespace minecpp::game
