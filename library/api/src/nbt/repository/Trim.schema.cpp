#include "nbt/repository/Trim.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::repository {

void TrimMaterialDescription::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "color");
   w.write_string_content(color);
   w.write_header(minecpp::nbt::TagId::String, "translate");
   w.write_string_content(translate);
   w.end_compound();
}

void TrimMaterialDescription::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

TrimMaterialDescription TrimMaterialDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   TrimMaterialDescription result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "color") {
         ::minecpp::nbt::verify_tag("TrimMaterialDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.color = r.read_str();
         continue;
      }
      if (in_field_name == "translate") {
         ::minecpp::nbt::verify_tag("TrimMaterialDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.translate = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

TrimMaterialDescription TrimMaterialDescription::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return TrimMaterialDescription::deserialize_no_header(r);
}

void TrimMaterialInfo::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "asset_name");
   w.write_string_content(asset_name);
   w.write_header(minecpp::nbt::TagId::Compound, "description");
   description.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "ingredient");
   w.write_string_content(ingredient);
   w.write_header(minecpp::nbt::TagId::Float, "item_model_index");
   w.write_float_content(item_model_index);
   w.write_header(minecpp::nbt::TagId::Compound, "override_armor_materials");
   minecpp::nbt::serialize_compound_content(w, override_armor_materials);
   w.end_compound();
}

void TrimMaterialInfo::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

TrimMaterialInfo TrimMaterialInfo::deserialize_no_header(minecpp::nbt::Reader &r) {
   TrimMaterialInfo result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "asset_name") {
         ::minecpp::nbt::verify_tag("TrimMaterialInfo", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.asset_name = r.read_str();
         continue;
      }
      if (in_field_name == "description") {
         ::minecpp::nbt::verify_tag("TrimMaterialInfo", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.description = TrimMaterialDescription::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "ingredient") {
         ::minecpp::nbt::verify_tag("TrimMaterialInfo", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.ingredient = r.read_str();
         continue;
      }
      if (in_field_name == "item_model_index") {
         ::minecpp::nbt::verify_tag("TrimMaterialInfo", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.item_model_index = r.read_float32();
         continue;
      }
      if (in_field_name == "override_armor_materials") {
         ::minecpp::nbt::verify_tag("TrimMaterialInfo", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.override_armor_materials = r.read_compound_content();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

TrimMaterialInfo TrimMaterialInfo::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return TrimMaterialInfo::deserialize_no_header(r);
}

void TrimMaterialEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "element");
   element.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Int, "id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::String, "name");
   w.write_string_content(name);
   w.end_compound();
}

void TrimMaterialEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

TrimMaterialEntry TrimMaterialEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   TrimMaterialEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "element") {
         ::minecpp::nbt::verify_tag("TrimMaterialEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.element = TrimMaterialInfo::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("TrimMaterialEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "name") {
         ::minecpp::nbt::verify_tag("TrimMaterialEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

TrimMaterialEntry TrimMaterialEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return TrimMaterialEntry::deserialize_no_header(r);
}

void TrimMaterialTypes::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::List, "value");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
   for (const auto &list_item_0 : value) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void TrimMaterialTypes::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

TrimMaterialTypes TrimMaterialTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   TrimMaterialTypes result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("TrimMaterialTypes", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("TrimMaterialTypes", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<TrimMaterialEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return TrimMaterialEntry::deserialize_no_header(r);
         });
         result.value = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

TrimMaterialTypes TrimMaterialTypes::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return TrimMaterialTypes::deserialize_no_header(r);
}

void TrimPatternDescription::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "translate");
   w.write_string_content(translate);
   w.end_compound();
}

void TrimPatternDescription::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

TrimPatternDescription TrimPatternDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   TrimPatternDescription result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "translate") {
         ::minecpp::nbt::verify_tag("TrimPatternDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.translate = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

TrimPatternDescription TrimPatternDescription::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return TrimPatternDescription::deserialize_no_header(r);
}

void TrimPatternInfo::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "asset_id");
   w.write_string_content(asset_id);
   w.write_header(minecpp::nbt::TagId::Compound, "description");
   description.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "template_item");
   w.write_string_content(template_item);
   w.end_compound();
}

void TrimPatternInfo::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

TrimPatternInfo TrimPatternInfo::deserialize_no_header(minecpp::nbt::Reader &r) {
   TrimPatternInfo result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "asset_id") {
         ::minecpp::nbt::verify_tag("TrimPatternInfo", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.asset_id = r.read_str();
         continue;
      }
      if (in_field_name == "description") {
         ::minecpp::nbt::verify_tag("TrimPatternInfo", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.description = TrimPatternDescription::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "template_item") {
         ::minecpp::nbt::verify_tag("TrimPatternInfo", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.template_item = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

TrimPatternInfo TrimPatternInfo::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return TrimPatternInfo::deserialize_no_header(r);
}

void TrimPatternEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "element");
   element.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Int, "id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::String, "name");
   w.write_string_content(name);
   w.end_compound();
}

void TrimPatternEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

TrimPatternEntry TrimPatternEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   TrimPatternEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "element") {
         ::minecpp::nbt::verify_tag("TrimPatternEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.element = TrimPatternInfo::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("TrimPatternEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "name") {
         ::minecpp::nbt::verify_tag("TrimPatternEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

TrimPatternEntry TrimPatternEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return TrimPatternEntry::deserialize_no_header(r);
}

void TrimPatternTypes::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::List, "value");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
   for (const auto &list_item_0 : value) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void TrimPatternTypes::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

TrimPatternTypes TrimPatternTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   TrimPatternTypes result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("TrimPatternTypes", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("TrimPatternTypes", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<TrimPatternEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return TrimPatternEntry::deserialize_no_header(r);
         });
         result.value = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

TrimPatternTypes TrimPatternTypes::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return TrimPatternTypes::deserialize_no_header(r);
}

}