#include <minecpp/repository/state.h>
#include <vector>

namespace minecpp::repository {

StateManager StateManager::g_instance;

std::tuple<int, int> StateManager::parse_block_id(int block_id) {
   int id = block_id;
   while (id != 0 && !m_states.contains(id))  {
      --id;
   }
   return {m_states[id], block_id - id};
}

}