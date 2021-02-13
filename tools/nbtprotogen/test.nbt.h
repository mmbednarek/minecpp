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

#ifndef NBT_IDL_OFFSET_CLASS
#define NBT_IDL_OFFSET_CLASS
class __nbt_idl_offset {
 public:
   mb::size offset{};
   mb::size size{};
   int id{};
};
#endif//NBT_IDL_OFFSET_CLASS

class Foo {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   std::string value{};
   std::vector<std::vector<std::uint8_t>> stuff{};
   Foo() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Foo deserialize_no_header(minecpp::nbt::Reader &r);
   static Foo deserialize(std::istream &in);
};

class Test {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   std::int32_t x{};
   std::string val{};
   std::vector<std::vector<Foo>> testval{};
   Test() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Test deserialize_no_header(minecpp::nbt::Reader &r);
   static Test deserialize(std::istream &in);
};

}
#endif//PROTO_NBT_TEST_TEST_H
