#include "minecpp/repository/Repository.h"
#include <fstream>
#include <minecpp/game/block/Block.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/item/Item.h>
#include <minecpp/nbt/repository/v1/Repository.schema.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/Item.h>
#include <minecpp/repository/State.h>

namespace minecpp::repository {

Block Block::s_instance;
BlockState BlockState::s_instance;

mb::emptyres load_repository_from_file(std::string_view filename)
{
   std::ifstream in_file(filename.data());
   if (!in_file.is_open()) {
      return mb::error("could not open file");
   }
   auto repo = minecpp::nbt::repository::v1::Repository::deserialize(in_file);

   auto &states = BlockState::the();
   for (auto &bool_state : repo.bool_properties) {
      states.register_resource(bool_state.tag, game::State(bool_state.property.name));
   }
   for (auto &int_state : repo.int_properties) {
      states.register_resource(int_state.tag,
                               game::State(int_state.property.name, int_state.property.min_value,
                                           int_state.property.max_value));
   }
   for (auto &enum_state : repo.enum_properties) {
      states.register_resource(enum_state.tag,
                               game::State(enum_state.property.name, enum_state.property.values));
   }

   auto &blocks        = Block::the();
   auto &state_manager = StateManager::the();
   for (auto &entry : repo.blocks) {
      std::vector<game::State> block_states;
      int block_state_count = 1;
      for (const auto &tag : entry.block.property_tags) {
         auto state = states.find_by_tag(tag);
         if (state.has_failed())
            return std::move(state.err());

         block_states.push_back(*state);
         block_state_count *= state->value_count();
      }
      state_manager.add_state(entry.id, block_state_count);

      game::block::BlockStats stats{};
      blocks.register_resource(entry.tag, game::block::Block(entry.tag, block_states, stats));
   }

   state_manager.allocate_info_storage();

   for (const auto &entry : repo.block_states) {
      state_manager.put_state_info(static_cast<game::BlockStateId>(entry.id),
                                   game::BlockStateInfo::from_nbt(entry.state));
   }

   auto &items = Item::the();
   for (auto &entry : repo.items) {
      game::item::Item item(game::item::Item::Details{
              .tag                     = entry.tag,
              .max_stack_size          = entry.item.max_item_stack,
              .is_block                = static_cast<bool>(entry.item.is_block),
              .corresponding_block_tag = entry.item.corresponding_block_tag,
      });
      items.register_resource(entry.tag, item);
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

      return 0;
   };
}

game::BlockStateId encode_block_by_tag(std::string_view tag)
{
   auto block_id = repository::Block::the().find_id_by_tag(std::string(tag)).unwrap();
   return repository::StateManager::the().block_base_state(static_cast<int>(block_id));
}

std::optional<game::BlockStateId> set_state(game::BlockId block_id, game::StateOffset block_state,
                                            std::string_view name, std::string_view value)
{
   auto block = Block::the().get_by_id(block_id);
   if (block.has_failed())
      return std::nullopt;

   std::vector<std::pair<game::BlockStateId, game::BlockStateId>> values;
   values.reserve(block->state_count());

   for (auto const &[state, state_index] : block->state_range(block_state)) {
      if (state.name() != name) {
         values.emplace_back(static_cast<game::BlockStateId>(state.value_count()),
                             static_cast<game::BlockStateId>(state_index));
         continue;
      }

      values.emplace_back(static_cast<game::BlockStateId>(state.value_count()),
                          static_cast<game::BlockStateId>(state.index_from_value(value)));
   }

   game::BlockStateId state_id{0};
   std::for_each(values.crbegin(), values.crend(), [&state_id](auto pair) {
      state_id *= pair.first;
      state_id += pair.second;
   });

   return StateManager::the().block_base_state(block_id) + state_id;
}

mb::result<nbt::repository::v1::Registry> load_network_registry_from_file(std::string_view filename)
{
   std::ifstream in_file(filename.data());
   if (!in_file.is_open()) {
      return mb::error("could not open file");
   }
   return minecpp::nbt::repository::v1::Registry::deserialize(in_file);
}

BlockIds &BlockIds::the()
{
   static BlockIds instance{};
   if (not instance.m_initialised) {
      instance.init();
   }
   return instance;
}

#define REGISTER_BLOCK_ID(identifier, tag_name)         \
   {                                                    \
      auto res = Block::the().find_id_by_tag(tag_name); \
      if (res.has_failed()) {                           \
         return;                                        \
      }                                                 \
      (identifier) = *res;                              \
   }

void BlockIds::init()
{
   m_initialised = false;
   REGISTER_BLOCK_ID(Air, "minecraft:air");
   REGISTER_BLOCK_ID(Stone, "minecraft:stone");
   REGISTER_BLOCK_ID(Water, "minecraft:water");
   REGISTER_BLOCK_ID(Torch, "minecraft:torch");
   REGISTER_BLOCK_ID(WallTorch, "minecraft:wall_torch");
   REGISTER_BLOCK_ID(OakDoor, "minecraft:oak_door");

   m_initialised = true;
}

}// namespace minecpp::repository