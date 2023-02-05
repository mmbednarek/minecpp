#ifndef MINECPP_NBT_REPOSITORY_V1_REPOSITORY_H
#define MINECPP_NBT_REPOSITORY_V1_REPOSITORY_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <minecpp/nbt/block/v1/Block.nbt.h>
#include <minecpp/nbt/block/v1/BlockState.nbt.h>
#include <minecpp/nbt/item/v1/Item.nbt.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::repository::v1 {

class BlockEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::Block>) {
         if (name == "Block") {
            this->block = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "Id") {
            this->id = std::forward<T>(value);
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
   std::int32_t id{};
   block::v1::Block block{};
   std::string tag{};
   BlockEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BlockEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BlockEntry deserialize(std::istream &in);
};

class ItemEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, item::v1::Item>) {
         if (name == "Item") {
            this->item = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "Id") {
            this->id = std::forward<T>(value);
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
   std::int32_t id{};
   item::v1::Item item{};
   std::string tag{};
   ItemEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ItemEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static ItemEntry deserialize(std::istream &in);
};

class EnumPropertyEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::EnumProperty>) {
         if (name == "Property") {
            this->property = std::forward<T>(value);
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
   block::v1::EnumProperty property{};
   std::string tag{};
   EnumPropertyEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static EnumPropertyEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static EnumPropertyEntry deserialize(std::istream &in);
};

class IntPropertyEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::IntProperty>) {
         if (name == "Property") {
            this->property = std::forward<T>(value);
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
   block::v1::IntProperty property{};
   std::string tag{};
   IntPropertyEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static IntPropertyEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static IntPropertyEntry deserialize(std::istream &in);
};

class BoolPropertyEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::BoolProperty>) {
         if (name == "Property") {
            this->property = std::forward<T>(value);
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
   block::v1::BoolProperty property{};
   std::string tag{};
   BoolPropertyEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BoolPropertyEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BoolPropertyEntry deserialize(std::istream &in);
};

class BlockStateEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, block::v1::BlockState>) {
         if (name == "State") {
            this->state = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "Id") {
            this->id = std::forward<T>(value);
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
   std::int32_t id{};
   block::v1::BlockState state{};
   std::string tag{};
   BlockStateEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BlockStateEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BlockStateEntry deserialize(std::istream &in);
};

class Repository {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::vector<BlockEntry>>) {
         if (name == "Blocks") {
            this->blocks = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<BlockStateEntry>>) {
         if (name == "BlockStates") {
            this->block_states = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<BoolPropertyEntry>>) {
         if (name == "BoolProperties") {
            this->bool_properties = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<EnumPropertyEntry>>) {
         if (name == "EnumProperties") {
            this->enum_properties = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<IntPropertyEntry>>) {
         if (name == "IntProperties") {
            this->int_properties = std::forward<T>(value);
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
   std::vector<BlockStateEntry> block_states{};
   std::vector<BlockEntry> blocks{};
   std::vector<ItemEntry> items{};
   std::vector<EnumPropertyEntry> enum_properties{};
   std::vector<IntPropertyEntry> int_properties{};
   std::vector<BoolPropertyEntry> bool_properties{};
   Repository() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Repository deserialize_no_header(minecpp::nbt::Reader &r);
   static Repository deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_REPOSITORY_V1_REPOSITORY_H
