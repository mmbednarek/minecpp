#ifndef MINECPP_GAME_BLOCK_BLOCK_H
#define MINECPP_GAME_BLOCK_BLOCK_H
#include "material.h"
#include "state.h"
#include <minecpp/game/state.h>
#include <minecpp/util/string.h>
#include <string_view>
#include <utility>
#include <vector>

namespace minecpp::game::block {

class Block {
   std::string m_tag;

 public:
    explicit Block(std::string_view tag, std::vector<State> states) : m_tag(std::string(tag)), states(std::move(states)) {}

   template<typename... T>
   explicit Block(std::string_view tag, T... params) : m_tag(std::string(tag)) {
      if constexpr (sizeof...(T) > 0) {
         apply_options(params...);
      }
   }

   [[nodiscard]] std::string_view tag() const;

   std::vector<const Attribute *> attributes{};
   std::vector<State> states;
   const Material *material{};
   ColorId color;
   std::string_view loot = "";
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

   std::size_t state_count() {
      std::size_t result = 1;
      for (auto &state : states) {
         result *= state.value_count();
      }
      return result;
   }

    struct StateIterator {
        typename std::vector<game::State>::reverse_iterator it;
        int state;
        Block &block;

        StateIterator &operator++() {
           state /= it->value_count();
           ++it;
            return *this;
        }

        [[nodiscard]] std::tuple<game::State &, int> operator *() const {
            return {*it, state % it->value_count()};
        }

        bool operator==(const StateIterator &rhs) {
           return it == rhs.it;
        }
   };

   struct StateRange {
      Block &block;
      int state;

      StateIterator begin() {
         return StateIterator{block.states.rbegin(), state, block};
      }

      StateIterator end() {
         return StateIterator{block.states.rend(), 0, block};
      }
   };

   [[nodiscard]] constexpr StateRange state_range(int state) {
      return StateRange{*this, state};
   }


 private:
   template<typename F, typename... Others>
   constexpr void apply_options(F first, Others... others) {
      first(*this);
      if constexpr (sizeof...(Others) > 0) {
         apply_options(others...);
      }
   }
};

std::function<void(Block &)> with_material(const Material *mat);

std::function<void(Block &)> with_material(const Material *mat, ColorId color);

std::function<void(Block &)> with_material(const Material *mat, DyeColor color);

std::function<void(Block &)> with_does_not_block_movement();

std::function<void(Block &)> with_ticks_randomly();

std::function<void(Block &)> with_no_drop();

std::function<void(Block &)> with_not_solid();

std::function<void(Block &)> with_light_value(int value);

std::function<void(Block &)> with_slipperiness(float value);

std::function<void(Block &)> with_speed_factor(float value);

std::function<void(Block &)> with_jump_factor(float value);

std::function<void(Block &)> with_loot(std::string_view loot);

std::function<void(Block &)> with_durability(float both);

std::function<void(Block &)> with_durability(float hardness, float resistance);

std::function<void(Block &)> with_zero_durability();

std::function<void(Block &)> with_variable_opacity();

template<typename... T>
std::function<void(Block &)> with_attributes(T... attribs) {
   return [attribs...](Block &b) {
      b.attributes = {attribs...};
      std::sort(b.attributes.begin(), b.attributes.end(),
                [](const Attribute *a, const Attribute *b) {
                   return a->name() < b->name();
                });
   };
}

struct Properties {
   const Material *material = &Material::Air;
   ColorId color = ColorId::Air;
   float hardness = 1.0f;
   float resistance = 1.0f;
};

std::function<void(Block &)> with_properties(Properties props);

}// namespace minecpp::game::block

#endif //MINECPP_GAME_BLOCK_BLOCK_H