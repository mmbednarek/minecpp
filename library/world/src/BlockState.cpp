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

}// namespace minecpp::world