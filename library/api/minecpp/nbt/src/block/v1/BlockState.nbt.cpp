#include <minecpp/nbt/block/v1/BlockState.nbt.h>

namespace minecpp::nbt::block::v1 {

void BlockState::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "BlocksMovement");
   w.write_byte_content(blocks_movement);
   w.write_header(minecpp::nbt::TagId::Int, "Luminance");
   w.write_int_content(luminance);
   w.write_header(minecpp::nbt::TagId::Int, "Opacity");
   w.write_int_content(opacity);
   w.write_header(minecpp::nbt::TagId::Compound, "SolidFaces");
   solid_faces.serialize_no_header(w);
   w.end_compound();
}

void BlockState::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BlockState BlockState::deserialize_no_header(minecpp::nbt::Reader &r) {
   BlockState res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "SolidFaces") {
            res.__xx_put(name, common::v1::FaceMask::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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