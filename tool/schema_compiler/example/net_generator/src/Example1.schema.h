#pragma once
#include "./Example2.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <string>

namespace minecpp::example1 {

class Item {
 public:
   std::string name{};
   std::int16_t count{};
   example2::Properties props{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Item deserialize(::minecpp::network::message::Reader &reader);
};

class Person {
 public:
   std::string name{};
   std::string surname{};
   std::int32_t age{};
   std::vector<std::vector<Item>> inventory{};
   std::int32_t dimension_types{};
   std::variant<std::int32_t, std::string, std::int8_t> foo_type{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Person deserialize(::minecpp::network::message::Reader &reader);
};

class Car {
 public:
   std::string brand{};
   std::string vin{};
   std::int64_t mileage{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Car deserialize(::minecpp::network::message::Reader &reader);
};

template<typename TVisitor>
void visit_message(TVisitor &visitor, ::minecpp::network::message::Reader &reader) {
   auto message_id = reader.read_byte();
   switch (message_id) {
   case 0x01: {
      auto message = Person::deserialize(reader);
      visitor.on_person(message);
      break;
   }
   case 0x02: {
      auto message = Car::deserialize(reader);
      visitor.on_car(message);
      break;
   }
   default: 
      visitor.on_failure(message_id);
      break;
   }
}

}
