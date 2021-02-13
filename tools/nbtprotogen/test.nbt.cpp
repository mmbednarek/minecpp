#include "test.nbt.h"

namespace proto::nbt::test {

void Foo::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "value");
   w.write_string_content(value);
   w.write_header(minecpp::nbt::TagId::List, "stuff");
   w.begin_list_no_header(minecpp::nbt::TagId::ByteArray, stuff.size());
   std::for_each(stuff.begin(), stuff.end(), [&w](const auto &value) {
      w.write_bytes_content(value);
   });
}

void Foo::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

Foo Foo::deserialize_no_header(minecpp::nbt::Reader &r) {
   Foo res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         switch (list_info0.tagid) {
         case minecpp::nbt::TagId::ByteArray: {
            std::vector<std::vector<std::uint8_t>> ls(list_info0.size);
            std::generate(ls.begin(), ls.end(), [&r]() {
               return r.read_byte_vector();
            });
            res.__xx_put(name, ls);
            return;
         }
         default: 
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

Foo Foo::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Foo();
   }
   return Foo::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Foo::__xx_offsets {
   {"value", {offsetof(Foo, value), sizeof(Foo::value), 1}},
   {"stuff", {offsetof(Foo, stuff), sizeof(Foo::stuff), 2}},
};

int Foo::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Test::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "x");
   w.write_int_content(x);
   w.write_header(minecpp::nbt::TagId::String, "value");
   w.write_string_content(val);
   w.write_header(minecpp::nbt::TagId::List, "testval");
   w.begin_list_no_header(minecpp::nbt::TagId::List, testval.size());
   std::for_each(testval.begin(), testval.end(), [&w](const auto &value) {
      w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
      std::for_each(value.begin(), value.end(), [&w](const auto &value) {
         value.serialize_no_header(w);
      });
   });
}

void Test::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

Test Test::deserialize_no_header(minecpp::nbt::Reader &r) {
   Test res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         switch (list_info0.tagid) {
         case minecpp::nbt::TagId::List: {
            auto list_info1 = r.peek_list();
            switch (list_info1.tagid) {
            case minecpp::nbt::TagId::Compound: {
               switch (res.__xx_get_id(name)) {
               case 3: {
                  std::vector<std::vector<Foo>> ls(list_info0.size);
                  if (list_info0.size != 0) {
                     auto it = ls.begin();
                     *it = [&r, &list_info1]() {
                        std::vector<Foo> ls(list_info1.size);
                        std::generate(ls.begin(), ls.end(), [&r]() {
                           return Foo::deserialize_no_header(r);
                        });
                        return ls;
                     }();
                     std::generate(it + 1, ls.end(), [&r]() {
                        auto list_info1 = r.peek_list();
                        std::vector<Foo> ls(list_info1.size);
                        std::generate(ls.begin(), ls.end(), [&r]() {
                           return Foo::deserialize_no_header(r);
                        });
                        return ls;
                     });
                  }
                  res.__xx_put(name, ls);
                  return;
               }
               }
            }
            default: 
               for (mb::size i = 0; i < list_info1.size; ++i) {
                  r.skip_payload(list_info1.tagid);
               }
            }
            return;
         }
         default: 
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

Test Test::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Test();
   }
   return Test::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Test::__xx_offsets {
   {"x", {offsetof(Test, x), sizeof(Test::x), 1}},
   {"value", {offsetof(Test, val), sizeof(Test::val), 2}},
   {"testval", {offsetof(Test, testval), sizeof(Test::testval), 3}},
};

int Test::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

}