#ifndef MINECPP_REPOSITORY_STATE_H
#define MINECPP_REPOSITORY_STATE_H
#include <tuple>
#include <map>
#include <span>
#include <minecpp/util/util.h>

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

   std::map<int, int> m_state_to_block_id;
   std::map<int, int> m_block_id_to_state;
   std::size_t m_state_count;
 public:

   std::tuple<int, int> parse_block_id(int block_id);

   [[nodiscard]] static constexpr StateManager &the() {
      return g_instance;
   }

   GETTER(state_count)

   void add_state(int block_id, int state_count) {
      m_state_to_block_id[static_cast<int>(m_state_count)] = block_id;
      m_block_id_to_state[block_id] = static_cast<int>(m_state_count);
      m_state_count += state_count;
   }

   [[nodiscard]] int block_base_state(int block_id) const {
      return m_block_id_to_state.at(block_id);
   }
};

}

#endif//MINECPP_REPOSITORY_STATE_H
