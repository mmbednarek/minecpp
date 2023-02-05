#ifndef MINECPP_NBT_COMMON_V1_COMMON_H
#define MINECPP_NBT_COMMON_V1_COMMON_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::common::v1 {

class ChunkPosition {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "x") {
            this->x = std::forward<T>(value);
            return;
         }
         if (name == "y") {
            this->y = std::forward<T>(value);
            return;
         }
         return;
      }
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

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "x") {
            this->x = std::forward<T>(value);
            return;
         }
         if (name == "y") {
            this->y = std::forward<T>(value);
            return;
         }
         if (name == "z") {
            this->z = std::forward<T>(value);
            return;
         }
         return;
      }
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

class FaceMask {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (name == "down") {
            this->down = std::forward<T>(value);
            return;
         }
         if (name == "east") {
            this->east = std::forward<T>(value);
            return;
         }
         if (name == "north") {
            this->north = std::forward<T>(value);
            return;
         }
         if (name == "south") {
            this->south = std::forward<T>(value);
            return;
         }
         if (name == "up") {
            this->up = std::forward<T>(value);
            return;
         }
         if (name == "west") {
            this->west = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t down{};
   std::int8_t east{};
   std::int8_t north{};
   std::int8_t south{};
   std::int8_t up{};
   std::int8_t west{};
   FaceMask() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static FaceMask deserialize_no_header(minecpp::nbt::Reader &r);
   static FaceMask deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_COMMON_V1_COMMON_H
