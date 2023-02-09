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
   std::map<game::BlockStateId, game::BlockId> m_state_to_block_id;
   std::map<game::BlockId, game::BlockStateId> m_block_id_to_state;
   std::vector<game::BlockStateInfo> m_info;
   game::BlockStateId m_top_state;

 public:
   std::tuple<game::BlockId, game::StateOffset> parse_block_id(game::BlockStateId block_id);

   [[nodiscard]] static StateManager &the();

   GETTER(top_state)

   void add_state(int block_id, int state_count);
   void allocate_info_storage();
   void put_state_info(game::BlockStateId id, game::BlockStateInfo info);

   [[nodiscard]] game::BlockStateId block_base_state(game::BlockId block_id) const;
   [[nodiscard]] const game::BlockStateInfo &get_info(game::BlockStateId state_id) const;
};

}// namespace minecpp::repository

#endif//MINECPP_REPOSITORY_STATE_H
