#include "minecpp/repository/Repository.h"
#include <fstream>
#include <minecpp/game/block/Block.h>
#include <minecpp/game/item/Item.h>
#include <minecpp/nbt/repository/v1/Repository.nbt.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/Item.h>
#include <minecpp/repository/State.h>

namespace minecpp::repository {

Block Block::g_instance;
BlockState BlockState::g_instance;

mb::emptyres load_repository_from_file(std::string_view filename)
{
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
      states.register_resource(int_state.tag, game::State(int_state.state.name, int_state.state.min_value,
                                                          int_state.state.max_value));
   }
   for (auto &enum_state : repo.enum_states) {
      states.register_resource(enum_state.tag, game::State(enum_state.state.name, enum_state.state.values));
   }

   auto &blocks        = Block::the();
   auto &state_manager = StateManager::the();
   int block_id        = 0;
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

   auto &items = Item::the();
   for (auto &nbt_item : repo.items) {
      game::item::Item item(game::item::Item::Details{
              .tag                     = nbt_item.tag,
              .max_stack_size          = nbt_item.item.max_item_stack,
              .is_block                = static_cast<bool>(nbt_item.item.is_block),
              .corresponding_block_tag = nbt_item.item.corresponding_block_tag,
      });
      items.register_resource(nbt_item.tag, item);
   }

   return mb::ok;
}

std::function<int(const game::State &)> make_compound_encoder(const nbt::CompoundContent &cnt)
{
   return [&cnt](const game::State &state) -> int {
      auto it = cnt.find(std::string(state.name()));
      if (it == cnt.end())
         return 0;

      auto &content = it->second;

      switch (content.tag_id) {
      case nbt::TagId::String: return state.index_from_value(content.as<std::string>());
      case nbt::TagId::Int: return state.index_from_value(content.as<int>());
      default: break;
      }
   };
}

int encode_block_by_tag(std::string_view tag)
{
   auto block_id = repository::Block::the().find_id_by_tag(std::string(tag)).unwrap();
   return repository::StateManager::the().block_base_state(static_cast<int>(block_id));
}

mb::result<nbt::repository::v1::Registry> load_network_registry_from_file(std::string_view filename)
{
   std::ifstream in_file(filename.data());
   if (!in_file.is_open()) {
      return mb::error("could not open file");
   }
   return std::move(minecpp::nbt::repository::v1::Registry::deserialize(in_file));
}

}// namespace minecpp::repository