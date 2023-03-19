#include <minecpp/nbt/common/v1/Common.nbt.h>

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
   serialize_no_header(w);
}

ChunkPosition ChunkPosition::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChunkPosition res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

BlockPosition BlockPosition::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockPosition res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

FaceMask FaceMask::deserialize_no_header(minecpp::nbt::Reader &r) {
   FaceMask res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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