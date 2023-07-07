#include "Example1.schema.h"

#include "minecpp/nbt/Parser.h"

#include <sstream>

using minecpp::example1::Item;
using minecpp::example1::Person;

int main() {
   Person person;
   person.name = "hello";
   person.surname = "world";
   person.age = 20;

   Item item1;
   item1.name = "hello";
   item1.count = 16;
   Item item2;
   item2.name = "world";
   item2.count = 32;
   std::vector<Item> items1{std::move(item1), std::move(item2)};
   person.inventory.emplace_back(std::move(items1));

   Item item3;
   item3.name = "foo";
   item3.count = 48;
   Item item4;
   item4.name = "bar";
   item4.count = 72;
   std::vector<Item> items2{std::move(item3), std::move(item4)};
   person.inventory.emplace_back(std::move(items2));

   std::stringstream ss;
   person.serialize(ss, "");
   ss.seekg(0, std::ios::beg);

   minecpp::nbt::Parser parser(ss);
   for (;;) {
      auto tag = parser.read_tag();
      if (tag.content.empty())
         break;
      std::cout << tag.content.to_string();
   }

   ss.clear();
   person.serialize(ss, "");
   ss.seekg(0, std::ios::beg);

   auto deserialized_person = Person::deserialize(ss);

   std::cout << "\n\n.name: " << deserialized_person.name << '\n';
   std::cout << ".surname: " << deserialized_person.surname << '\n';
   std::cout << ".age: " << deserialized_person.age << '\n';
   int x{};
   for (const auto &value : deserialized_person.inventory) {
      int y{};
      for (const auto &value_value : value) {
         std::cout << ".inventory[" << x << "][" << y << "].name: " << value_value.name << '\n';
         std::cout << ".inventory[" << x << "][" << y << "].count: " << value_value.count << '\n';
         ++y;
      }
      ++x;
   }
}