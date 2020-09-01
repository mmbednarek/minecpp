// Generated using ProtoNBT generator
#pragma once
#include <string>
#include <vector>
#include <nbt/writer.h>
#include <nbt/reader.h>
#include <map>
#include <iostream>
#include <error/result.h>

namespace proto::nbt::test {

struct __nbt_offset { std::size_t offset, size; int id; };

struct Foo;
struct Test;
struct User;

struct Foo {
   std::string value{};
   std::vector<std::vector<std::uint8_t>> stuff{};

   Foo() = default;

   void serialize_no_header(NBT::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name = "") const;

   static Foo deserialize_no_header(NBT::Reader &r);
   static Foo deserialize(std::istream &in);

private:
   static std::map<std::string, __nbt_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) return;
      if (it->second.size != sizeof(T)) return;
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }
};

struct Test {
   std::int32_t x{};
   std::string val{};
   std::vector<std::int32_t> testval{};
   std::vector<std::vector<Foo>> values{};

   Test() = default;

   void serialize_no_header(NBT::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name = "") const;

   static Test deserialize_no_header(NBT::Reader &r);
   static Test deserialize(std::istream &in);

private:
   static std::map<std::string, __nbt_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) return;
      if (it->second.size != sizeof(T)) return;
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }
};

struct User {
   std::string name{};
   std::string surname{};

   User() = default;

   void serialize_no_header(NBT::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name = "") const;

   static User deserialize_no_header(NBT::Reader &r);
   static User deserialize(std::istream &in);

private:
   static std::map<std::string, __nbt_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) return;
      if (it->second.size != sizeof(T)) return;
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }
};

}//namespace proto::nbt::test
