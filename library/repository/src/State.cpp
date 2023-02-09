#include <minecpp/repository/Block.h>
#include <minecpp/repository/State.h>
#include <vector>

namespace minecpp::repository {

std::tuple<int, int> StateManager::parse_block_id(game::BlockStateId block_id)
{
   auto id = block_id;
   while (id != 0 && !m_state_to_block_id.contains(id)) {
      --id;
   }
   return {m_state_to_block_id[id], block_id - id};
}

std::size_t id_to_required_side(game::BlockStateId id)
{
   for (std::size_t i = 4; i < std::numeric_limits<game::BlockStateId>::max(); i = 2 * i) {
      if (id <= i)
         return i;
   }
   assert(false && "unable to find appropriate size for resources");
   return 0;
}

void StateManager::put_state_info(game::BlockStateId id, game::BlockStateInfo info)
{
   assert(m_info.size() >= id);
   m_info[id] = info;
}

StateManager &StateManager::the()
{
   static StateManager instance;
   return instance;
}

const game::BlockStateInfo &StateManager::get_info(game::BlockStateId state_id) const
{
   return m_info[state_id];
}

void StateManager::add_state(int block_id, int state_count)
{
   m_state_to_block_id[m_top_state] = block_id;
   m_block_id_to_state[block_id]    = m_top_state;
   m_top_state += static_cast<game::BlockStateId>(state_count);
}

game::BlockStateId StateManager::block_base_state(game::BlockId block_id) const
{
   return m_block_id_to_state.at(block_id);
}

void StateManager::allocate_info_storage()
{
   m_info.resize(m_top_state);
}

}// namespace minecpp::repository