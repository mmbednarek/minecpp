#include "Example1.schema.h"

#include "minecpp/network/message/Writer.h"

#include <sstream>

using minecpp::example1::Item;
using minecpp::example1::Person;
using minecpp::example1::Car;

class Visitor {
 public:
   void on_person(const Person &person) {
      std::cout << "visited person\n";
      std::cout << "\n\n.name: " << person.name << '\n';
      std::cout << ".surname: " << person.surname << '\n';
      std::cout << ".age: " << person.age << '\n';
      int x{};
      for (const auto &value : person.inventory) {
         int y{};
         for (const auto &value_value : value) {
            std::cout << ".inventory[" << x << "][" << y << "].name: " << value_value.name << '\n';
            std::cout << ".inventory[" << x << "][" << y << "].count: " << value_value.count << '\n';
            ++y;
         }
         ++x;
      }
   }

   void on_car(const Car &car) {
      std::cout << "visited car " << car.brand << "\n";
   }

   void on_failure(std::uint8_t message_id) const {
      std::cerr << "failed to read message with id " << message_id << '\n';
   }
};

int main() {
   Person person;
   person.name = "hello";
   person.surname = "world";
   person.age = 20;

   Item item1;
   item1.name = "hello";
   item1.count = 16;
   item1.props.meta["hey"] = "lala";
   Item item2;
   item2.name = "world";
   item2.count = 32;
   item2.props.meta["hello"] = "aaaa";
   item2.props.meta["hiiii"] = "bbbb";
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

   minecpp::network::message::Writer writer;
   person.serialize(writer);

   auto result = writer.buff(0);
   auto result_stream = result.make_stream();
   minecpp::network::message::Reader reader(result_stream);

   std::cout << "message size: " << reader.read_varint() << '\n';

   Visitor visitor;
   minecpp::example1::visit_message(visitor, reader);
}