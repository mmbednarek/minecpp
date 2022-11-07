#ifndef MINECPP_NBT_REPOSITORY_V1_REPOSITORY_H
#define MINECPP_NBT_REPOSITORY_V1_REPOSITORY_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/block/v1/Block.nbt.h>
#include <minecpp/nbt/item/v1/Item.nbt.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::repository::v1 {

class BlockEntry
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::Block>) {
         if (name == "Block") {
            this->block = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "Tag") {
            this->tag = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   block::v1::Block block{};
   std::string tag{};
   BlockEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BlockEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BlockEntry deserialize(std::istream &in);
};

class ItemEntry
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, item::v1::Item>) {
         if (name == "Item") {
            this->item = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "Tag") {
            this->tag = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   item::v1::Item item{};
   std::string tag{};
   ItemEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ItemEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static ItemEntry deserialize(std::istream &in);
};

class EnumStateEntry
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::EnumState>) {
         if (name == "State") {
            this->state = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "Tag") {
            this->tag = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   block::v1::EnumState state{};
   std::string tag{};
   EnumStateEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static EnumStateEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static EnumStateEntry deserialize(std::istream &in);
};

class IntStateEntry
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::IntState>) {
         if (name == "State") {
            this->state = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "Tag") {
            this->tag = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   block::v1::IntState state{};
   std::string tag{};
   IntStateEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static IntStateEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static IntStateEntry deserialize(std::istream &in);
};

class BoolStateEntry
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::BoolState>) {
         if (name == "State") {
            this->state = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "Tag") {
            this->tag = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   block::v1::BoolState state{};
   std::string tag{};
   BoolStateEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BoolStateEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BoolStateEntry deserialize(std::istream &in);
};

class Repository
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::vector<BlockEntry>>) {
         if (name == "Blocks") {
            this->blocks = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<BoolStateEntry>>) {
         if (name == "BoolStates") {
            this->bool_states = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<EnumStateEntry>>) {
         if (name == "EnumStates") {
            this->enum_states = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<IntStateEntry>>) {
         if (name == "IntStates") {
            this->int_states = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<ItemEntry>>) {
         if (name == "Items") {
            this->items = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<EnumStateEntry> enum_states{};
   std::vector<IntStateEntry> int_states{};
   std::vector<BoolStateEntry> bool_states{};
   std::vector<BlockEntry> blocks{};
   std::vector<ItemEntry> items{};
   Repository() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Repository deserialize_no_header(minecpp::nbt::Reader &r);
   static Repository deserialize(std::istream &in);
};

}// namespace minecpp::nbt::repository::v1
#endif//MINECPP_NBT_REPOSITORY_V1_REPOSITORY_H
