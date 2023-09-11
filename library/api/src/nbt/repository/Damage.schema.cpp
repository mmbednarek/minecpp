#include "nbt/repository/Damage.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::repository {

void DamageTypeDescription::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Float, "exhaustion");
   w.write_float_content(exhaustion);
   w.write_header(minecpp::nbt::TagId::String, "message_id");
   w.write_string_content(message_id);
   w.write_header(minecpp::nbt::TagId::String, "scaling");
   w.write_string_content(scaling);
   w.end_compound();
}

void DamageTypeDescription::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DamageTypeDescription DamageTypeDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   DamageTypeDescription result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "exhaustion") {
         ::minecpp::nbt::verify_tag("DamageTypeDescription", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.exhaustion = r.read_float32();
         continue;
      }
      if (in_field_name == "message_id") {
         ::minecpp::nbt::verify_tag("DamageTypeDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.message_id = r.read_str();
         continue;
      }
      if (in_field_name == "scaling") {
         ::minecpp::nbt::verify_tag("DamageTypeDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.scaling = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DamageTypeDescription DamageTypeDescription::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DamageTypeDescription::deserialize_no_header(r);
}

void DamageTypeEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "element");
   element.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Int, "id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::String, "name");
   w.write_string_content(name);
   w.end_compound();
}

void DamageTypeEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DamageTypeEntry DamageTypeEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   DamageTypeEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "element") {
         ::minecpp::nbt::verify_tag("DamageTypeEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.element = DamageTypeDescription::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("DamageTypeEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "name") {
         ::minecpp::nbt::verify_tag("DamageTypeEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DamageTypeEntry DamageTypeEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DamageTypeEntry::deserialize_no_header(r);
}

void DamageTypes::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::List, "value");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
   for (const auto &list_item_0 : value) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void DamageTypes::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DamageTypes DamageTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   DamageTypes result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("DamageTypes", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("DamageTypes", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<DamageTypeEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return DamageTypeEntry::deserialize_no_header(r);
         });
         result.value = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DamageTypes DamageTypes::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DamageTypes::deserialize_no_header(r);
}

}