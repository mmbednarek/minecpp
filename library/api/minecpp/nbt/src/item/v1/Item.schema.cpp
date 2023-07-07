#include "item/v1/Item.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::item::v1 {

void Item::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "IsBlock");
   w.write_byte_content(static_cast<std::uint8_t>(is_block));
   w.write_header(minecpp::nbt::TagId::String, "CorrespondingBlockTag");
   w.write_string_content(corresponding_block_tag);
   w.write_header(minecpp::nbt::TagId::Int, "MaxItemStack");
   w.write_int_content(max_item_stack);
   w.end_compound();
}

void Item::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Item Item::deserialize_no_header(minecpp::nbt::Reader &r) {
   Item result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "IsBlock") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_block = r.read_byte();
         continue;
      }
      if (in_field_name == "CorrespondingBlockTag") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.corresponding_block_tag = r.read_str();
         continue;
      }
      if (in_field_name == "MaxItemStack") {
         ::minecpp::nbt::verify_tag("Item", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.max_item_stack = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Item Item::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Item::deserialize_no_header(r);
}

}