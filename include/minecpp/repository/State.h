#ifndef MINECPP_REPOSITORY_STATE_H
#define MINECPP_REPOSITORY_STATE_H
#include "mb/result.h"
#include <map>
#include <minecpp/game/Game.h>
#include <minecpp/util/Util.h>
#include <span>
#include <tuple>

namespace minecpp::repository {

template<typename TInIter, typename TOutIter>
void parse_state(TInIter inBeg, TInIter inEnd, TOutIter outBeg, int encoded)
{
   for (; inBeg != inEnd; ++inBeg, ++outBeg) {
      auto x  = *inBeg;
      *outBeg = encoded % x;
      encoded /= x;
   }
}

class StateManager
{
   static StateManager g_instance;

   std::map<game::BlockState, int> m_state_to_block_id;
   std::map<int, game::BlockState> m_block_id_to_state;
   game::BlockState m_top_state;

 public:
   std::tuple<int, int> parse_block_id(game::BlockState block_id);

   [[nodiscard]] static constexpr StateManager &the()
   {
      return g_instance;
   }

   GETTER(top_state)

   void add_state(int block_id, int state_count)
   {
      m_state_to_block_id[static_cast<int>(m_top_state)] = block_id;
      m_block_id_to_state[block_id]                      = m_top_state;
      m_top_state += static_cast<game::BlockState>(state_count);
   }

   [[nodiscard]] game::BlockState block_base_state(int block_id) const
   {
      return m_block_id_to_state.at(block_id);
   }
};

}// namespace minecpp::repository

#endif//MINECPP_REPOSITORY_STATE_H
