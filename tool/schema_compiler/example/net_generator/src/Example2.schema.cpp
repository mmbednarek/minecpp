#include "Example2.schema.h"
#include <algorithm>

namespace minecpp::example2 {

void Properties::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_string(this->name);
   writer.write_double(this->position);
   writer.write_big_endian(this->count);
   writer.write_varint(static_cast<std::int32_t>(this->meta.size()));
   for (const auto &[key_0, value_0] : this->meta) {
      writer.write_string(key_0);
      writer.write_string(value_0);
   }
}

Properties Properties::deserialize(::minecpp::network::message::Reader &reader) {
   Properties result;
   result.name = reader.read_string();
   result.position = reader.read_double();
   result.count = reader.read_big_endian<std::int16_t>();
   const auto meta_map_size = reader.read_varint();
   std::generate_n(std::inserter(result.meta, result.meta.begin()), static_cast<std::size_t>(meta_map_size), [&reader]() {
      std::string key_result;
      std::string value_result;
      key_result = reader.read_string();
      value_result = reader.read_string();
      return std::make_pair(key_result, value_result);
   });
   return result;
}

}