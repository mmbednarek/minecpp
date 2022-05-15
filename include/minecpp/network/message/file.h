#pragma once
#include <boost/endian/conversion.hpp>
#include <iostream>
#include <minecpp/game/item/item.h>
#include <minecpp/game/item/recipe.h>
#include <minecpp/nbt/tag.h>

namespace minecpp::network::message {

class Reader
{
 public:
   explicit Reader(std::istream &s);

   uint8_t read_byte();
   int read_varint();
   std::string read_string();
   float read_float();
   double read_double();
   nbt::CompoundContent read_nbt_tag();

   game::item::Recipe read_recipe();
   game::item::Recipe read_recipe_shaped();
   game::item::Recipe read_recipe_shapeless();
   game::item::Recipe read_recipe_heat_treatment(game::item::RecipeType type);
   game::item::Recipe read_recipe_stone_cutting();

   game::item::ItemStack read_stack();
   game::item::StackVariants read_stack_variants();

   std::string get_hex_data();

   template<typename T>
   T read_big_endian()
   {
      T result;
      s.read((char *) &result, sizeof(T));
      result = boost::endian::big_to_native(result);
      return result;
   }

   uint64_t read_long();

 private:
   std::istream &s;
};

}// namespace minecpp::network::message
