#include <minecpp/game/block/block.h>

namespace Game::Block {

std::string_view Block::tag() const { return _tag; }

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

std::function<void(Block &)> with_properties(Properties props) {
   return [props](Block &b) {
      b.material = props.material;
      b.color = props.color;
      b.hardness = props.hardness;
      b.resistance = props.resistance;
   };
}

} // namespace Game::Block
