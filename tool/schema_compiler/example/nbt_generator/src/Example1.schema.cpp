#include "Example1.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::example1 {

void Item::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Short, "Count");
   w.write_short_content(count);
   w.write_header(minecpp::nbt::TagId::Compound, "Props");
   props.serialize_no_header(w);
   w.end_compound();
}

void Item::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Item Item::deserialize_no_header(minecpp::nbt::Reader &r) {
   Item result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "Count") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.count = r.read_short();
         continue;
      }
      if (in_field_name == "Props") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.props = example2::Properties::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Item Item::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Item::deserialize_no_header(r);
}

void Person::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::String, "Surname");
   w.write_string_content(surname);
   w.write_header(minecpp::nbt::TagId::Int, "Age");
   w.write_int_content(age);
   w.write_header(minecpp::nbt::TagId::List, "Inventory");
   w.begin_list_no_header(minecpp::nbt::TagId::List, inventory.size());
   for (const auto &list_item_0 : inventory) {
      w.begin_list_no_header(minecpp::nbt::TagId::Compound, list_item_0.size());
      for (const auto &list_item_1 : list_item_0) {
         list_item_1.serialize_no_header(w);
      }
   }
   w.write_header(minecpp::nbt::TagId::Int, "dimension_types:dimension_type/stuff");
   w.write_int_content(dimension_types);
   if (std::holds_alternative<std::int32_t>(foo_type)) {
      w.write_header(minecpp::nbt::TagId::Int, "FooType");
      w.write_int_content(std::get<std::int32_t>(foo_type));
   } else if (std::holds_alternative<std::string>(foo_type)) {
      w.write_header(minecpp::nbt::TagId::String, "FooType");
      w.write_string_content(std::get<std::string>(foo_type));
   } else if (std::holds_alternative<std::int8_t>(foo_type)) {
      w.write_header(minecpp::nbt::TagId::Byte, "FooType");
      w.write_byte_content(static_cast<std::uint8_t>(std::get<std::int8_t>(foo_type)));
   }
   w.end_compound();
}

void Person::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Person Person::deserialize_no_header(minecpp::nbt::Reader &r) {
   Person result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("Person", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "Surname") {
         ::minecpp::nbt::verify_tag("Person", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.surname = r.read_str();
         continue;
      }
      if (in_field_name == "Age") {
         ::minecpp::nbt::verify_tag("Person", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.age = r.read_int();
         continue;
      }
      if (in_field_name == "Inventory") {
         ::minecpp::nbt::verify_tag("Person", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::vector<Item>> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            auto list_info = r.peek_list();
            std::vector<Item> list(list_info.size);
            std::generate(list.begin(), list.end(), [&r]() {
               return Item::deserialize_no_header(r);
            });
            return list;
         });
         result.inventory = std::move(list);
         continue;
      }
      if (in_field_name == "dimension_types:dimension_type/stuff") {
         ::minecpp::nbt::verify_tag("Person", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.dimension_types = r.read_int();
         continue;
      }
      if (in_field_name == "FooType") {
         std::variant<std::int32_t, std::string, std::int8_t> result_variant;
         if (tagid == minecpp::nbt::TagId::Int) {
            result_variant = r.read_int();
         } else if (tagid == minecpp::nbt::TagId::String) {
            result_variant = r.read_str();
         } else if (tagid == minecpp::nbt::TagId::Byte) {
            result_variant = r.read_byte();
         }
         result.foo_type = std::move(result_variant);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Person Person::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Person::deserialize_no_header(r);
}

}