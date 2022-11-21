#ifndef MINECPP_NBT_BLOCK_V1_BLOCK_H
#define MINECPP_NBT_BLOCK_V1_BLOCK_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::block::v1 {

class EnumState
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "Name") {
            this->name = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::string>>) {
         if (name == "Label") {
            this->values = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   std::vector<std::string> values{};
   EnumState() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static EnumState deserialize_no_header(minecpp::nbt::Reader &r);
   static EnumState deserialize(std::istream &in);
};

class IntState
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "MinValue") {
            this->min_value = std::forward<T>(value);
            return;
         }
         if (name == "MaxValue") {
            this->max_value = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "Name") {
            this->name = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   std::int32_t min_value{};
   std::int32_t max_value{};
   IntState() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static IntState deserialize_no_header(minecpp::nbt::Reader &r);
   static IntState deserialize(std::istream &in);
};

class BoolState
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "Name") {
            this->name = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   BoolState() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BoolState deserialize_no_header(minecpp::nbt::Reader &r);
   static BoolState deserialize(std::istream &in);
};

class Block
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "IsSolid") {
            this->is_solid = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::string>>) {
         if (name == "StateTags") {
            this->state_tags = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<std::string> state_tags{};
   std::int32_t is_solid{};
   Block() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Block deserialize_no_header(minecpp::nbt::Reader &r);
   static Block deserialize(std::istream &in);
};

}// namespace minecpp::nbt::block::v1
#endif//MINECPP_NBT_BLOCK_V1_BLOCK_H
