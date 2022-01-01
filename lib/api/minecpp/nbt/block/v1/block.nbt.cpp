#include <minecpp/nbt/block/v1/block.nbt.h>

namespace minecpp::nbt::block::v1 {

void EnumAllowedValues::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "Label");
   w.begin_list_no_header(minecpp::nbt::TagId::String, values.size());
   std::for_each(values.begin(), values.end(), [&w](const auto &value) {
      w.write_string_content(value);
   });
   w.end_compound();
}

void EnumAllowedValues::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

EnumAllowedValues EnumAllowedValues::deserialize_no_header(minecpp::nbt::Reader &r) {
   EnumAllowedValues res;
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

EnumAllowedValues EnumAllowedValues::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return EnumAllowedValues();
   }
   return EnumAllowedValues::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> EnumAllowedValues::__xx_offsets {
   {"Label", {offsetof(EnumAllowedValues, values), sizeof(EnumAllowedValues::values), 2}},
};

int EnumAllowedValues::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void IntAllowedValues::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "MinValue");
   w.write_int_content(min_value);
   w.write_header(minecpp::nbt::TagId::Int, "MaxValue");
   w.write_int_content(max_value);
   w.end_compound();
}

void IntAllowedValues::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

IntAllowedValues IntAllowedValues::deserialize_no_header(minecpp::nbt::Reader &r) {
   IntAllowedValues res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

IntAllowedValues IntAllowedValues::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return IntAllowedValues();
   }
   return IntAllowedValues::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> IntAllowedValues::__xx_offsets {
   {"MinValue", {offsetof(IntAllowedValues, min_value), sizeof(IntAllowedValues::min_value), 2}},
   {"MaxValue", {offsetof(IntAllowedValues, max_value), sizeof(IntAllowedValues::max_value), 2}},
};

int IntAllowedValues::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void State::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::String, "Tag");
   w.write_string_content(tag);
   w.write_header(minecpp::nbt::TagId::Int, "AllowedValuesVariant");
   w.write_int_content(allowed_values_variant);
   w.write_header(minecpp::nbt::TagId::Compound, "EnumAllowedValues");
   enum_allowed_values.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "IntAllowedValues");
   int_allowed_values.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "position");
   position.serialize_no_header(w);
   w.end_compound();
}

void State::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

State State::deserialize_no_header(minecpp::nbt::Reader &r) {
   State res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 4:
            res.__xx_put(name, EnumAllowedValues::deserialize_no_header(r));
            return;
         case 5:
            res.__xx_put(name, IntAllowedValues::deserialize_no_header(r));
            return;
         case 6:
            res.__xx_put(name, BlockPosition::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

State State::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return State();
   }
   return State::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> State::__xx_offsets {
   {"Name", {offsetof(State, name), sizeof(State::name), 1}},
   {"Tag", {offsetof(State, tag), sizeof(State::tag), 2}},
   {"AllowedValuesVariant", {offsetof(State, allowed_values_variant), sizeof(State::allowed_values_variant), 3}},
   {"EnumAllowedValues", {offsetof(State, enum_allowed_values), sizeof(State::enum_allowed_values), 4}},
   {"IntAllowedValues", {offsetof(State, int_allowed_values), sizeof(State::int_allowed_values), 5}},
   {"position", {offsetof(State, position), sizeof(State::position), 6}},
};

int State::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Block::serialize_no_header(minecpp::nbt::Writer &w) const {
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

std::unordered_map<std::string, __nbt_idl_offset> Block::__xx_offsets {
};

int Block::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

}