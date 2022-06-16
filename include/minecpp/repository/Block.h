#ifndef MINECPP_REPOSITORY_BLOCK_H
#define MINECPP_REPOSITORY_BLOCK_H
#include "Repository.h"
#include "State.h"
#include <functional>
#include <mb/result.h>
#include <minecpp/game/block/Block.h>
#include <minecpp/game/State.h>
#include <minecpp/nbt/Tag.h>

namespace minecpp::repository {

class Block : public Repository<game::block::Block, game::BlockId>
{
   static Block g_instance;

 public:
   constexpr static Block &the()
   {
      return g_instance;
   }
};

class BlockState : public Repository<game::State>
{
   static BlockState g_instance;

 public:
   constexpr static BlockState &the()
   {
      return g_instance;
   }
};

template<typename TFunc>
mb::result<game::BlockStateId> encode_state(game::BlockId block_id, TFunc fn)
{
   const auto &block = MB_TRY(Block::the().get_by_id(block_id));
   game::BlockStateId state_id{0};
   for (auto const &state : block) {
      state_id *= static_cast<game::BlockStateId>(state.value_count());
      state_id += fn(state);
   }
   return StateManager::the().block_base_state(block_id) + state_id;
}

std::optional<game::BlockStateId> set_state(game::BlockId block_id, int block_state,
                                                   std::string_view name, std::string_view value);

std::function<int(const game::State &)> make_compound_encoder(const nbt::CompoundContent &cnt);

int encode_block_by_tag(std::string_view tag);

template<typename... TRest>
game::BlockStateId encode_block_inner(const game::State &state,
                                      std::pair<std::string_view, std::string_view> field, TRest... values)
{
   if (state.name() == field.first) {
      return static_cast<game::BlockStateId>(state.index_from_value(field.second));
   }

   if constexpr (sizeof...(values) != 0)
      return encode_block_inner(state, values...);
   return 0;
}

template<typename... T>
game::BlockStateId encode_block_by_tag(std::string_view tag, T... values)
{
   auto block_id = repository::Block::the().find_id_by_tag(std::string(tag)).unwrap();
   return repository::encode_state(
                  block_id,
                  [values...](const game::State &state) { return encode_block_inner(state, values...); })
           .unwrap(0);
}

template<typename... T>
game::BlockStateId encode_block_state_by_id(game::BlockId block_id, T... values)
{
   return repository::encode_state(
                  block_id,
                  [values...](const game::State &state) { return encode_block_inner(state, values...); })
           .unwrap(0);
}

}// namespace minecpp::repository

#endif//MINECPP_REPOSITORY_BLOCK_H
