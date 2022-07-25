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
   auto it = std::find_if(m_states.begin(), m_states.end(),
                          [&target](const State &state) { return state.name() == target; });
   if (it == m_states.end())
      return std::nullopt;

   return *it;
}

bool Block::has_state(std::string_view state) const
{
   return find_state(state) != std::nullopt;
}

std::string Block::state_value(std::string_view name, game::StateOffset state_id) const
{
   auto range = state_range(state_id);

   auto half_it = std::find_if(range.begin(), range.end(),
                               [name](const auto &state) { return state.first.name() == name; });

   return half_it.value();
}

}// namespace minecpp::game::block
