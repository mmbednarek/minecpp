#include <minecpp/nbt/tag.h>
#include <minecpp/nbt/writer.h>

#include <minecpp/mineutils/format.h>
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

void serialize_compound_content(NBT::Writer &w, const CompoundContent &cc) {
   for (auto pair : cc) {
      w.write_header(pair.second.tag_id, pair.first);
      serialize_content(w, &pair.second);
   }
   w.end_compound();
}

void serialize_content(NBT::Writer &w, const Content *c) {
   switch (c->tag_id) {
   case TagId::Byte:
      w.write_byte_content(c->as<int8_t>());
      return;
   case TagId::Short:
      w.write_short_content(c->as<int16_t>());
      return;
   case TagId::Int:
      w.write_int_content(c->as<int32_t>());
      return;
   case TagId::Long:
      w.write_long_content(c->as<int64_t>());
      return;
   case TagId::Float:
      w.write_float_content(c->as<float>());
      return;
   case TagId::Double:
      w.write_double_content(c->as<double>());
      return;
   case TagId::ByteArray:
      w.write_bytes_content(c->as<std::vector<uint8_t>>());
      return;
   case TagId::String:
      w.write_string_content(c->as<std::string>());
      return;
   case TagId::List: {
      auto list = c->as<ListContent>();
      w.begin_list_no_header(list.tag_id, list.elements.size());
      for (auto elm : list) {
         serialize_content(w, &elm);
      }
      return;
   }
   case TagId::Compound: {
      auto compound = c->as<CompoundContent>();
      serialize_compound_content(w, compound);
      return;
   }
   case TagId::IntArray:
      w.write_ints_content(c->as<std::vector<int32_t>>());
      return;
   case TagId::LongArray:
      w.write_longs_content(c->as<std::vector<int64_t>>());
      return;
   }
}

void Content::serialize(const std::string_view name, std::ostream &s) const {
   Writer w(s);
   w.write_header(tag_id, name);
   serialize_content(w, this);
}

Content make_string(std::string s) {
   return Content{
           .tag_id = TagId::String,
           .content = std::move(s),
   };
}

}// namespace NBT
