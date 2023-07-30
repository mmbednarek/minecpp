#include "ExampleNbt.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt {

void Properties::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Double, "Position");
   w.write_double_content(position);
   w.write_header(minecpp::nbt::TagId::Short, "Count");
   w.write_short_content(count);
   w.write_header(minecpp::nbt::TagId::Compound, "Meta");
   for (const auto &[key_0, value_0] : meta) {
      w.write_header(minecpp::nbt::TagId::String, key_0);
      w.write_string_content(value_0);
   }
   w.end_compound();
   w.end_compound();
}

void Properties::serialize(std::ostream &out_stream, std::string_view in_compound_name) const
{
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Properties Properties::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Properties result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("Properties", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "Position") {
         ::minecpp::nbt::verify_tag("Properties", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.position = r.read_float64();
         continue;
      }
      if (in_field_name == "Count") {
         ::minecpp::nbt::verify_tag("Properties", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.count = r.read_short();
         continue;
      }
      if (in_field_name == "Meta") {
         ::minecpp::nbt::verify_tag("Properties", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         std::map<std::string, std::string> map_result;
         for (const auto &[tag_id, key] : r.iterate_compound()) {
            map_result[key] = r.read_str();
         }
         result.meta = std::move(map_result);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Properties Properties::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Properties::deserialize_no_header(r);
}

}// namespace minecpp::nbt