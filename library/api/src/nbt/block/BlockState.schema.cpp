#include "nbt/block/BlockState.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::block {

void BlockState::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "BlocksMovement");
   w.write_byte_content(static_cast<std::uint8_t>(blocks_movement));
   w.write_header(minecpp::nbt::TagId::Int, "Luminance");
   w.write_int_content(luminance);
   w.write_header(minecpp::nbt::TagId::Int, "Opacity");
   w.write_int_content(opacity);
   w.write_header(minecpp::nbt::TagId::Compound, "SolidFaces");
   solid_faces.serialize_no_header(w);
   w.end_compound();
}

void BlockState::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BlockState BlockState::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockState result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "BlocksMovement") {
         ::minecpp::nbt::verify_tag("BlockState", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.blocks_movement = r.read_byte();
         continue;
      }
      if (in_field_name == "Luminance") {
         ::minecpp::nbt::verify_tag("BlockState", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.luminance = r.read_int();
         continue;
      }
      if (in_field_name == "Opacity") {
         ::minecpp::nbt::verify_tag("BlockState", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.opacity = r.read_int();
         continue;
      }
      if (in_field_name == "SolidFaces") {
         ::minecpp::nbt::verify_tag("BlockState", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.solid_faces = common::FaceMask::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BlockState BlockState::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BlockState::deserialize_no_header(r);
}

}