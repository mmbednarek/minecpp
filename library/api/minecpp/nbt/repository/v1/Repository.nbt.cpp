#include <minecpp/nbt/repository/v1/Repository.nbt.h>

namespace minecpp::nbt::repository::v1 {

void BlockEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "Block");
   block.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void BlockEntry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BlockEntry BlockEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "Block") {
            res.__xx_put(name, block::v1::Block::deserialize_no_header(r));
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
   w.write_header(minecpp::nbt::TagId::Compound, "Item");
   item.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void ItemEntry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ItemEntry ItemEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   ItemEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "Item") {
            res.__xx_put(name, item::v1::Item::deserialize_no_header(r));
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

void EnumStateEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "State");
   state.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void EnumStateEntry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

EnumStateEntry EnumStateEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   EnumStateEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "State") {
            res.__xx_put(name, block::v1::EnumState::deserialize_no_header(r));
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

EnumStateEntry EnumStateEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return EnumStateEntry::deserialize_no_header(r);
}

void IntStateEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "State");
   state.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void IntStateEntry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

IntStateEntry IntStateEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   IntStateEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "State") {
            res.__xx_put(name, block::v1::IntState::deserialize_no_header(r));
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

IntStateEntry IntStateEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return IntStateEntry::deserialize_no_header(r);
}

void BoolStateEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "State");
   state.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.end_compound();
}

void BoolStateEntry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BoolStateEntry BoolStateEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BoolStateEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "State") {
            res.__xx_put(name, block::v1::BoolState::deserialize_no_header(r));
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

BoolStateEntry BoolStateEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BoolStateEntry::deserialize_no_header(r);
}

void Repository::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "EnumStates");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, enum_states.size());
   std::for_each(enum_states.begin(), enum_states.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::List, "IntStates");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, int_states.size());
   std::for_each(int_states.begin(), int_states.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::List, "BoolStates");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, bool_states.size());
   std::for_each(bool_states.begin(), bool_states.end(), [&w](const auto &value) {
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
   w.end_compound();
}

void Repository::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Repository Repository::deserialize_no_header(minecpp::nbt::Reader &r) {
   Repository res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               if (name == "EnumStates") {
                  std::vector<EnumStateEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return EnumStateEntry::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               if (name == "IntStates") {
                  std::vector<IntStateEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return IntStateEntry::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               if (name == "BoolStates") {
                  std::vector<BoolStateEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return BoolStateEntry::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               if (name == "Blocks") {
                  std::vector<BlockEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return BlockEntry::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               if (name == "Items") {
                  std::vector<ItemEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return ItemEntry::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
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