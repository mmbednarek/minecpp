#include "nbt/repository/Chat.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::repository {

void ChatDecorationStyle::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "color");
   w.write_string_content(color);
   w.write_header(minecpp::nbt::TagId::Byte, "italic");
   w.write_byte_content(static_cast<std::uint8_t>(italic));
   w.write_header(minecpp::nbt::TagId::Byte, "bold");
   w.write_byte_content(static_cast<std::uint8_t>(bold));
   w.end_compound();
}

void ChatDecorationStyle::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatDecorationStyle ChatDecorationStyle::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatDecorationStyle result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "color") {
         ::minecpp::nbt::verify_tag("ChatDecorationStyle", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.color = r.read_str();
         continue;
      }
      if (in_field_name == "italic") {
         ::minecpp::nbt::verify_tag("ChatDecorationStyle", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.italic = r.read_byte();
         continue;
      }
      if (in_field_name == "bold") {
         ::minecpp::nbt::verify_tag("ChatDecorationStyle", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.bold = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatDecorationStyle ChatDecorationStyle::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatDecorationStyle::deserialize_no_header(r);
}

void ChatDetails::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "parameters");
   w.begin_list_no_header(minecpp::nbt::TagId::String, parameters.size());
   for (const auto &list_item_0 : parameters) {
      w.write_string_content(list_item_0);
   }
   if (style.has_value()) {
      w.write_header(minecpp::nbt::TagId::Compound, "style");
      style->serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::String, "translation_key");
   w.write_string_content(translation_key);
   w.end_compound();
}

void ChatDetails::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatDetails ChatDetails::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatDetails result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "parameters") {
         ::minecpp::nbt::verify_tag("ChatDetails", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::string> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_str();
         });
         result.parameters = std::move(list);
         continue;
      }
      if (in_field_name == "style") {
         ::minecpp::nbt::verify_tag("ChatDetails", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.style = ChatDecorationStyle::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "translation_key") {
         ::minecpp::nbt::verify_tag("ChatDetails", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.translation_key = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatDetails ChatDetails::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatDetails::deserialize_no_header(r);
}

void ChatTypeDescription::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "chat");
   chat.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "narration");
   narration.serialize_no_header(w);
   w.end_compound();
}

void ChatTypeDescription::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatTypeDescription ChatTypeDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypeDescription result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chat") {
         ::minecpp::nbt::verify_tag("ChatTypeDescription", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.chat = ChatDetails::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "narration") {
         ::minecpp::nbt::verify_tag("ChatTypeDescription", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.narration = ChatDetails::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatTypeDescription ChatTypeDescription::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatTypeDescription::deserialize_no_header(r);
}

void ChatTypeEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Int, "id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::Compound, "element");
   element.serialize_no_header(w);
   w.end_compound();
}

void ChatTypeEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatTypeEntry ChatTypeEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypeEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "name") {
         ::minecpp::nbt::verify_tag("ChatTypeEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("ChatTypeEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "element") {
         ::minecpp::nbt::verify_tag("ChatTypeEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.element = ChatTypeDescription::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatTypeEntry ChatTypeEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatTypeEntry::deserialize_no_header(r);
}

void ChatTypes::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::List, "value");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
   for (const auto &list_item_0 : value) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void ChatTypes::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatTypes ChatTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypes result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("ChatTypes", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("ChatTypes", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<ChatTypeEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return ChatTypeEntry::deserialize_no_header(r);
         });
         result.value = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatTypes ChatTypes::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatTypes::deserialize_no_header(r);
}

}