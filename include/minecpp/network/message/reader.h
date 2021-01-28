#pragma once
#include <boost/endian/conversion.hpp>
#include <iostream>
#include <minecpp/game/item/item.h>
#include <minecpp/game/item/recipe.h>
#include <minecpp/nbt/tag.h>

namespace minecpp::network::message {

class Reader {
 public:
   explicit Reader(std::istream &s);

   uint8_t read_byte();
   int read_varint();
   std::string read_string();
   float read_float();
   double read_double();
   nbt::CompoundContent read_nbt_tag();

   game::Recipe read_recipe();
   game::Recipe read_recipe_shaped();
   game::Recipe read_recipe_shapeless();
   game::Recipe read_recipe_heat_treatment(game::RecipeType type);
   game::Recipe read_recipe_stone_cutting();

   game::ItemStack read_stack();
   game::StackVariants read_stack_variants();

   std::string get_hex_data();

   template <typename T> T read_big_endian() {
      T result;
      s.read((char *)&result, sizeof(T));
      result = boost::endian::big_to_native(result);
      return result;
   }

 private:
   std::istream &s;
};

} // namespace minecpp::network::Message
