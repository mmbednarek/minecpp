#pragma once
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::common {

class ChunkPosition {
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
