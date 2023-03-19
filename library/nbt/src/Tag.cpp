#include <minecpp/nbt/Tag.h>
#include <minecpp/nbt/Writer.h>

#include <fmt/format.h>
#include <sstream>
#include <utility>

namespace minecpp::nbt {

NamedTag::NamedTag(std::string name, TagId tag_id, std::any content) :
    name(std::move(name)),
    content{.tag_id = tag_id, .content = std::move(content)}
{
}

static std::string pad(int padding)
{
   std::string out(static_cast<std::size_t>(padding), '\t');
   return out;
}

template<typename I, char prefix>
static std::string format_int_vec(std::vector<I> vec, int padding = 0)
{
   std::stringstream ss;

   auto it = vec.begin();
   if (it == vec.end()) {
      ss << "[]";
      return ss.str();
   }

   ss << '[' << prefix << ";\n";
   ss << pad(padding + 1) << static_cast<int64_t>(*it);
   std::for_each(++it, vec.end(), [&ss, padding](const auto &el) {
      ss << ",\n" << pad(padding + 1) << static_cast<int64_t>(el);
   });
   ss << '\n' << pad(padding) << ']';

   return ss.str();
}

static std::string format_list(ListContent list, int padding = 0)
{
   std::stringstream ss;

   auto it = list.begin();
   if (it == list.end()) {
      ss << "[]";
      return ss.str();
   }

   ss << "[\n";
   ss << pad(padding + 1) << (*it).to_string(padding + 1);
   std::for_each(++it, list.end(), [&ss, padding](const auto &el) {
      ss << ",\n" << pad(padding + 1) << el.to_string(padding + 1);
   });
   ss << '\n' << pad(padding) << ']';

   return ss.str();
}

static std::string format_label(const std::string &label)
{
   auto it = std::find(label.begin(), label.end(), ':');
   if (it == label.end()) {
      return label;
   }
   return fmt::format("\"{}\"", label);
}

static std::string format_compound(std::map<std::string, Content> compound, int padding = 0)
{
   std::stringstream ss;

   auto it = compound.begin();
   if (it == compound.end()) {
      ss << "{}";
      return ss.str();
   }

   ss << "{\n";
   ss << pad(padding + 1) << format_label(it->first) << ": " << it->second.to_string(padding + 1);
   std::for_each(++it, compound.end(), [&ss, padding](const auto &el) {
      ss << ",\n" << pad(padding + 1) << format_label(el.first) << ": " << el.second.to_string(padding + 1);
   });
   ss << '\n' << pad(padding) << '}';

   return ss.str();
}

std::string Content::to_string(int padding) const
{
   switch (tag_id) {
   case TagId::End: return "<end>";
   case TagId::Byte: return fmt::format("{}b", static_cast<int32_t>(as<int8_t>()));
   case TagId::Short: return fmt::format("{}s", as<int16_t>());
   case TagId::Int: return std::to_string(as<int32_t>());
   case TagId::Long: return fmt::format("{}l", as<int64_t>());
   case TagId::Float: return fmt::format("{}f", as<float>());
   case TagId::Double: return fmt::format("{}d", as<double>());
   case TagId::ByteArray: return format_int_vec<uint8_t, 'B'>(as<std::vector<uint8_t>>(), padding);
   case TagId::String: return fmt::format("\"{}\"", as<std::string>());
   case TagId::List: return format_list(as<ListContent>(), padding);
   case TagId::Compound: return format_compound(as<std::map<std::string, Content>>(), padding);
   case TagId::IntArray: return format_int_vec<int32_t, 'I'>(as<std::vector<int32_t>>(), padding);
   case TagId::LongArray: return format_int_vec<int64_t, 'L'>(as<std::vector<int64_t>>(), padding);
   }
   return {};
}

bool Content::empty() const
{
   return tag_id == TagId::End;
}

void serialize_compound_content(nbt::Writer &w, const CompoundContent &cc)
{
   for (auto pair : cc) {
      w.write_header(pair.second.tag_id, pair.first);
      serialize_content(w, &pair.second);
   }
   w.end_compound();
}

void serialize_content(nbt::Writer &w, const Content *c)
{
   switch (c->tag_id) {
   case TagId::Byte: w.write_byte_content(static_cast<std::uint8_t>(c->as<int8_t>())); return;
   case TagId::Short: w.write_short_content(c->as<int16_t>()); return;
   case TagId::Int: w.write_int_content(c->as<int32_t>()); return;
   case TagId::Long: w.write_long_content(c->as<int64_t>()); return;
   case TagId::Float: w.write_float_content(c->as<float>()); return;
   case TagId::Double: w.write_double_content(c->as<double>()); return;
   case TagId::ByteArray: w.write_bytes_content(c->as<std::vector<uint8_t>>()); return;
   case TagId::String: w.write_string_content(c->as<std::string>()); return;
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
   case TagId::IntArray: w.write_ints_content(c->as<std::vector<int32_t>>()); return;
   case TagId::LongArray: w.write_longs_content(c->as<std::vector<int64_t>>()); return;
   default: break;
   }
}

void Content::serialize(const std::string_view name, std::ostream &s) const
{
   Writer w(s);
   w.write_header(tag_id, name);
   serialize_content(w, this);
}

Content make_string(std::string s)
{
   return Content{
           .tag_id  = TagId::String,
           .content = std::move(s),
   };
}

Content make_byte(std::int8_t bt)
{
   return Content{
           .tag_id  = TagId::Byte,
           .content = bt,
   };
}

Content make_short(std::int16_t bt)
{
   return Content{
           .tag_id  = TagId::Short,
           .content = bt,
   };
}

Content make_int(std::int32_t bt)
{
   return Content{
           .tag_id  = TagId::Int,
           .content = bt,
   };
}

Content make_long(std::int64_t bt)
{
   return Content{
           .tag_id  = TagId::Long,
           .content = bt,
   };
}

Content make_float(float value)
{
   return Content{
           .tag_id  = TagId::Float,
           .content = value,
   };
}

Content make_double(double value)
{
   return Content{
           .tag_id  = TagId::Double,
           .content = value,
   };
}

Content make_compound(CompoundContent cont)
{
   return Content{
           .tag_id  = TagId::Compound,
           .content = std::move(cont),
   };
}

Content make_list(ListContent cont)
{
   return Content{
           .tag_id  = TagId::List,
           .content = std::move(cont),
   };
}

}// namespace minecpp::nbt
