#include <cassert>
#include <minecpp/game/block/Material.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/State.h>
#include <minecpp/util/Packed.h>
#include <minecpp/world/Util.h>

namespace minecpp::world {

int calculate_ref_count(const std::vector<std::uint64_t> &data, const std::vector<std::uint32_t> &palette)
{
   if (data.empty()) {
      return 0;
   }
   auto bits = static_cast<std::uint8_t>(minecpp::util::log2(static_cast<std::uint32_t>(palette.size())));
   if (bits < 4) {
      bits = 4;
   }
   int count = 0;
   minecpp::util::for_each_packed(data, bits, 4096, [&count, palette](uint32_t value) {
      assert(value < palette.size());
      auto [block_id, state_value] = repository::StateManager::the().parse_block_id(
              static_cast<game::BlockStateId>(palette[value % palette.size()]));

      auto res = repository::Block::the().get_by_id(block_id);
      if (!res.ok())
         return;

      auto &block = res.unwrap();
      if (block.stats().material != &game::block::Material::Air) {
         ++count;
      }
   });
   return count;
}

}// namespace minecpp::world
