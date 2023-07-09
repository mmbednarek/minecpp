#include "Example1.schema.h"
#include <algorithm>

namespace minecpp::example1 {

void Item::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->name);
   writer.write_short(this->count);
   this->props.serialize(writer);
}

Item Item::deserialize(::minecpp::network::message::Reader &reader) {
   Item result;
   result.name = reader.read_string();
   result.count = reader.read_short();
   result.props = example2::Properties::deserialize(reader);
   return result;
}

void Person::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x01);
   writer.write_string(this->name);
   writer.write_string(this->surname);
   writer.write_big_endian(this->age);
   writer.write_varint(static_cast<std::uint32_t>(this->inventory.size()));
   for (const auto &value_0 : this->inventory) {
      writer.write_varint(static_cast<std::uint32_t>(value_0.size()));
      for (const auto &value_1 : value_0) {
         value_1.serialize(writer);
      }
   }
   writer.write_big_endian(this->dimension_types);
}

Person Person::deserialize(::minecpp::network::message::Reader &reader) {
   Person result;
   result.name = reader.read_string();
   result.surname = reader.read_string();
   result.age = reader.read_big_endian<int>();
   auto size = reader.read_varint();
   result.inventory.resize(static_cast<std::size_t>(size));
   std::generate(result.inventory.begin(), result.inventory.end(), [&reader]() {
      std::vector<Item> result;
      auto size = reader.read_varint();
      result.resize(static_cast<std::size_t>(size));
      std::generate(result.begin(), result.end(), [&reader]() {
         Item result;
         result = Item::deserialize(reader);
         return result;
      });
      return result;
   });
   result.dimension_types = reader.read_big_endian<int>();
   return result;
}

void Car::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(0x02);
   writer.write_string(this->brand);
   writer.write_string(this->vin);
   writer.write_long(this->mileage);
}

Car Car::deserialize(::minecpp::network::message::Reader &reader) {
   Car result;
   result.brand = reader.read_string();
   result.vin = reader.read_string();
   result.mileage = reader.read_long();
   return result;
}

}