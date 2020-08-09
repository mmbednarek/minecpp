#include "tag.h"

#include <mineutils/format.h>
#include <utility>

namespace NBT {

NamedTag::NamedTag(std::string name, TagId tag_id, std::any content) : name(std::move(name)), content{.tag_id = tag_id, .content = std::move(content)} {}

static std::string pad(int padding) {
   return std::string(padding, '\t');
}

template<typename I, char prefix>
static std::string format_int_vec(std::vector<I> vec, int padding = 0) {
   std::stringstream ss;

   auto it = vec.begin();
   if (it == vec.end()) {
      ss << "[]";
      return ss.str();
   }

   ss << '[' << prefix << ";\n";
   ss << pad(padding + 1) << static_cast<int64_t>(*it);
   std::for_each(
           ++it, vec.end(), [&ss, padding](const auto &el) {
              ss << ",\n"
                 << pad(padding + 1) << static_cast<int64_t>(el);
           });
   ss << '\n'
      << pad(padding) << ']';

   return ss.str();
}

static std::string format_list(ListContent list, int padding = 0) {
   std::stringstream ss;

   auto it = list.begin();
   if (it == list.end()) {
      ss << "[]";
      return ss.str();
   }

   ss << "[\n";
   ss << pad(padding + 1) << (*it).to_string(padding + 1);
   std::for_each(
           ++it, list.end(), [&ss, padding](const auto &el) {
              ss << ",\n"
                 << pad(padding + 1) << el.to_string(padding + 1);
           });
   ss << '\n'
      << pad(padding) << ']';

   return ss.str();
}

static std::string format_compound(std::map<std::string, Content> compound, int padding = 0) {
   std::stringstream ss;

   auto it = compound.begin();
   if (it == compound.end()) {
      ss << "{}";
      return ss.str();
   }

   ss << "{\n";
   ss << pad(padding + 1) << it->first << ": " << it->second.to_string(padding + 1);
   std::for_each(
           ++it, compound.end(), [&ss, padding](const auto &el) {
              ss << ",\n"
                 << pad(padding + 1) << el.first << ": " << el.second.to_string(padding + 1);
           });
   ss << '\n'
      << pad(padding) << '}';

   return ss.str();
}

std::string Content::to_string(int padding) const {
   switch (tag_id) {
      case TagId::End:
         return "<end>";
      case TagId::Byte:
         return Utils::format("{}b", static_cast<int32_t>(as<int8_t>()));
      case TagId::Short:
         return Utils::format("{}s", as<int16_t>());
      case TagId::Int:
         return std::to_string(as<int32_t>());
      case TagId::Long:
         return Utils::format("{}l", as<int64_t>());
      case TagId::Float:
         return Utils::format("{}f", as<float>());
      case TagId::Double:
         return Utils::format("{}d", as<double>());
      case TagId::ByteArray:
         return format_int_vec<uint8_t, 'B'>(as<std::vector<uint8_t>>(), padding);
      case TagId::String:
         return Utils::format("\"{}\"", as<std::string>());
      case TagId::List:
         return format_list(as<ListContent>(), padding);
      case TagId::Compound:
         return format_compound(as<std::map<std::string, Content>>(), padding);
      case TagId::IntArray:
         return format_int_vec<int32_t, 'I'>(as<std::vector<int32_t>>(), padding);
      case TagId::LongArray:
         return format_int_vec<int64_t, 'L'>(as<std::vector<int64_t>>(), padding);
   }
   return std::string();
}

bool Content::empty() const {
   return tag_id == TagId::End;
}

}// namespace NewNBT
