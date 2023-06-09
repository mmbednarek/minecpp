#pragma once
#include <boost/endian/conversion.hpp>
#include <iostream>
#include <minecpp/container/BasicBuffer.hpp>
#include <minecpp/game/item/Item.h>
#include <minecpp/game/item/Recipe.h>
#include <minecpp/nbt/Tag.h>

namespace minecpp::network::message {

class Reader
{
 public:
   explicit Reader(std::istream &s);

   uint8_t read_byte();
   int read_varint();
   std::string read_string();
   void read_bytes(std::uint8_t *data, std::size_t size);
   container::Buffer read_buffer();
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
      m_stream.read((char *) &result, sizeof(T));
      result = boost::endian::big_to_native(result);
      return result;
   }

   uint64_t read_long();

   short read_short();

 private:
   std::istream &m_stream;
};

}// namespace minecpp::network::message
