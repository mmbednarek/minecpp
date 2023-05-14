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

class EnumProperty
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "Name") {
            this->name = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::string>>) {
         if (in_field_name == "Label") {
            this->values = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   std::vector<std::string> values{};
   EnumProperty() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static EnumProperty deserialize_no_header(minecpp::nbt::Reader &r);
   static EnumProperty deserialize(std::istream &in);
};

class IntProperty
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "MinValue") {
            this->min_value = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "MaxValue") {
            this->max_value = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "Name") {
            this->name = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   std::int32_t min_value{};
   std::int32_t max_value{};
   IntProperty() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static IntProperty deserialize_no_header(minecpp::nbt::Reader &r);
   static IntProperty deserialize(std::istream &in);
};

class BoolProperty
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "Name") {
            this->name = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   BoolProperty() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BoolProperty deserialize_no_header(minecpp::nbt::Reader &r);
   static BoolProperty deserialize(std::istream &in);
};

class Block
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::vector<std::string>>) {
         if (in_field_name == "PropertyTags") {
            this->property_tags = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<std::string> property_tags{};
   Block() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Block deserialize_no_header(minecpp::nbt::Reader &r);
   static Block deserialize(std::istream &in);
};

}// namespace minecpp::nbt::block::v1
#endif//MINECPP_NBT_BLOCK_V1_BLOCK_H
