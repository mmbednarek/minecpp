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
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "x") {
            this->x = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "y") {
            this->y = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ChunkPosition deserialize_no_header(minecpp::nbt::Reader &r);
   static ChunkPosition deserialize(std::istream &in);
};

class BlockPosition {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "x") {
            this->x = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "y") {
            this->y = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "z") {
            this->z = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BlockPosition deserialize_no_header(minecpp::nbt::Reader &r);
   static BlockPosition deserialize(std::istream &in);
};

class FaceMask {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "down") {
            this->down = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "east") {
            this->east = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "north") {
            this->north = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "south") {
            this->south = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "up") {
            this->up = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "west") {
            this->west = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static FaceMask deserialize_no_header(minecpp::nbt::Reader &r);
   static FaceMask deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_COMMON_V1_COMMON_H
