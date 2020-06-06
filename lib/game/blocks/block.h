#pragma once
#include "material.h"
#include "state.h"
#include <string_view>
#include <vector>

namespace Game::Block {

class Block {
   std::string_view _tag;

 public:
   template <typename... T>
   explicit Block(std::string_view tag, T... params) : _tag(tag) {
      if constexpr (sizeof...(T) > 0) {
         apply_options(params...);
      }
   }

   [[nodiscard]] std::string_view tag() const;

   std::vector<const Attribute *> attributes{};
   const Material *material;
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

 private:
   template <typename F, typename... Others>
   constexpr void apply_options(F first, Others... others) {
      first(*this);
      if constexpr (sizeof...(Others) > 0) {
         apply_options(others...);
      }
   }
};

std::function<void(Block &)> with_material(const Material *mat) {
   return [mat](Block &b) {
      b.material = mat;
      b.color = mat->color;
      b.blocks_movement = b.material->blocks_movement;
      b.solid = b.material->is_solid;
   };
}

std::function<void(Block &)> with_material(const Material *mat, ColorId color) {
   return [mat, color](Block &b) {
      b.material = mat;
      b.color = color;
      b.blocks_movement = b.material->blocks_movement;
      b.solid = b.material->is_solid;
   };
}

std::function<void(Block &)> with_material(const Material *mat,
                                           DyeColor color) {
   return [mat, color](Block &b) {
      b.material = mat;
      b.color = dye_color_id(color);
      b.blocks_movement = b.material->blocks_movement;
      b.solid = b.material->is_solid;
   };
}

std::function<void(Block &)> with_does_not_block_movement() {
   return [](Block &b) { b.blocks_movement = false; };
}

std::function<void(Block &)> with_ticks_randomly() {
   return [](Block &b) { b.ticks_randomly = true; };
}

std::function<void(Block &)> with_no_drop() {
   return [](Block &b) { b.no_drop = true; };
}

std::function<void(Block &)> with_not_solid() {
   return [](Block &b) { b.solid = false; };
}

std::function<void(Block &)> with_hardness(float hardness) {
   return [hardness](Block &b) { b.hardness = hardness; };
}

std::function<void(Block &)> with_resistance(float resistance) {
   return [resistance](Block &b) { b.resistance = resistance; };
}

std::function<void(Block &)> with_light_value(int value) {
   return [value](Block &b) { b.light_value = value; };
}

std::function<void(Block &)> with_slipperiness(float value) {
   return [value](Block &b) { b.slipperiness = value; };
}

std::function<void(Block &)> with_speed_factor(float value) {
   return [value](Block &b) { b.speed_factor = value; };
}

std::function<void(Block &)> with_jump_factor(float value) {
   return [value](Block &b) { b.jump_factor = value; };
}

std::function<void(Block &)> with_loot(std::string_view loot) {
   return [loot](Block &b) { b.loot = loot; };
}

std::function<void(Block &)> with_durability(float both) {
   return [both](Block &b) {
      b.hardness = both;
      b.resistance = both;
   };
}

std::function<void(Block &)> with_durability(float hardness, float resistance) {
   return [hardness, resistance](Block &b) {
      b.hardness = hardness;
      b.resistance = resistance;
   };
}

std::function<void(Block &)> with_zero_durability() {
   return [](Block &b) {
      b.hardness = 0.0f;
      b.resistance = 0.0f;
   };
}

std::function<void(Block &)> with_variable_opacity() {
   return [](Block &b) { b.variable_opacity = true; };
}

template <typename... T>
std::function<void(Block &)> with_attributes(T... attribs) {
   return [attribs...](Block &b) { b.attributes = {attribs...}; };
}

struct Properties {
   const Material *material = &Material::Air;
   ColorId color = ColorId::Air;
   float hardness = 1.0f;
   float resistance = 1.0f;
};

std::function<void(Block &)> with_properties(Properties props) {
   return [props](Block &b) {
      b.material = props.material;
      b.color = props.color;
      b.hardness = props.hardness;
      b.resistance = props.resistance;
   };
}

} // namespace Game::Block
