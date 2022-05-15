#include <minecpp/game/block/block.h>

namespace minecpp::game::block {

std::size_t Block::state_count() const
{
   std::size_t result = 1;
   for (auto &state : m_states) { result *= state.value_count(); }
   return result;
}

}// namespace minecpp::game::block
