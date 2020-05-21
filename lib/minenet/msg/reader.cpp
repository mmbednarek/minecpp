#include "reader.h"
#include <boost/endian/conversion.hpp>
#include <nbt/parser.h>
#include <stdexcept>

namespace MineNet::Message {

Reader::Reader(std::istream &s) : s(s) {}

uint8_t Reader::read_byte() {
   uint8_t result;
   s.read((char *)&result, sizeof(uint8_t));
   return result;
}

int Reader::read_varint() {
   uint32_t result = 0u;
   uint32_t shift = 0u;

   for (;;) {
      uint8_t b = read_byte();
      if (b & 0x80u) {
         result |= (b & 0x7Fu) << shift;
         shift += 7u;
         continue;
      }
      result |= b << shift;
      break;
   }
   return result;
}

std::string Reader::read_string() {
   int size = read_varint();
   char buff[size];
   s.read(buff, size);
   return std::string(buff, size);
}

float Reader::read_float() {
   static_assert(sizeof(uint32_t) == sizeof(float));
   uint32_t value;
   s.read((char *)&value, sizeof(uint32_t));
   value = boost::endian::big_to_native(value);
   return *reinterpret_cast<float *>(&value);
}

NBT::TagPtr Reader::read_nbt_tag() {
   NBT::Parser p(s);
   return p.read_tag();
}

Game::Recipe Reader::read_recipe() {
   auto kind = read_string();
   auto name = read_string();

   if (kind == "minecraft:crafting_shaped") {
      return read_recipe_shaped();
   } else if (kind == "minecraft:crafting_shapeless") {
      return read_recipe_shapeless();
   } else if (kind == "minecraft:smelting") {
      return read_recipe_heat_treatment(Game::RecipeType::Smelting);
   } else if (kind == "minecraft:blasting") {
      return read_recipe_heat_treatment(Game::RecipeType::Blasting);
   } else if (kind == "minecraft:smoking") {
      return read_recipe_heat_treatment(Game::RecipeType::Smoking);
   } else if (kind == "minecraft:campfire_cooking") {
      return read_recipe_heat_treatment(Game::RecipeType::CampfireCooking);
   } else if (kind == "minecraft:stonecutting") {
      return read_recipe_stone_cutting();
   } else {
      return Game::Recipe(Game::ItemStack{.id = 0, .amount = 0},
                          Game::RecipeType::Special);
   }
}
Game::Recipe Reader::read_recipe_shaped() {
   auto width = read_varint();
   auto height = read_varint();
   auto group = read_string();

   auto num = width * height;

   std::vector<Game::StackVariants> ingredients(num);
   for (int i = 0; i < num; i++) {
      ingredients[i] = read_stack_variants();
   }
   auto crafted = read_stack();

   return Game::Recipe(crafted, group,
                       Game::Recipe::CraftingShaped{
                           .width = width,
                           .height = height,
                           .ingredients = std::move(ingredients),
                       });
}

Game::Recipe Reader::read_recipe_shapeless() {
   auto group = read_string();
   auto num = read_varint();

   std::vector<Game::StackVariants> ingredients(num);
   for (int i = 0; i < num; i++) {
      ingredients[i] = read_stack_variants();
   }
   auto outcome = read_stack();

   return Game::Recipe(outcome, group,
                       Game::Recipe::CraftingShapeless{
                           .ingredients = std::move(ingredients),
                       });
}

Game::Recipe Reader::read_recipe_heat_treatment(Game::RecipeType type) {
   auto group = read_string();
   auto ingredient = read_stack_variants();
   auto outcome = read_stack();
   auto experience = read_float();
   auto cooking_time = read_varint();
   return Game::Recipe(outcome, group, type,
                       Game::Recipe::HeatTreatment{
                           .ingredient = std::move(ingredient),
                           .experience = experience,
                           .cooking_time = cooking_time,
                       });
}

Game::Recipe Reader::read_recipe_stone_cutting() {
   auto group = read_string();
   auto ingredient = read_stack_variants();
   auto outcome = read_stack();
   return Game::Recipe(outcome, group,
                       Game::Recipe::StoneCutting{
                           .ingredient = std::move(ingredient),
                       });
}

Game::StackVariants Reader::read_stack_variants() {
   auto num_variants = read_varint();
   Game::StackVariants result(num_variants);
   for (int v = 0; v < num_variants; v++) {
      result[v] = read_stack();
   }
   return result;
}

Game::ItemStack Reader::read_stack() {
   auto not_empty = read_byte();
   if (!not_empty) {
      return Game::ItemStack{
          .id = 0,
          .amount = 0,
      };
   }
   auto id = read_varint();
   auto amount = read_byte();
   auto additional_data = read_nbt_tag();
   return Game::ItemStack{
       .id = id,
       .amount = amount,
   };
}

} // namespace MineNet::Message
