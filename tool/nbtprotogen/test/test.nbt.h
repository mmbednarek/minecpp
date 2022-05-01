#ifndef PROTO_NBT_TEST_TEST_H
#define PROTO_NBT_TEST_TEST_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/writer.h>
#include <string>
#include <vector>

namespace proto::nbt::test {

#ifndef PROTO_NBT_TEST_TEST_H_OFFSET_CLASS
#define PROTO_NBT_TEST_TEST_H_OFFSET_CLASS
class __nbt_idl_offset {
 public:
   mb::size offset{};
   mb::size size{};
   int id{};
};
#endif//PROTO_NBT_TEST_TEST_H_OFFSET_CLASS

class Foo {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::map<std::string, std::int32_t>>) {
         if (name == "stuff") {
            this->stuff = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "value") {
            this->value = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string value{};
   std::map<std::string, std::int32_t> stuff{};
   Foo() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Foo deserialize_no_header(minecpp::nbt::Reader &r);
   static Foo deserialize(std::istream &in);
};

class Bar {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, minecpp::nbt::CompoundContent>) {
         if (name == "meta") {
            this->meta = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::map<std::string, Foo>>) {
         if (name == "foo_map") {
            this->foo_map = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<Foo>>) {
         if (name == "foo") {
            this->foo = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<Foo> foo{};
   std::map<std::string, Foo> foo_map{};
   minecpp::nbt::CompoundContent meta{};
   Bar() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Bar deserialize_no_header(minecpp::nbt::Reader &r);
   static Bar deserialize(std::istream &in);
};

}
#endif//PROTO_NBT_TEST_TEST_H
