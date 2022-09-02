#include <minecpp/repository/State.h>
#include <minecpp/repository/Block.h>
#include <vector>

namespace minecpp::repository {

StateManager StateManager::g_instance;

std::tuple<int, int> StateManager::parse_block_id(game::BlockStateId block_id)
{
   auto id = block_id;
   while (id != 0 && !m_state_to_block_id.contains(id)) {
      --id;
   }
   return {m_state_to_block_id[id], block_id - id};
}

void StateManager::cache_block_stats()
{
   m_is_solid.resize(m_top_state);
   for (auto [state, block_id] : m_state_to_block_id) {
      auto block = Block::the().get_by_id(block_id);
      if (block.has_failed()) {
         continue;
      }

      m_is_solid[state] = block->stats().solid;
   }
}

bool StateManager::is_solid(game::BlockStateId state_id) const
{
   if  (state_id >= m_is_solid.size())
      return false;
   return m_is_solid.at(state_id);
}

}// namespace minecpp::repository