#include "nbt/block/Block.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::block {

void EnumProperty::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::List, "Label");
   w.begin_list_no_header(minecpp::nbt::TagId::String, values.size());
   for (const auto &list_item_0 : values) {
      w.write_string_content(list_item_0);
   }
   w.end_compound();
}

void EnumProperty::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

EnumProperty EnumProperty::deserialize_no_header(minecpp::nbt::Reader &r) {
   EnumProperty result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("EnumProperty", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "Label") {
         ::minecpp::nbt::verify_tag("EnumProperty", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::string> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_str();
         });
         result.values = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

EnumProperty EnumProperty::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return EnumProperty::deserialize_no_header(r);
}

void IntProperty::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Int, "MinValue");
   w.write_int_content(min_value);
   w.write_header(minecpp::nbt::TagId::Int, "MaxValue");
   w.write_int_content(max_value);
   w.end_compound();
}

void IntProperty::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

IntProperty IntProperty::deserialize_no_header(minecpp::nbt::Reader &r) {
   IntProperty result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("IntProperty", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "MinValue") {
         ::minecpp::nbt::verify_tag("IntProperty", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.min_value = r.read_int();
         continue;
      }
      if (in_field_name == "MaxValue") {
         ::minecpp::nbt::verify_tag("IntProperty", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.max_value = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

IntProperty IntProperty::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return IntProperty::deserialize_no_header(r);
}

void BoolProperty::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.end_compound();
}

void BoolProperty::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BoolProperty BoolProperty::deserialize_no_header(minecpp::nbt::Reader &r) {
   BoolProperty result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("BoolProperty", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BoolProperty BoolProperty::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BoolProperty::deserialize_no_header(r);
}

void Block::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "PropertyTags");
   w.begin_list_no_header(minecpp::nbt::TagId::String, property_tags.size());
   for (const auto &list_item_0 : property_tags) {
      w.write_string_content(list_item_0);
   }
   w.end_compound();
}

void Block::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Block Block::deserialize_no_header(minecpp::nbt::Reader &r) {
   Block result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "PropertyTags") {
         ::minecpp::nbt::verify_tag("Block", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::string> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_str();
         });
         result.property_tags = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Block Block::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Block::deserialize_no_header(r);
}

void BlockEntityData::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.end_compound();
}

void BlockEntityData::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BlockEntityData BlockEntityData::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockEntityData result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      r.skip_payload(tagid);
   }
   return result;
}

BlockEntityData BlockEntityData::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BlockEntityData::deserialize_no_header(r);
}

}