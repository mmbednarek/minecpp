#include <minecpp/repository/block.h>
#include <minecpp/repository/state.h>
#include <minecpp/game/block/block.h>
#include <minecpp/nbt/repository/v1/repository.nbt.h>
#include <fstream>

namespace minecpp::repository {

Block Block::g_instance;
BlockState BlockState::g_instance;

mb::emptyres load_blocks_from_file(std::string_view filename) {
   std::ifstream in_file(filename.data());
   if (!in_file.is_open()) {
      return mb::error("could not open file");
   }
   auto repo = minecpp::nbt::repository::v1::Repository::deserialize(in_file);

   auto &states = BlockState::the();
   for (auto &bool_state : repo.bool_states) {
      states.register_resource(bool_state.tag, game::State(bool_state.state.name));
   }
   for (auto &int_state : repo.int_states) {
      states.register_resource(int_state.tag, game::State(int_state.state.name, int_state.state.min_value, int_state.state.max_value));
   }
   for (auto &enum_state : repo.enum_states) {
      states.register_resource(enum_state.tag, game::State(enum_state.state.name, enum_state.state.values));
   }

   auto &blocks = Block::the();
   auto &state_manager = StateManager::the();
   int state_id = 0;
   int block_id = 0;
   for (auto &block : repo.blocks) {
      blocks.register_resource(block.tag, game::block::Block(block.tag));
      int block_states = 1;
      for (const auto &tag : block.block.state_tags) {
         auto state = MB_TRY(states.find_block_by_tag(tag));
         block_states *= state.value_count();
      }
      state_manager.add_state(state_id, block_id);
      ++block_id;
      state_id += block_states;
   }

   return mb::ok;
}

}