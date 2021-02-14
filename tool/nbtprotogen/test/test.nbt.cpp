#include "test.nbt.h"

namespace proto::nbt::test {

void Foo::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "value");
   w.write_string_content(value);
   w.write_header(minecpp::nbt::TagId::Compound, "stuff");
   std::for_each(stuff.begin(), stuff.end(), [&w](const auto &pair) {
      w.write_header(minecpp::nbt::TagId::Int, pair.first);
      w.write_int_content(pair.second);
   });
   w.end_compound();
   w.end_compound();
}

void Foo::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Foo Foo::deserialize_no_header(minecpp::nbt::Reader &r) {
   Foo res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 2:
            r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
               if (tagid != minecpp::nbt::TagId::Int) {
                  r.skip_payload(tagid);
                  return;
               }
               res.stuff.insert(std::make_pair(name, r.read_int()));
            });
            return;
         }
         break;
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

void Bar::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "foo");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, foo.size());
   std::for_each(foo.begin(), foo.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::Compound, "foo_map");
   std::for_each(foo_map.begin(), foo_map.end(), [&w](const auto &pair) {
      w.write_header(minecpp::nbt::TagId::Compound, pair.first);
      pair.second.serialize_no_header(w);
   });
   w.end_compound();
   w.write_header(minecpp::nbt::TagId::Compound, "meta");
   minecpp::nbt::serialize_compound_content(w, meta);
   w.end_compound();
}

void Bar::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Bar Bar::deserialize_no_header(minecpp::nbt::Reader &r) {
   Bar res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 2:
            r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
               if (tagid != minecpp::nbt::TagId::Compound) {
                  r.skip_payload(tagid);
                  return;
               }
               res.foo_map.insert(std::make_pair(name, Foo::deserialize_no_header(r)));
            });
            return;
         case 3:
            res.__xx_put(name, r.read_compound_content());
            return;
         }
         break;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         switch (list_info0.tagid) {
         case minecpp::nbt::TagId::Compound: {
            switch (res.__xx_get_id(name)) {
            case 1: {
               std::vector<Foo> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() {
                  return Foo::deserialize_no_header(r);
               });
               res.__xx_put(name, ls);
               return;
            }
            }
            break;
         }
         }
         for (mb::size i = 0; i < list_info0.size; ++i) {
            r.skip_payload(list_info0.tagid);
         }
         return;
      }
      }
      r.skip_payload(tagid);
   });
   return res;
}

Bar Bar::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Bar();
   }
   return Bar::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Bar::__xx_offsets {
   {"foo", {offsetof(Bar, foo), sizeof(Bar::foo), 1}},
   {"foo_map", {offsetof(Bar, foo_map), sizeof(Bar::foo_map), 2}},
   {"meta", {offsetof(Bar, meta), sizeof(Bar::meta), 3}},
};

int Bar::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

}