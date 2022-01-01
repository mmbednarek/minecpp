#ifndef MINECPP_NBT_COMMON_V1_COMMON_H
#define MINECPP_NBT_COMMON_V1_COMMON_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/writer.h>
#include <string>
#include <vector>

namespace minecpp::nbt::common::v1 {

#ifndef MINECPP_NBT_COMMON_V1_COMMON_H_OFFSET_CLASS
#define MINECPP_NBT_COMMON_V1_COMMON_H_OFFSET_CLASS
class __nbt_idl_offset {
 public:
   mb::size offset{};
   mb::size size{};
   int id{};
};
#endif//MINECPP_NBT_COMMON_V1_COMMON_H_OFFSET_CLASS

class ChunkPosition {
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
   std::int32_t y{};
   ChunkPosition() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ChunkPosition deserialize_no_header(minecpp::nbt::Reader &r);
   static ChunkPosition deserialize(std::istream &in);
};

class BlockPosition {
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
   std::int32_t y{};
   std::int32_t z{};
   BlockPosition() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BlockPosition deserialize_no_header(minecpp::nbt::Reader &r);
   static BlockPosition deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_COMMON_V1_COMMON_H
