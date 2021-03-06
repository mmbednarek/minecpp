#include <boost/program_options.hpp>
#include <fstream>
#include <minecpp/game/item/registry.h>
#include <minecpp/network/message/io.h>

namespace options = boost::program_options;

void print_shaped(minecpp::game::item::Recipe recipe) {
   std::cout << "shaped:\n";
   auto details = recipe.details<minecpp::game::item::Recipe::CraftingShaped>();
   assert((details.width * details.height) == (int) details.ingredients.size());
   for (int y = 0; y < details.height; ++y) {
      std::cout << "  ";
      for (int x = 0; x < details.width; ++x) {
         auto in = details.ingredients[y * details.width + x];
         if (in.empty()) {
            std::cout << "empty ";
            continue;
         }
         auto item = minecpp::game::item::item_by_id(in[0].id);
         std::cout << item.tag() << " ";
      }
      std::cout << "\n";
   }
}

auto main(int argc, char *argv[]) -> int {
   options::options_description desc("params");
   desc.add_options()("help", "help message")(
           "input", options::value<std::string>(), "read stuff");

   options::variables_map var_map;
   options::store(options::parse_command_line(argc, argv, desc), var_map);

   if (!var_map.count("input")) {
      std::cerr << "no input file provided";
      return 1;
   }

   auto f = std::ifstream();
   f.open(var_map["input"].as<std::string>());
   if (!f.is_open()) {
      std::cerr << "could not open file";
      return 2;
   }

   minecpp::network::message::Reader reader(f);
   auto b = reader.read_byte();

   if (b != 0x5b) {
      std::cerr << "invalid signature";
      return 3;
   }

   auto num_recipes = reader.read_varint();

   std::cout << "reading " << num_recipes << " recipes\n\n";
   for (int i = 0; i < num_recipes; i++) {
      auto recipe = reader.read_recipe();

      auto out_stack = recipe.outcome();
      auto outcome = minecpp::game::item::item_by_id(out_stack.id);

      std::cout << "--------------------\n";
      std::cout << "outcome item = " << outcome.tag() << "\n";
      std::cout << "amount = " << (int) out_stack.amount << "\n";
      switch (recipe.type()) {
      case minecpp::game::item::CraftingShaped:
         print_shaped(recipe);
         break;
      case minecpp::game::item::CraftingShapeless:
         std::cout << "shapeless\n";
         break;
      case minecpp::game::item::Smelting:
         std::cout << "smelting\n";
         break;
      case minecpp::game::item::Blasting:
         std::cout << "blasting\n";
         break;
      case minecpp::game::item::Smoking:
         std::cout << "smoking\n";
         break;
      case minecpp::game::item::CampfireCooking:
         std::cout << "campfire_cooking\n";
         break;
      case minecpp::game::item::StoneCutting:
         std::cout << "stone cutting\n";
         break;
      case minecpp::game::item::Special:
         std::cout << "special\n";
         break;
      }
   }
}