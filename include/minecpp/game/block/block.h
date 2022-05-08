#ifndef MINECPP_GAME_BLOCK_BLOCK_H
#define MINECPP_GAME_BLOCK_BLOCK_H
#include "material.h"
#include <minecpp/game/state.h>
#include <minecpp/util/string.h>
#include <string_view>
#include <utility>
#include <vector>

namespace minecpp::game::block {

struct BlockStats {
   const Material *material{};
   ColorId color{};
   std::string loot{};
   int light_value = 0;
   float hardness = 1.0f;
   float resistance = 1.0f;
   float slipperiness = 1.0f;
   float speed_factor = 1.0f;
   float jump_factor = 1.0f;
   bool blocks_movement = true;
   bool no_drop = false;
   bool ticks_randomly = false;
   bool solid = true;
   bool variable_opacity = false;
};

class Block {
   std::string m_tag;
   std::vector<State> m_states;
   BlockStats m_stats;

 public:
   struct StateIterator {
      typename std::vector<game::State>::const_reverse_iterator it;
      int state;
      const Block &block;

      StateIterator &operator++() {
         state /= it->value_count();
         ++it;
         return *this;
      }

      [[nodiscard]] std::tuple<const game::State &, int> operator*() const {
         return {*it, state % it->value_count()};
      }

      bool operator==(const StateIterator &rhs) const {
         return it == rhs.it;
      }
   };

   struct StateRange {
      const Block &block;
      int state;

      StateIterator begin() {
         return StateIterator{block.m_states.crbegin(), state, block};
      }

      StateIterator end() {
         return StateIterator{block.m_states.crend(), 0, block};
      }
   };

   explicit Block(std::string_view tag, std::vector<State> states, const BlockStats &stats={}) : m_tag(std::string(tag)), m_states(std::move(states)), m_stats(stats) {
      if (tag == "minecraft:air") {
         m_stats.material = &Material::Air;
         return;
      }
      m_stats.material = &Material::Rock;
   }

   [[nodiscard]] std::size_t state_count() const;

   [[nodiscard]] constexpr StateRange state_range(int state) const {
      return StateRange{*this, state};
   }

   [[nodiscard]] constexpr const std::string &tag() const {
      return m_tag;
   }

   [[nodiscard]] constexpr const BlockStats &stats() const {
      return m_stats;
   }

   [[nodiscard]] auto begin() const {
      return m_states.begin();
   }

   [[nodiscard]] auto end() const {
      return m_states.end();
   }

   [[nodiscard]] bool is_single_state() const {
      return m_states.empty();
   }
};

}// namespace minecpp::game::block

#endif//MINECPP_GAME_BLOCK_BLOCK_H