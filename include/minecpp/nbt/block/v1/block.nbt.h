#ifndef MINECPP_NBT_BLOCK_V1_BLOCK_H
#define MINECPP_NBT_BLOCK_V1_BLOCK_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/common/v1/common.nbt.h>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/writer.h>
#include <string>
#include <vector>

namespace minecpp::nbt::block::v1 {

#ifndef MINECPP_NBT_BLOCK_V1_BLOCK_H_OFFSET_CLASS
#define MINECPP_NBT_BLOCK_V1_BLOCK_H_OFFSET_CLASS
class __nbt_idl_offset {
 public:
   mb::size offset{};
   mb::size size{};
   int id{};
};
#endif//MINECPP_NBT_BLOCK_V1_BLOCK_H_OFFSET_CLASS

class EnumAllowedValues {
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
   std::vector<std::string> values{};
   EnumAllowedValues() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static EnumAllowedValues deserialize_no_header(minecpp::nbt::Reader &r);
   static EnumAllowedValues deserialize(std::istream &in);
};

class IntAllowedValues {
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
   std::int32_t min_value{};
   std::int32_t max_value{};
   IntAllowedValues() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static IntAllowedValues deserialize_no_header(minecpp::nbt::Reader &r);
   static IntAllowedValues deserialize(std::istream &in);
};

class State {
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
   std::string name{};
   std::string tag{};
   std::int32_t allowed_values_variant{};
   EnumAllowedValues enum_allowed_values{};
   IntAllowedValues int_allowed_values{};
   common::v1::BlockPosition position{};
   State() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static State deserialize_no_header(minecpp::nbt::Reader &r);
   static State deserialize(std::istream &in);
};

class Block {
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
   Block() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Block deserialize_no_header(minecpp::nbt::Reader &r);
   static Block deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_BLOCK_V1_BLOCK_H
