#include <minecpp/nbt/repository/v1/Repository.nbt.h>

namespace minecpp::nbt::repository::v1 {

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
   serialize_no_header(w);
}

BlockEntry BlockEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "Block") {
            res.set_property(in_field_name, block::v1::Block::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

ItemEntry ItemEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   ItemEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "Item") {
            res.set_property(in_field_name, item::v1::Item::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

EnumPropertyEntry EnumPropertyEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   EnumPropertyEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "Property") {
            res.set_property(in_field_name, block::v1::EnumProperty::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

IntPropertyEntry IntPropertyEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   IntPropertyEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "Property") {
            res.set_property(in_field_name, block::v1::IntProperty::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

BoolPropertyEntry BoolPropertyEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BoolPropertyEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "Property") {
            res.set_property(in_field_name, block::v1::BoolProperty::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

BlockStateEntry BlockStateEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockStateEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "State") {
            res.set_property(in_field_name, block::v1::BlockState::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   std::for_each(block_states.begin(), block_states.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::List, "Blocks");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, blocks.size());
   std::for_each(blocks.begin(), blocks.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::List, "Items");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, items.size());
   std::for_each(items.begin(), items.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::List, "EnumProperties");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, enum_properties.size());
   std::for_each(enum_properties.begin(), enum_properties.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::List, "IntProperties");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, int_properties.size());
   std::for_each(int_properties.begin(), int_properties.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::List, "BoolProperties");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, bool_properties.size());
   std::for_each(bool_properties.begin(), bool_properties.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.end_compound();
}

void Repository::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   serialize_no_header(w);
}

Repository Repository::deserialize_no_header(minecpp::nbt::Reader &r) {
   Repository res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               if (in_field_name == "BlockStates") {
                  std::vector<BlockStateEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return BlockStateEntry::deserialize_no_header(r);
                  });
                  res.set_property(in_field_name, ls);
                  return;
               }
               if (in_field_name == "Blocks") {
                  std::vector<BlockEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return BlockEntry::deserialize_no_header(r);
                  });
                  res.set_property(in_field_name, ls);
                  return;
               }
               if (in_field_name == "Items") {
                  std::vector<ItemEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return ItemEntry::deserialize_no_header(r);
                  });
                  res.set_property(in_field_name, ls);
                  return;
               }
               if (in_field_name == "EnumProperties") {
                  std::vector<EnumPropertyEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return EnumPropertyEntry::deserialize_no_header(r);
                  });
                  res.set_property(in_field_name, ls);
                  return;
               }
               if (in_field_name == "IntProperties") {
                  std::vector<IntPropertyEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return IntPropertyEntry::deserialize_no_header(r);
                  });
                  res.set_property(in_field_name, ls);
                  return;
               }
               if (in_field_name == "BoolProperties") {
                  std::vector<BoolPropertyEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return BoolPropertyEntry::deserialize_no_header(r);
                  });
                  res.set_property(in_field_name, ls);
                  return;
               }
               break;
            }
            default: 
               break;
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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