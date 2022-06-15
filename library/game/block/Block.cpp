#include <minecpp/game/block/Block.h>

namespace minecpp::game::block {

std::size_t Block::state_count() const
{
   std::size_t result = 1;
   for (auto &state : m_states) {
      result *= state.value_count();
   }
   return result;
}

std::optional<State> Block::find_state(std::string_view target) const
{
   auto it = std::find_if(m_states.begin(), m_states.end(), [&target](const State &state) {
      return state.name() == target;
   });
   if (it == m_states.end())
      return std::nullopt;

   return *it;
}

}// namespace minecpp::game::block
