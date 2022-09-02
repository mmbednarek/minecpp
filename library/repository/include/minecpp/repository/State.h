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

   std::map<game::BlockStateId, game::BlockId> m_state_to_block_id;
   std::map<game::BlockId, game::BlockStateId> m_block_id_to_state;
   std::vector<bool> m_is_solid;
   game::BlockStateId m_top_state;

 public:
   std::tuple<game::BlockId, game::StateOffset> parse_block_id(game::BlockStateId block_id);

   [[nodiscard]] static constexpr StateManager &the()
   {
      return g_instance;
   }

   GETTER(top_state)

   void add_state(int block_id, int state_count)
   {
      m_state_to_block_id[m_top_state] = block_id;
      m_block_id_to_state[block_id]    = m_top_state;
      m_top_state += static_cast<game::BlockStateId>(state_count);
   }

   void cache_block_stats();

   [[nodiscard]] game::BlockStateId block_base_state(game::BlockId block_id) const
   {
      return m_block_id_to_state.at(block_id);
   }

   [[nodiscard]] bool is_solid(game::BlockStateId state_id) const;
};

}// namespace minecpp::repository

#endif//MINECPP_REPOSITORY_STATE_H
