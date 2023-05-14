#include <minecpp/nbt/item/v1/Item.nbt.h>

namespace minecpp::nbt::item::v1 {

void Item::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::Byte, "IsBlock");
   w.write_byte_content(static_cast<std::uint8_t>(is_block));
   w.write_header(minecpp::nbt::TagId::String, "CorrespondingBlockTag");
   w.write_string_content(corresponding_block_tag);
   w.write_header(minecpp::nbt::TagId::Int, "MaxItemStack");
   w.write_int_content(max_item_stack);
   w.end_compound();
}

void Item::serialize(std::ostream &out_stream, std::string_view in_compound_name) const
{
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   serialize_no_header(w);
}

Item Item::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Item res;
   r.read_compound(
           [&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
              switch (tagid) {
              case minecpp::nbt::TagId::Byte: res.set_property(in_field_name, r.read_byte()); return;
              case minecpp::nbt::TagId::Int: res.set_property(in_field_name, r.read_int()); return;
              case minecpp::nbt::TagId::String: res.set_property(in_field_name, r.read_str()); return;
              default: break;
              }
              r.skip_payload(tagid);
           });
   return res;
}

Item Item::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Item::deserialize_no_header(r);
}

}// namespace minecpp::nbt::item::v1