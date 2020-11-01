#include "reader.h"
#include "parser.h"
#include <cassert>

namespace NBT {

Reader::Reader(std::istream &s) : Utils::Reader(s) {}

void Reader::find_compound(std::string name) {
   if (!seek_tag<TagId::Compound>(name)) {
      throw std::runtime_error("could not find tag");
   }
}

void Reader::leave_compound() {
   for (;;) {
      auto type = read_static(TagId::End);
      if (type == TagId::End)
         return;
      auto name_size = read_bswap<short>();
      get_stream().ignore(name_size);
      skip_payload(type);
   }
}

void Reader::skip_payload(TagId tagid) {
   int size;
   TagId elm_tagid;

   switch (tagid) {
   case TagId::Byte:
      get_stream().ignore(sizeof(uint8_t));
      return;
   case TagId::Short:
      get_stream().ignore(sizeof(short));
      return;
   case TagId::Int:
      get_stream().ignore(sizeof(int));
      return;
   case TagId::Long:
      get_stream().ignore(sizeof(long long));
      return;
   case TagId::Float:
      get_stream().ignore(sizeof(float));
      return;
   case TagId::Double:
      get_stream().ignore(sizeof(double));
      return;
   case TagId::List:
      elm_tagid = read_static(TagId::End);
      size = read_bswap<int>();
      for (int i = 0; i < size; i++) {
         skip_payload(elm_tagid);
      }
      return;
   case TagId::Compound:
      for (;;) {
         elm_tagid = read_static(TagId::End);
         if (elm_tagid == TagId::End) {
            return;
         }
         size = read_bswap<short>();
         get_stream().ignore(size);
         skip_payload(elm_tagid);
      }
   case TagId::String:
      size = read_bswap<short>();
      get_stream().ignore(size);
      return;
   case TagId::ByteArray:
      size = read_bswap<int>();
      get_stream().ignore(size * sizeof(uint8_t));
      return;
   case TagId::IntArray:
      size = read_bswap<int>();
      get_stream().ignore(size * sizeof(int));
      return;
   case TagId::LongArray:
      size = read_bswap<int>();
      get_stream().ignore(size * sizeof(long long));
      return;
   case TagId::End:
      return;
   default:
      throw std::runtime_error("invalid tag");
   }
}

void Reader::iter_compound(std::string name, const IterCallback &callback) {
   must_seek_tag<TagId::Compound>(name);
   for (;;) {
      auto type = read_static(TagId::End);
      if (type == TagId::End)
         return;
      auto tag_name = read_string();
      callback(*this, type, tag_name);
   }
}

bool Reader::find_bool_str(std::string name, bool def) {
   if (!seek_tag<NBT::TagId::String>(name)) {
      return def;
   }
   return read_str() == "true";
}

TagHeader Reader::peek_tag() {
   auto tagid = read_static(TagId::End);
   if (tagid == TagId::End) {
      return TagHeader{.id = tagid};
   }
   return TagHeader{.id = tagid, .name = read_string()};
}

void Reader::check_signature() {
   auto type = read_static(TagId::End);
   auto name_size = read_bswap<short>();
   if (type != TagId::Compound || name_size != 0) {
      throw std::runtime_error("stream does not contain correct nbt data");
   }
}

void Reader::read_compound(
        std::function<void(Reader &r, TagId key, std::string)> for_elem) {
   for (;;) {
      auto header = peek_tag();
      if (header.id == NBT::TagId::End)
         return;
      for_elem(*this, header.id, header.name);
   }
}

result<empty> Reader::try_read_compound(std::function<result<empty>(Reader &, TagId, std::string)> for_value) {
   for (;;) {
      auto header = peek_tag();
      if (header.id == NBT::TagId::End)
         return result_ok;
      auto res = for_value(*this, header.id, header.name);
      if (!res.ok()) {
         return res.err();
      }
   }
}

void Reader::read_list(std::function<void(Reader &)> for_elem) {
   auto tagid = read_static(TagId::End);
   auto size = read_bswap<int>();
   if (tagid == TagId::End)
      return;

   for (int i = 0; i < size; i++) {
      for_elem(*this);
   }
}

void Reader::foreach_long(std::function<void(long long value)> for_elem) {
   auto size = read_bswap<int>();
   for (int i = 0; i < size; i++) {
      for_elem(read_bswap<long long>());
   }
}

std::istream &Reader::raw_stream() { return get_stream(); }

Utils::Vec3 Reader::read_vec3() {
   auto tagid = read_static(TagId::End);
   auto size = read_bswap<int>();
   if (tagid == TagId::End)
      return Utils::Vec3();

   if (size != 3) {
      for (int i = 0; i < size; ++i) {
         skip_payload(TagId::Double);
      }
      return Utils::Vec3();
   }

   return Utils::Vec3(read_float64(),
                      read_float64(),
                      read_float64());
}

ListHeader Reader::peek_list() {
   return ListHeader{read_static(NBT::TagId::End), static_cast<std::size_t>(read_bswap<int>())};
}

CompoundContent Reader::read_compound_content() {
   Parser p(raw_stream());
   return p.read_compound();
}

}// namespace NBT
