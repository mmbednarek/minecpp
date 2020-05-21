#pragma once
#include <boost/endian/conversion.hpp>
#include <game/items/item.h>
#include <game/items/recipe.h>
#include <iostream>
#include <nbt/tag.h>

namespace MineNet::Message {

class Reader {
 public:
   explicit Reader(std::istream &s);

   uint8_t read_byte();
   int read_varint();
   std::string read_string();
   float read_float();
   NBT::TagPtr read_nbt_tag();

   Game::Recipe read_recipe();
   Game::Recipe read_recipe_shaped();
   Game::Recipe read_recipe_shapeless();
   Game::Recipe read_recipe_heat_treatment(Game::RecipeType type);
   Game::Recipe read_recipe_stone_cutting();

   Game::ItemStack read_stack();
   Game::StackVariants read_stack_variants();

   template <typename T> T read_big_endian() {
      T result;
      s.read((char *)&result, sizeof(T));
      result = boost::endian::big_to_native(result);
      return result;
   }

 private:
   std::istream &s;
};

} // namespace MineNet::Message
