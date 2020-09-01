// Generated using ProtoNBT generator
#include "test.h"

namespace proto::nbt::test {

int Foo::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Foo::serialize_no_header(NBT::Writer &w) const {
   w.write_string("value", this->value);
   w.begin_list("stuff", NBT::TagId::ByteArray, stuff.size());
   for (const auto &val0 : stuff) {
      w.write_bytes_content(val0);
   }
   w.end_compound();
}

void Foo::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::map<std::string, __nbt_offset> Foo::__xx_offsets {
   {"value", {offsetof(Foo, value), sizeof(Foo::value), 1}},
   {"stuff", {offsetof(Foo, stuff), sizeof(Foo::stuff), 2}},
};

Foo Foo::deserialize_no_header(NBT::Reader &r) {
   Foo res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::List: {
         auto list_info0 = r.peek_list();
         switch (list_info0.tagid) {
         case NBT::TagId::ByteArray: {
            std::vector<std::vector<std::uint8_t>> ls(list_info0.size);
            std::generate(ls.begin(), ls.end(), [&r]() { return r.read_byte_vector(); });
            res.__xx_put(name, ls);
            return;
         }
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Foo Foo::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Foo();
   }
   return Foo::deserialize_no_header(r);
}

int Test::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Test::serialize_no_header(NBT::Writer &w) const {
   w.write_int("x", this->x);
   w.write_string("value", this->val);
   w.begin_list("testval", NBT::TagId::Int, testval.size());
   for (const auto &val0 : testval) {
      w.write_int_content(val0);
   }
   w.begin_list("values", NBT::TagId::List, values.size());
   for (const auto &val0 : values) {
      w.begin_list_no_header(NBT::TagId::Compound, val0.size());
      for (const auto &val1 : val0) {
         val1.serialize_no_header(w);
      }
   }
   w.end_compound();
}

void Test::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::map<std::string, __nbt_offset> Test::__xx_offsets {
   {"x", {offsetof(Test, x), sizeof(Test::x), 1}},
   {"value", {offsetof(Test, val), sizeof(Test::val), 2}},
   {"testval", {offsetof(Test, testval), sizeof(Test::testval), 3}},
   {"values", {offsetof(Test, values), sizeof(Test::values), 4}},
};

Test Test::deserialize_no_header(NBT::Reader &r) {
   Test res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Int: 
         res.__xx_put(name, r.read_int());
         return;
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::List: {
         auto list_info0 = r.peek_list();
         switch (list_info0.tagid) {
         case NBT::TagId::Int: {
            std::vector<std::int32_t> ls(list_info0.size);
            std::generate(ls.begin(), ls.end(), [&r]() { return r.read_int(); });
            res.__xx_put(name, ls);
            return;
         }
         case NBT::TagId::List: {
            auto list_info1 = r.peek_list();
            switch (list_info1.tagid) {
            case NBT::TagId::Compound: {
               switch(res.__xx_get_id(name)) {
               case 4: {
                  std::vector<std::vector<Foo>> ls(list_info0.size);
                  if (list_info1.size == 0) {
                     return;
                  }
                  std::vector<Foo> ls_first(list_info1.size);
                  std::generate(ls_first.begin(), ls_first.end(), [&r]() { return Foo::deserialize_no_header(r); });
                  ls[0] = ls_first;
                  std::generate(ls.begin()+1, ls.end(), [&r, &list_info1]() {
                     list_info1 = r.peek_list();
                     std::vector<Foo> ls(list_info1.size);
                     std::generate(ls.begin(), ls.end(), [&r]() { return Foo::deserialize_no_header(r); });
                     return ls;
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               }
               break;
            }
            }
            break;
         }
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Test Test::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Test();
   }
   return Test::deserialize_no_header(r);
}

int User::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void User::serialize_no_header(NBT::Writer &w) const {
   w.write_string("name", this->name);
   w.write_string("surname", this->surname);
   w.end_compound();
}

void User::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::map<std::string, __nbt_offset> User::__xx_offsets {
   {"name", {offsetof(User, name), sizeof(User::name), 1}},
   {"surname", {offsetof(User, surname), sizeof(User::surname), 2}},
};

User User::deserialize_no_header(NBT::Reader &r) {
   User res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

User User::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return User();
   }
   return User::deserialize_no_header(r);
}

}// namespace proto::nbt::test
