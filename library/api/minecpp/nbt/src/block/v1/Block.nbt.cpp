#include <minecpp/nbt/block/v1/Block.nbt.h>

namespace minecpp::nbt::block::v1 {

void EnumProperty::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::List, "Label");
   w.begin_list_no_header(minecpp::nbt::TagId::String, values.size());
   std::for_each(values.begin(), values.end(), [&w](const auto &value) { w.write_string_content(value); });
   w.end_compound();
}

void EnumProperty::serialize(std::ostream &out_stream, std::string_view in_compound_name) const
{
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   serialize_no_header(w);
}

EnumProperty EnumProperty::deserialize_no_header(minecpp::nbt::Reader &r)
{
   EnumProperty res;
   r.read_compound(
           [&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
              switch (tagid) {
              case minecpp::nbt::TagId::String: res.set_property(in_field_name, r.read_str()); return;
              case minecpp::nbt::TagId::List: {
                 auto list_info0 = r.peek_list();
                 if (list_info0.size > 0) {
                    switch (list_info0.tagid) {
                    case minecpp::nbt::TagId::String: {
                       std::vector<std::string> ls(list_info0.size);
                       std::generate(ls.begin(), ls.end(), [&r]() { return r.read_str(); });
                       res.set_property(in_field_name, ls);
                       return;
                    }
                    default: break;
                    }
                    for (mb::size i = 0; i < list_info0.size; ++i) {
                       r.skip_payload(list_info0.tagid);
                    }
                 }
                 return;
              }
              default: break;
              }
              r.skip_payload(tagid);
           });
   return res;
}

EnumProperty EnumProperty::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return EnumProperty::deserialize_no_header(r);
}

void IntProperty::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Int, "MinValue");
   w.write_int_content(min_value);
   w.write_header(minecpp::nbt::TagId::Int, "MaxValue");
   w.write_int_content(max_value);
   w.end_compound();
}

void IntProperty::serialize(std::ostream &out_stream, std::string_view in_compound_name) const
{
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   serialize_no_header(w);
}

IntProperty IntProperty::deserialize_no_header(minecpp::nbt::Reader &r)
{
   IntProperty res;
   r.read_compound(
           [&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
              switch (tagid) {
              case minecpp::nbt::TagId::Int: res.set_property(in_field_name, r.read_int()); return;
              case minecpp::nbt::TagId::String: res.set_property(in_field_name, r.read_str()); return;
              default: break;
              }
              r.skip_payload(tagid);
           });
   return res;
}

IntProperty IntProperty::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return IntProperty::deserialize_no_header(r);
}

void BoolProperty::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.end_compound();
}

void BoolProperty::serialize(std::ostream &out_stream, std::string_view in_compound_name) const
{
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   serialize_no_header(w);
}

BoolProperty BoolProperty::deserialize_no_header(minecpp::nbt::Reader &r)
{
   BoolProperty res;
   r.read_compound(
           [&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
              switch (tagid) {
              case minecpp::nbt::TagId::String: res.set_property(in_field_name, r.read_str()); return;
              default: break;
              }
              r.skip_payload(tagid);
           });
   return res;
}

BoolProperty BoolProperty::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BoolProperty::deserialize_no_header(r);
}

void Block::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::List, "PropertyTags");
   w.begin_list_no_header(minecpp::nbt::TagId::String, property_tags.size());
   std::for_each(property_tags.begin(), property_tags.end(),
                 [&w](const auto &value) { w.write_string_content(value); });
   w.end_compound();
}

void Block::serialize(std::ostream &out_stream, std::string_view in_compound_name) const
{
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   serialize_no_header(w);
}

Block Block::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Block res;
   r.read_compound(
           [&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
              switch (tagid) {
              case minecpp::nbt::TagId::List: {
                 auto list_info0 = r.peek_list();
                 if (list_info0.size > 0) {
                    switch (list_info0.tagid) {
                    case minecpp::nbt::TagId::String: {
                       std::vector<std::string> ls(list_info0.size);
                       std::generate(ls.begin(), ls.end(), [&r]() { return r.read_str(); });
                       res.set_property(in_field_name, ls);
                       return;
                    }
                    default: break;
                    }
                    for (mb::size i = 0; i < list_info0.size; ++i) {
                       r.skip_payload(list_info0.tagid);
                    }
                 }
                 return;
              }
              default: break;
              }
              r.skip_payload(tagid);
           });
   return res;
}

Block Block::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Block::deserialize_no_header(r);
}

}// namespace minecpp::nbt::block::v1