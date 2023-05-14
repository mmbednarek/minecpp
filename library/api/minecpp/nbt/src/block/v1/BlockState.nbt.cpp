#include <minecpp/nbt/block/v1/BlockState.nbt.h>

namespace minecpp::nbt::block::v1 {

void BlockState::serialize_no_header(minecpp::nbt::Writer &w) const
{
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

void BlockState::serialize(std::ostream &out_stream, std::string_view in_compound_name) const
{
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   serialize_no_header(w);
}

BlockState BlockState::deserialize_no_header(minecpp::nbt::Reader &r)
{
   BlockState res;
   r.read_compound(
           [&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
              switch (tagid) {
              case minecpp::nbt::TagId::Byte: res.set_property(in_field_name, r.read_byte()); return;
              case minecpp::nbt::TagId::Int: res.set_property(in_field_name, r.read_int()); return;
              case minecpp::nbt::TagId::Compound:
                 if (in_field_name == "SolidFaces") {
                    res.set_property(in_field_name, common::v1::FaceMask::deserialize_no_header(r));
                    return;
                 }
                 break;
              default: break;
              }
              r.skip_payload(tagid);
           });
   return res;
}

BlockState BlockState::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BlockState::deserialize_no_header(r);
}

}// namespace minecpp::nbt::block::v1