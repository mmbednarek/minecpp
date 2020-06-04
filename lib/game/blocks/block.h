#pragma once
#include "state.h"
#include <string_view>
#include <vector>

namespace Game::Block {

class Block {
   std::string_view _tag;
   State _state{};

 public:
   Block(std::string_view tag, State state);

   template <typename... T>
   explicit Block(std::string_view tag, T... params) : _tag(tag) {
      if constexpr (sizeof...(T) > 0) {
         apply_options(params...);
      }
   }

   [[nodiscard]] std::string_view tag() const;

   float hardness = 1.0f;
   float resistance = 1.0f;

 private:
   template <typename F, typename... Others>
   constexpr void apply_options(F first, Others... others) {
      first(*this);
      if constexpr (sizeof...(Others) > 0) {
         apply_options(others...);
      }
   }
};

std::function<void(Block &)> with_hardness(float hardness) {
   return [hardness](Block &b) { b.hardness = hardness; };
}

std::function<void(Block &)> with_durability(float hardness, float resistance) {
   return [hardness, resistance](Block &b) {
      b.hardness = hardness;
      b.resistance = resistance;
   };
}

} // namespace Game::Block
