#include <minecpp/repository/state.h>
#include <vector>

namespace minecpp::repository {

StateManager StateManager::g_instance;

std::tuple<int, int> StateManager::parse_block_id(int block_id)
{
   int id = block_id;
   while (id != 0 && !m_state_to_block_id.contains(id)) {
      --id;
   }
   return {m_state_to_block_id[id], block_id - id};
}

}// namespace minecpp::repository