#include <minecpp/world/BlockState.h>
#include <tuple>

namespace minecpp::world {

using repository::StateManager;

BlockState::BlockState(game::BlockStateId id)
{
   std::tie(m_block_id, m_state_offset) = StateManager::the().parse_block_id(id);
}

BlockState::BlockState(game::BlockId block_id, game::StateOffset state_offset) :
    m_block_id{block_id},
    m_state_offset{state_offset}
{
}

game::BlockStateId BlockState::block_state_id() const
{
   return repository::StateManager::the().block_base_state(m_block_id) +
          static_cast<game::BlockStateId>(m_state_offset);
}

template<>
[[nodiscard]] std::optional<bool> BlockState::get(std::string_view name) const
{
   auto block = repository::Block::the().get_by_id(m_block_id);
   if (block.has_failed())
      return std::nullopt;

   return block->state_value(name, m_state_offset) == "true";
};

template<>
bool BlockState::set(std::string_view name, bool value)
{
   auto block = repository::Block::the().get_by_id(m_block_id);
   if (block.has_failed())
      return false;

   std::vector<std::pair<int, int>> values;
   values.reserve(block->state_count());

   for (auto const &[state, state_index] : block->state_range(m_state_offset)) {
      if (state.name() != name) {
         values.emplace_back(static_cast<game::BlockStateId>(state.value_count()),
                             static_cast<game::BlockStateId>(state_index));
         continue;
      }

      values.emplace_back(static_cast<game::BlockStateId>(state.value_count()),
                          static_cast<game::BlockStateId>(state.index_from_value(value ? "true" : "false")));
   }

   m_state_offset = 0;
   std::for_each(values.crbegin(), values.crend(), [this](auto pair) {
      m_state_offset *= pair.first;
      m_state_offset += pair.second;
   });

   return true;
};

}// namespace minecpp::world
