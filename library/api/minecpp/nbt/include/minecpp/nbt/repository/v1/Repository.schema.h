#pragma once
#include "minecpp/nbt/block/v1/Block.schema.h"
#include "minecpp/nbt/block/v1/BlockState.schema.h"
#include "minecpp/nbt/item/v1/Item.schema.h"
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::repository::v1 {

class BlockEntry {
 public:
   std::int32_t id{};
   block::v1::Block block{};
   std::string tag{};
   BlockEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BlockEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BlockEntry deserialize(std::istream &in);
};

class ItemEntry {
 public:
   std::int32_t id{};
   item::v1::Item item{};
   std::string tag{};
   ItemEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ItemEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static ItemEntry deserialize(std::istream &in);
};

class EnumPropertyEntry {
 public:
   block::v1::EnumProperty property{};
   std::string tag{};
   EnumPropertyEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static EnumPropertyEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static EnumPropertyEntry deserialize(std::istream &in);
};

class IntPropertyEntry {
 public:
   block::v1::IntProperty property{};
   std::string tag{};
   IntPropertyEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static IntPropertyEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static IntPropertyEntry deserialize(std::istream &in);
};

class BoolPropertyEntry {
 public:
   block::v1::BoolProperty property{};
   std::string tag{};
   BoolPropertyEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BoolPropertyEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BoolPropertyEntry deserialize(std::istream &in);
};

class BlockStateEntry {
 public:
   std::int32_t id{};
   block::v1::BlockState state{};
   std::string tag{};
   BlockStateEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BlockStateEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BlockStateEntry deserialize(std::istream &in);
};

class Repository {
 public:
   std::vector<BlockStateEntry> block_states{};
   std::vector<BlockEntry> blocks{};
   std::vector<ItemEntry> items{};
   std::vector<EnumPropertyEntry> enum_properties{};
   std::vector<IntPropertyEntry> int_properties{};
   std::vector<BoolPropertyEntry> bool_properties{};
   Repository() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Repository deserialize_no_header(minecpp::nbt::Reader &r);
   static Repository deserialize(std::istream &in);
};

}
