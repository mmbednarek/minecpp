#ifndef MINECPP_REPOSITORY_STATE_H
#define MINECPP_REPOSITORY_STATE_H
#include <tuple>
#include <map>
#include <span>

namespace minecpp::repository {

template<typename TInIter, typename TOutIter>
void parse_state(TInIter inBeg, TInIter inEnd, TOutIter outBeg, int encoded) {
   for (; inBeg != inEnd; ++inBeg, ++outBeg) {
      auto x = *inBeg;
      *outBeg = encoded % x;
      encoded /= x;
   }
}

class StateManager {
   static StateManager g_instance;

   std::map<int, int> m_states;
 public:
   std::tuple<int, int> parse_block_id(int block_id);

   static constexpr StateManager &the() {
      return g_instance;
   }

   void add_state(int state_id, int block_id) {
      m_states[state_id] = block_id;
   }
};

}

#endif//MINECPP_REPOSITORY_STATE_H
