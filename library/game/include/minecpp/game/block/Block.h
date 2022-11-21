#ifndef MINECPP_GAME_BLOCK_BLOCK_H
#define MINECPP_GAME_BLOCK_BLOCK_H
#include "Material.h"
#include <minecpp/game/Game.h>
#include <minecpp/game/State.h>
#include <optional>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

namespace minecpp::game::block {

struct BlockStats
{
   const Material *material{};
   ColorId color{};
   std::string loot{};
   int light_value       = 0;
   float hardness        = 1.0f;
   float resistance      = 1.0f;
   float slipperiness    = 1.0f;
   float speed_factor    = 1.0f;
   float jump_factor     = 1.0f;
   bool blocks_movement  = true;
   bool no_drop          = false;
   bool ticks_randomly   = false;
   bool solid            = false;
   bool variable_opacity = false;
};

class Block
{
   std::string m_tag;
   std::vector<State> m_states;
   BlockStats m_stats;

 public:
   struct StateIterator
   {
      using vector_iterator   = typename std::vector<game::State>::const_reverse_iterator;
      using iterator_category = std::forward_iterator_tag;
      using difference_type   = std::ptrdiff_t;
      using value_type        = std::pair<const game::State &, int>;
      using pointer           = value_type *;
      using reference         = value_type &;

      vector_iterator it;
      game::StateOffset state;
      const Block &block;

      StateIterator(game::StateOffset state, const Block &block) :
          it{block.m_states.crbegin()},
          state{state},
          block{block}
      {
      }

      explicit StateIterator(const Block &block) :
          it{block.m_states.crend()},
          state{0},
          block{block}
      {
      }

      StateIterator &operator++()
      {
         state /= it->value_count();
         ++it;
         return *this;
      }

      [[nodiscard]] value_type operator*() const
      {
         return {*it, state % it->value_count()};
      }

      [[nodiscard]] auto value() const
      {
         auto current_value = operator*();
         return current_value.first.value_from_index(current_value.second);
      }

      bool operator==(const StateIterator &rhs) const
      {
         return it == rhs.it;
      }

      bool operator!=(const StateIterator &rhs) const
      {
         return it != rhs.it;
      }
   };

   struct StateRange
   {
      const Block &block;
      game::StateOffset state;

      StateIterator begin()
      {
         return StateIterator{state, block};
      }

      StateIterator end()
      {
         return StateIterator{block};
      }
   };

   Block(std::string_view tag, std::vector<State> states, BlockStats stats = {}) :
       m_tag(std::string(tag)),
       m_states(std::move(states)),
       m_stats(std::move(stats))
   {
      if (tag == "minecraft:air") {
         m_stats.material = &Material::Air;
         return;
      }
      m_stats.material = &Material::Rock;
   }

   [[nodiscard]] std::optional<State> find_state(std::string_view state) const;
   [[nodiscard]] bool has_state(std::string_view state) const;
   [[nodiscard]] std::string state_value(std::string_view name, game::StateOffset state_id) const;

   [[nodiscard]] std::size_t state_count() const;

   [[nodiscard]] constexpr StateRange state_range(game::StateOffset state) const
   {
      return StateRange{*this, state};
   }

   [[nodiscard]] constexpr const std::string &tag() const
   {
      return m_tag;
   }

   [[nodiscard]] constexpr const BlockStats &stats() const
   {
      return m_stats;
   }

   [[nodiscard]] auto begin() const
   {
      return m_states.begin();
   }

   [[nodiscard]] auto end() const
   {
      return m_states.end();
   }

   [[nodiscard]] bool is_single_state() const
   {
      return m_states.empty();
   }
};

}// namespace minecpp::game::block

#endif//MINECPP_GAME_BLOCK_BLOCK_H