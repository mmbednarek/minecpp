#include <fstream>
#include <minecpp/game/block/block.h>
#include <minecpp/nbt/repository/v1/repository.nbt.h>
#include <minecpp/repository/block.h>
#include <minecpp/repository/state.h>

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
   int block_id = 0;
   for (auto &block : repo.blocks) {
      std::vector<game::State> block_states;
      int block_state_count = 1;
      for (const auto &tag : block.block.state_tags) {
         auto state = MB_TRY(states.find_block_by_tag(tag));
         block_states.push_back(state);
         block_state_count *= state.value_count();
      }
      state_manager.add_state(block_id, block_state_count);

      blocks.register_resource(block.tag, game::block::Block(block.tag, block_states));

      ++block_id;
   }

   return mb::ok;
}
std::function<int(const game::State &)> make_compound_encoder(const nbt::CompoundContent &cnt) {
   return [&cnt](const game::State &state) -> int {
      auto it = cnt.find(std::string(state.name()));
      if (it == cnt.end())
         return 0;

      auto &content = it->second;

      switch (content.tag_id) {
      case nbt::TagId::String:
         return state.index_from_value(content.as<std::string>());
      case nbt::TagId::Int:
         return state.index_from_value(content.as<int>());
      default:
         break;
      }
   };
}

}// namespace minecpp::repository