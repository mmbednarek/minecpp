#ifndef MINECPP_REPOSITORY_BLOCK_H
#define MINECPP_REPOSITORY_BLOCK_H
#include "repository.h"
#include "state.h"
#include <minecpp/game/block/block.h>
#include <minecpp/game/state.h>

namespace minecpp::repository {

class Block : public Repository<game::block::Block> {
   static Block g_instance;
 public:
   constexpr static Block &the() {
      return g_instance;
   }
};

class BlockState : public Repository<game::State> {
   static BlockState g_instance;
 public:
   constexpr static BlockState &the() {
      return g_instance;
   }
};

mb::emptyres load_blocks_from_file(std::string_view filename);

template<typename TFunc>
mb::result<int> encode_state(int block_id, TFunc fn) {
   const auto &block = MB_TRY(Block::the().get_by_id(block_id));
   auto state_id = 0;
   for (auto const &state : block.states) {
      state_id *= state.value_count();
      state_id += fn(state);
   }
//   std::for_each(block.states.rbegin(), block.states.rend(), [&state_id, &fn](const game::State &state) {
//     state_id *= state.value_count();
//     state_id += fn(state);
//   });
   return StateManager::the().block_base_state(block_id) + state_id;
}

std::function<int (const game::State  &)> make_compound_encoder(const nbt::CompoundContent &cnt);

}

#endif//MINECPP_REPOSITORY_BLOCK_H
