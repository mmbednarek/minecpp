#include <minecpp/nbt/block/v1/block.nbt.h>

namespace minecpp::nbt::block::v1 {

void EnumState::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::List, "Label");
   w.begin_list_no_header(minecpp::nbt::TagId::String, values.size());
   std::for_each(values.begin(), values.end(), [&w](const auto &value) {
      w.write_string_content(value);
   });
   w.end_compound();
}

void EnumState::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

EnumState EnumState::deserialize_no_header(minecpp::nbt::Reader &r) {
   EnumState res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::String: {
               std::vector<std::string> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() {
                  return r.read_str();
               });
               res.__xx_put(name, ls);
               return;
            }
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      }
      r.skip_payload(tagid);
   });
   return res;
}

EnumState EnumState::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return EnumState();
   }
   return EnumState::deserialize_no_header(r);
}

void IntState::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Int, "MinValue");
   w.write_int_content(min_value);
   w.write_header(minecpp::nbt::TagId::Int, "MaxValue");
   w.write_int_content(max_value);
   w.end_compound();
}

void IntState::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

IntState IntState::deserialize_no_header(minecpp::nbt::Reader &r) {
   IntState res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

IntState IntState::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return IntState();
   }
   return IntState::deserialize_no_header(r);
}

void BoolState::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.end_compound();
}

void BoolState::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BoolState BoolState::deserialize_no_header(minecpp::nbt::Reader &r) {
   BoolState res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

BoolState BoolState::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return BoolState();
   }
   return BoolState::deserialize_no_header(r);
}

void Block::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "StateTags");
   w.begin_list_no_header(minecpp::nbt::TagId::String, state_tags.size());
   std::for_each(state_tags.begin(), state_tags.end(), [&w](const auto &value) {
      w.write_string_content(value);
   });
   w.end_compound();
}

void Block::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Block Block::deserialize_no_header(minecpp::nbt::Reader &r) {
   Block res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::String: {
               std::vector<std::string> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() {
                  return r.read_str();
               });
               res.__xx_put(name, ls);
               return;
            }
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      }
      r.skip_payload(tagid);
   });
   return res;
}

Block Block::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Block();
   }
   return Block::deserialize_no_header(r);
}

}