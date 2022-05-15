#include <minecpp/nbt/parser.h>

namespace minecpp::nbt {

Parser::Parser(std::istream &stream) : reader(stream) {}

NamedTag Parser::read_tag()
{
   auto tag_id = read_tag_id();
   if (tag_id == TagId::End) {
      return NamedTag("", TagId::End, std::any());
   }
   auto name    = read_content_string();
   auto content = read_content(tag_id);
   return NamedTag(name, tag_id, content);
}

TagId Parser::read_tag_id() { return reader.read_static(TagId::End); }

std::any Parser::read_content(const TagId id) { return content_reader(id)(); }

std::function<std::any()> Parser::content_reader(const TagId id)
{
   switch (id) {
   case TagId::Byte: return [this]() { return read_content_byte(); };
   case TagId::Short: return [this]() { return read_content_short(); };
   case TagId::Int: return [this]() { return read_content_int(); };
   case TagId::Long: return [this]() { return read_content_long(); };
   case TagId::Float: return [this]() { return read_content_float(); };
   case TagId::Double: return [this]() { return read_content_double(); };
   case TagId::ByteArray: return [this]() { return read_content_byte_array(); };
   case TagId::String: return [this]() { return read_content_string(); };
   case TagId::List: return [this]() { return read_content_list(); };
   case TagId::Compound: return [this]() { return read_compound(); };
   case TagId::IntArray: return [this]() { return read_content_int_array(); };
   case TagId::LongArray: return [this]() { return read_content_long_array(); };
   default: return []() { return nullptr; };
   }
}

std::vector<std::any> Parser::read_content_n(const TagId id, std::size_t amount)
{
   std::vector<std::any> result(amount);
   auto content = content_reader(id);
   std::for_each(result.begin(), result.end(), [content](auto &element) { element = content(); });
   return result;
}

int8_t Parser::read_content_byte() { return reader.read_static(static_cast<int8_t>(0)); }

int16_t Parser::read_content_short() { return reader.read_bswap<short>(); }

int32_t Parser::read_content_int() { return reader.read_bswap<int>(); }

int64_t Parser::read_content_long() { return reader.read_bswap<uint64_t>(); }

float Parser::read_content_float() { return reader.read_float(); }

double Parser::read_content_double() { return reader.read_double(); }

std::vector<uint8_t> Parser::read_content_byte_array() { return reader.read_byte_vec(); }

std::string Parser::read_content_string() { return reader.read_string(); }

ListContent Parser::read_content_list()
{
   auto tag_id      = read_tag_id();
   std::size_t size = read_content_int();
   return ListContent{.tag_id = tag_id, .elements = read_content_n(tag_id, size)};
}

std::vector<int32_t> Parser::read_content_int_array() { return reader.read_int_list<int32_t>(); }

std::vector<int64_t> Parser::read_content_long_array() { return reader.read_int_list<int64_t>(); }

std::map<std::string, Content> Parser::read_compound()
{
   std::map<std::string, Content> result;
   for (;;) {
      auto content = read_tag();
      if (content.content.tag_id == TagId::End) {
         return result;
      }
      result[content.name] = content.content;
   }
}

}// namespace minecpp::nbt
