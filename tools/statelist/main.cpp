#include <fmt/core.h>
#include <minecpp/game/block/registry.h>

auto main() -> int {
   for (auto &block : minecpp::game::block::blocks) {
      fmt::print("minecraft:{}\n", block.tag());
      for (const auto &attrib : block.attributes) {
         fmt::print("  - {} [", attrib->name());
         for (int i = 0; i < attrib->num_states() - 1; ++i) {
            fmt::print("{}, ", attrib->name_of(i));
         }
         fmt::print("{}]\n", attrib->name_of(attrib->num_states() - 1));
      }
   }
}
