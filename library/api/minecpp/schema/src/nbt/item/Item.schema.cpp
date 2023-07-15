#include "nbt/item/Item.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::item {

void Item::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "IsBlock");
   w.write_byte_content(static_cast<std::uint8_t>(is_block));
   w.write_header(minecpp::nbt::TagId::String, "CorrespondingBlockTag");
   w.write_string_content(corresponding_block_tag);
   w.write_header(minecpp::nbt::TagId::Int, "MaxItemStack");
   w.write_int_content(max_item_stack);
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
      if (in_field_name == "IsBlock") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_block = r.read_byte();
         continue;
      }
      if (in_field_name == "CorrespondingBlockTag") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.corresponding_block_tag = r.read_str();
         continue;
      }
      if (in_field_name == "MaxItemStack") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.max_item_stack = r.read_int();
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

void StoredEnchantment::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.write_header(minecpp::nbt::TagId::Short, "lvl");
   w.write_short_content(lvl);
   w.end_compound();
}

void StoredEnchantment::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

StoredEnchantment StoredEnchantment::deserialize_no_header(minecpp::nbt::Reader &r) {
   StoredEnchantment result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("StoredEnchantment", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.id = r.read_str();
         continue;
      }
      if (in_field_name == "lvl") {
         ::minecpp::nbt::verify_tag("StoredEnchantment", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.lvl = r.read_short();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

StoredEnchantment StoredEnchantment::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return StoredEnchantment::deserialize_no_header(r);
}

void SlotData::serialize_no_header(minecpp::nbt::Writer &w) const {
   if (stored_enchantments.has_value()) {
      w.write_header(minecpp::nbt::TagId::List, "StoredEnchantments");
      w.begin_list_no_header(minecpp::nbt::TagId::Compound, stored_enchantments->size());
      for (const auto &list_item_0 : *stored_enchantments) {
         list_item_0.serialize_no_header(w);
      }
   }
   w.end_compound();
}

void SlotData::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

SlotData SlotData::deserialize_no_header(minecpp::nbt::Reader &r) {
   SlotData result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "StoredEnchantments") {
         ::minecpp::nbt::verify_tag("SlotData", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<StoredEnchantment> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return StoredEnchantment::deserialize_no_header(r);
         });
         result.stored_enchantments = list;
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

SlotData SlotData::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return SlotData::deserialize_no_header(r);
}

}