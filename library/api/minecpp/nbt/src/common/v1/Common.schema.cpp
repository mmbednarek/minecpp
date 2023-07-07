#include "common/v1/Common.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::common::v1 {

void ChunkPosition::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "x");
   w.write_int_content(x);
   w.write_header(minecpp::nbt::TagId::Int, "y");
   w.write_int_content(y);
   w.end_compound();
}

void ChunkPosition::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChunkPosition ChunkPosition::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChunkPosition result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "x") {
         ::minecpp::nbt::verify_tag("ChunkPosition", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.x = r.read_int();
         continue;
      }
      if (in_field_name == "y") {
         ::minecpp::nbt::verify_tag("ChunkPosition", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.y = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChunkPosition ChunkPosition::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChunkPosition::deserialize_no_header(r);
}

void BlockPosition::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "x");
   w.write_int_content(x);
   w.write_header(minecpp::nbt::TagId::Int, "y");
   w.write_int_content(y);
   w.write_header(minecpp::nbt::TagId::Int, "z");
   w.write_int_content(z);
   w.end_compound();
}

void BlockPosition::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BlockPosition BlockPosition::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockPosition result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "x") {
         ::minecpp::nbt::verify_tag("BlockPosition", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.x = r.read_int();
         continue;
      }
      if (in_field_name == "y") {
         ::minecpp::nbt::verify_tag("BlockPosition", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.y = r.read_int();
         continue;
      }
      if (in_field_name == "z") {
         ::minecpp::nbt::verify_tag("BlockPosition", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.z = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BlockPosition BlockPosition::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BlockPosition::deserialize_no_header(r);
}

void FaceMask::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "down");
   w.write_byte_content(static_cast<std::uint8_t>(down));
   w.write_header(minecpp::nbt::TagId::Byte, "east");
   w.write_byte_content(static_cast<std::uint8_t>(east));
   w.write_header(minecpp::nbt::TagId::Byte, "north");
   w.write_byte_content(static_cast<std::uint8_t>(north));
   w.write_header(minecpp::nbt::TagId::Byte, "south");
   w.write_byte_content(static_cast<std::uint8_t>(south));
   w.write_header(minecpp::nbt::TagId::Byte, "up");
   w.write_byte_content(static_cast<std::uint8_t>(up));
   w.write_header(minecpp::nbt::TagId::Byte, "west");
   w.write_byte_content(static_cast<std::uint8_t>(west));
   w.end_compound();
}

void FaceMask::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

FaceMask FaceMask::deserialize_no_header(minecpp::nbt::Reader &r) {
   FaceMask result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "down") {
         ::minecpp::nbt::verify_tag("FaceMask", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.down = r.read_byte();
         continue;
      }
      if (in_field_name == "east") {
         ::minecpp::nbt::verify_tag("FaceMask", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.east = r.read_byte();
         continue;
      }
      if (in_field_name == "north") {
         ::minecpp::nbt::verify_tag("FaceMask", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.north = r.read_byte();
         continue;
      }
      if (in_field_name == "south") {
         ::minecpp::nbt::verify_tag("FaceMask", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.south = r.read_byte();
         continue;
      }
      if (in_field_name == "up") {
         ::minecpp::nbt::verify_tag("FaceMask", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.up = r.read_byte();
         continue;
      }
      if (in_field_name == "west") {
         ::minecpp::nbt::verify_tag("FaceMask", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.west = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

FaceMask FaceMask::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return FaceMask::deserialize_no_header(r);
}

}