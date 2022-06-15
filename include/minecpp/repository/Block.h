#ifndef MINECPP_REPOSITORY_BLOCK_H
#define MINECPP_REPOSITORY_BLOCK_H
#include "Repository.h"
#include "State.h"
#include <functional>
#include <minecpp/game/block/Block.h>
#include <minecpp/game/State.h>
#include <minecpp/nbt/Tag.h>

namespace minecpp::repository {

class Block : public Repository<game::block::Block>
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
mb::result<int> encode_state(int block_id, TFunc fn)
{
   const auto &block = MB_TRY(Block::the().get_by_id(block_id));
   auto state_id     = 0;
   for (auto const &state : block) {
      state_id *= state.value_count();
      state_id += fn(state);
   }
   return StateManager::the().block_base_state(block_id) + state_id;
}

std::function<int(const game::State &)> make_compound_encoder(const nbt::CompoundContent &cnt);

int encode_block_by_tag(std::string_view tag);

template<typename TField, typename... TRest>
game::BlockState encode_block_inner(const game::State &state, TField field, TRest... values)
{
   if (state.name() == field.first) {
      return state.index_from_value(field.second);
   }

   if constexpr (sizeof...(values) != 0)
      return encode_block_inner(state, values...);
   return 0;
}

template<typename... T>
game::BlockState encode_block_by_tag(std::string_view tag, T... values)
{
   auto block_id = repository::Block::the().find_id_by_tag(std::string(tag)).unwrap();
   return repository::encode_state(
                  static_cast<game::BlockState>(block_id),
                  [values...](const game::State &state) { return encode_block_inner(state, values...); })
           .unwrap();
}

}// namespace minecpp::repository

#endif//MINECPP_REPOSITORY_BLOCK_H
