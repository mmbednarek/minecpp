#include <game/blocks/registry.h>
#include <iostream>

auto main() -> int {
   for (auto &block : Game::Block::blocks) {
      std::cout << block.tag() << '\n';
      for (const auto &attrib : block.attributes) {
         std::cout << "  - " << attrib->name() << " [";
         for (int i = 0; i < attrib->num_states() - 1; ++i) {
            std::cout << attrib->name_of(i) << ", ";
         }
         std::cout << attrib->name_of(attrib->num_states() - 1) << "]\n";
      }
   }
}
