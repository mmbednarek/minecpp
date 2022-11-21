#include <boost/endian/conversion.hpp>
#include <minecpp/nbt/Parser.h>
#include <minecpp/network/message/File.h>
#include <stdexcept>

namespace minecpp::network::message {

Reader::Reader(std::istream &s) :
    m_stream(s)
{
}

uint8_t Reader::read_byte()
{
   uint8_t result;
   m_stream.read((char *) &result, sizeof(uint8_t));
   return result;
}

int Reader::read_varint()
{
   uint32_t result = 0u;
   uint32_t shift  = 0u;

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

std::string Reader::read_string()
{
   int size = read_varint();
   char buff[size];
   m_stream.read(buff, size);
   return {buff, static_cast<std::size_t>(size)};
}

float Reader::read_float()
{
   static_assert(sizeof(uint32_t) == sizeof(float));
   uint32_t value;
   m_stream.read((char *) &value, sizeof(uint32_t));
   value = boost::endian::big_to_native(value);
   return *reinterpret_cast<float *>(&value);
}

double Reader::read_double()
{
   static_assert(sizeof(uint64_t) == sizeof(double));
   uint64_t value;
   m_stream.read((char *) &value, sizeof(uint64_t));
   value = boost::endian::big_to_native(value);
   return *reinterpret_cast<double *>(&value);
}

nbt::CompoundContent Reader::read_nbt_tag()
{
   nbt::Parser p(m_stream);
   return p.read_tag().content.as<nbt::CompoundContent>();
}

game::item::Recipe Reader::read_recipe()
{
   auto kind = read_string();
   auto name = read_string();

   if (kind == "minecraft:crafting_shaped") {
      return read_recipe_shaped();
   } else if (kind == "minecraft:crafting_shapeless") {
      return read_recipe_shapeless();
   } else if (kind == "minecraft:smelting") {
      return read_recipe_heat_treatment(game::item::RecipeType::Smelting);
   } else if (kind == "minecraft:blasting") {
      return read_recipe_heat_treatment(game::item::RecipeType::Blasting);
   } else if (kind == "minecraft:smoking") {
      return read_recipe_heat_treatment(game::item::RecipeType::Smoking);
   } else if (kind == "minecraft:campfire_cooking") {
      return read_recipe_heat_treatment(game::item::RecipeType::CampfireCooking);
   } else if (kind == "minecraft:stonecutting") {
      return read_recipe_stone_cutting();
   } else {
      return game::item::Recipe(game::item::ItemStack{.id = 0, .amount = 0}, game::item::RecipeType::Special);
   }
}

game::item::Recipe Reader::read_recipe_shaped()
{
   auto width  = read_varint();
   auto height = read_varint();
   auto group  = read_string();

   auto num = width * height;

   std::vector<game::item::StackVariants> ingredients(num);
   for (int i = 0; i < num; i++) {
      ingredients[i] = read_stack_variants();
   }
   auto crafted = read_stack();

   return game::item::Recipe(crafted, group,
                             game::item::Recipe::CraftingShaped{
                                     .width       = width,
                                     .height      = height,
                                     .ingredients = std::move(ingredients),
                             });
}

game::item::Recipe Reader::read_recipe_shapeless()
{
   auto group = read_string();
   auto num   = read_varint();

   std::vector<game::item::StackVariants> ingredients(num);
   for (int i = 0; i < num; i++) {
      ingredients[i] = read_stack_variants();
   }
   auto outcome = read_stack();

   return game::item::Recipe(outcome, group,
                             game::item::Recipe::CraftingShapeless{
                                     .ingredients = std::move(ingredients),
                             });
}

game::item::Recipe Reader::read_recipe_heat_treatment(game::item::RecipeType type)
{
   auto group        = read_string();
   auto ingredient   = read_stack_variants();
   auto outcome      = read_stack();
   auto experience   = read_float();
   auto cooking_time = read_varint();
   return game::item::Recipe(outcome, group, type,
                             game::item::Recipe::HeatTreatment{
                                     .ingredient   = std::move(ingredient),
                                     .experience   = experience,
                                     .cooking_time = cooking_time,
                             });
}

game::item::Recipe Reader::read_recipe_stone_cutting()
{
   auto group      = read_string();
   auto ingredient = read_stack_variants();
   auto outcome    = read_stack();
   return game::item::Recipe(outcome, group,
                             game::item::Recipe::StoneCutting{
                                     .ingredient = std::move(ingredient),
                             });
}

game::item::StackVariants Reader::read_stack_variants()
{
   auto num_variants = read_varint();
   game::item::StackVariants result(num_variants);
   for (int v = 0; v < num_variants; v++) {
      result[v] = read_stack();
   }
   return result;
}

game::item::ItemStack Reader::read_stack()
{
   auto not_empty = read_byte();
   if (!not_empty) {
      return game::item::ItemStack{
              .id     = 0,
              .amount = 0,
      };
   }
   auto id              = read_varint();
   auto amount          = read_byte();
   auto additional_data = read_nbt_tag();
   return game::item::ItemStack{
           .id     = id,
           .amount = amount,
   };
}

std::string Reader::get_hex_data()
{
   std::string result;
   unsigned char c;
   while (m_stream.read((char *) &c, 1)) {
      auto most  = c / 16;
      auto least = c % 16;

      if (most > 9) {
         result.push_back(most - 10 + 'a');
      } else {
         result.push_back(most + '0');
      }

      if (least > 9) {
         result.push_back(least - 10 + 'a');
      } else {
         result.push_back(least + '0');
      }
   }

   return result;
}

uint64_t Reader::read_long()
{
   uint64_t value;
   m_stream.read((char *) &value, sizeof(uint64_t));
   value = boost::endian::big_to_native(value);
   return value;
}

short Reader::read_short()
{
   short value;
   m_stream.read((char *) &value, sizeof(short));
   value = boost::endian::big_to_native(value);
   return value;
}

void Reader::read_bytes(std::uint8_t *data, std::size_t size) {
   m_stream.read(reinterpret_cast<char *>(data), static_cast<long>(size));
}

container::Buffer Reader::read_buffer()
{
   auto buffer_size = read_varint();
   container::Buffer buffer(static_cast<std::size_t>(buffer_size));
   read_bytes(buffer.data(), buffer.size());
   return buffer;
}

}// namespace minecpp::network::message
