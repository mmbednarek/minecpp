#include "repository/Repository.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::repository {

void BlockEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "Id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::Compound, "Block");
   block.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void BlockEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BlockEntry BlockEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Id") {
         ::minecpp::nbt::verify_tag("BlockEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "Block") {
         ::minecpp::nbt::verify_tag("BlockEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.block = block::Block::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "Tag") {
         ::minecpp::nbt::verify_tag("BlockEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.tag = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BlockEntry BlockEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BlockEntry::deserialize_no_header(r);
}

void ItemEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "Id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::Compound, "Item");
   item.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void ItemEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ItemEntry ItemEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   ItemEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Id") {
         ::minecpp::nbt::verify_tag("ItemEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "Item") {
         ::minecpp::nbt::verify_tag("ItemEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.item = item::Item::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "Tag") {
         ::minecpp::nbt::verify_tag("ItemEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.tag = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ItemEntry ItemEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ItemEntry::deserialize_no_header(r);
}

void EnumPropertyEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "Property");
   property.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void EnumPropertyEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

EnumPropertyEntry EnumPropertyEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   EnumPropertyEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Property") {
         ::minecpp::nbt::verify_tag("EnumPropertyEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.property = block::EnumProperty::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "Tag") {
         ::minecpp::nbt::verify_tag("EnumPropertyEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.tag = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

EnumPropertyEntry EnumPropertyEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return EnumPropertyEntry::deserialize_no_header(r);
}

void IntPropertyEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "Property");
   property.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void IntPropertyEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

IntPropertyEntry IntPropertyEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   IntPropertyEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Property") {
         ::minecpp::nbt::verify_tag("IntPropertyEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.property = block::IntProperty::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "Tag") {
         ::minecpp::nbt::verify_tag("IntPropertyEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.tag = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

IntPropertyEntry IntPropertyEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return IntPropertyEntry::deserialize_no_header(r);
}

void BoolPropertyEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "Property");
   property.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void BoolPropertyEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BoolPropertyEntry BoolPropertyEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BoolPropertyEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Property") {
         ::minecpp::nbt::verify_tag("BoolPropertyEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.property = block::BoolProperty::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "Tag") {
         ::minecpp::nbt::verify_tag("BoolPropertyEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.tag = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BoolPropertyEntry BoolPropertyEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BoolPropertyEntry::deserialize_no_header(r);
}

void BlockStateEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "Id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::Compound, "State");
   state.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void BlockStateEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BlockStateEntry BlockStateEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockStateEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Id") {
         ::minecpp::nbt::verify_tag("BlockStateEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "State") {
         ::minecpp::nbt::verify_tag("BlockStateEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.state = block::BlockState::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "Tag") {
         ::minecpp::nbt::verify_tag("BlockStateEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.tag = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BlockStateEntry BlockStateEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BlockStateEntry::deserialize_no_header(r);
}

void Repository::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "BlockStates");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, block_states.size());
   for (const auto &list_item_0 : block_states) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::List, "Blocks");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, blocks.size());
   for (const auto &list_item_0 : blocks) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::List, "Items");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, items.size());
   for (const auto &list_item_0 : items) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::List, "EnumProperties");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, enum_properties.size());
   for (const auto &list_item_0 : enum_properties) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::List, "IntProperties");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, int_properties.size());
   for (const auto &list_item_0 : int_properties) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::List, "BoolProperties");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, bool_properties.size());
   for (const auto &list_item_0 : bool_properties) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void Repository::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Repository Repository::deserialize_no_header(minecpp::nbt::Reader &r) {
   Repository result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "BlockStates") {
         ::minecpp::nbt::verify_tag("Repository", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<BlockStateEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return BlockStateEntry::deserialize_no_header(r);
         });
         result.block_states = std::move(list);
         continue;
      }
      if (in_field_name == "Blocks") {
         ::minecpp::nbt::verify_tag("Repository", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<BlockEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return BlockEntry::deserialize_no_header(r);
         });
         result.blocks = std::move(list);
         continue;
      }
      if (in_field_name == "Items") {
         ::minecpp::nbt::verify_tag("Repository", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<ItemEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return ItemEntry::deserialize_no_header(r);
         });
         result.items = std::move(list);
         continue;
      }
      if (in_field_name == "EnumProperties") {
         ::minecpp::nbt::verify_tag("Repository", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<EnumPropertyEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return EnumPropertyEntry::deserialize_no_header(r);
         });
         result.enum_properties = std::move(list);
         continue;
      }
      if (in_field_name == "IntProperties") {
         ::minecpp::nbt::verify_tag("Repository", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<IntPropertyEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return IntPropertyEntry::deserialize_no_header(r);
         });
         result.int_properties = std::move(list);
         continue;
      }
      if (in_field_name == "BoolProperties") {
         ::minecpp::nbt::verify_tag("Repository", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<BoolPropertyEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return BoolPropertyEntry::deserialize_no_header(r);
         });
         result.bool_properties = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Repository Repository::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Repository::deserialize_no_header(r);
}

}