#include <cassert>
#include <minecpp/nbt/Parser.h>
#include <minecpp/nbt/Reader.h>
#include <utility>

namespace minecpp::nbt {

Reader::Reader(std::istream &s) :
    minecpp::util::Reader(s)
{
}

void Reader::find_compound(std::string name)
{
   if (!seek_tag<TagId::Compound>(name)) {
      throw std::runtime_error("could not find tag");
   }
}

void Reader::leave_compound()
{
   for (;;) {
      auto type = read_static(TagId::End);
      if (type == TagId::End)
         return;
      auto name_size = read_big_endian<short>();
      get_stream().ignore(name_size);
      skip_payload(type);
   }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

void Reader::skip_payload(TagId tagid)
{
   int size;
   TagId elm_tagid;

   switch (tagid) {
   case TagId::Byte: get_stream().ignore(sizeof(uint8_t)); return;
   case TagId::Short: get_stream().ignore(sizeof(short)); return;
   case TagId::Int: get_stream().ignore(sizeof(int)); return;
   case TagId::Long: get_stream().ignore(sizeof(long long)); return;
   case TagId::Float: get_stream().ignore(sizeof(float)); return;
   case TagId::Double: get_stream().ignore(sizeof(double)); return;
   case TagId::List:
      elm_tagid = read_static(TagId::End);
      size      = read_big_endian<int>();
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
         size = read_big_endian<short>();
         get_stream().ignore(size);
         skip_payload(elm_tagid);
      }
   case TagId::String:
      size = read_big_endian<short>();
      get_stream().ignore(size);
      return;
   case TagId::ByteArray:
      size = read_big_endian<int>();
      get_stream().ignore(size * static_cast<int>(sizeof(std::uint8_t)));
      return;
   case TagId::IntArray:
      size = read_big_endian<int>();
      get_stream().ignore(size * static_cast<int>(sizeof(int)));
      return;
   case TagId::LongArray:
      size = read_big_endian<int>();
      get_stream().ignore(size * static_cast<int>(sizeof(long long)));
      return;
   case TagId::End: return;
   default: throw std::runtime_error("invalid tag");
   }
}

#pragma clang diagnostic pop

void Reader::iter_compound(std::string name, const IterCallback &callback)
{
   must_seek_tag<TagId::Compound>(name);
   for (;;) {
      auto type = read_static(TagId::End);
      if (type == TagId::End)
         return;
      auto tag_name = read_string();
      callback(*this, type, tag_name);
   }
}

bool Reader::find_bool_str(std::string name, bool def)
{
   if (!seek_tag<nbt::TagId::String>(name)) {
      return def;
   }
   return read_str() == "true";
}

TagHeader Reader::peek_tag()
{
   auto tagid = read_static(TagId::End);
   if (tagid == TagId::End) {
      return TagHeader{.id = tagid, .name{}};
   }
   return TagHeader{.id = tagid, .name = read_string()};
}

void Reader::check_signature()
{
   auto type      = read_static(TagId::End);
   auto name_size = read_big_endian<short>();
   if (type != TagId::Compound || name_size != 0) {
      throw std::runtime_error("stream does not contain correct nbt data");
   }
}

std::istream &Reader::raw_stream()
{
   return get_stream();
}

ListHeader Reader::peek_list()
{
   return ListHeader{read_static(nbt::TagId::End), static_cast<std::size_t>(read_big_endian<int>())};
}

CompoundContent Reader::read_compound_content()
{
   Parser p(raw_stream());
   return p.read_compound();
}

Reader::CompoundRange Reader::iterate_compound()
{
   return Reader::CompoundRange{*this};
}

Reader::CompoundIterator::CompoundIterator(Reader &reader, TagHeader current) :
    m_reader(reader),
    m_current(std::move(current))
{
}

const TagHeader &Reader::CompoundIterator::operator*() const
{
   return m_current;
}

Reader::CompoundIterator &Reader::CompoundIterator::operator++()
{
   m_current = m_reader.peek_tag();
   return *this;
}

bool Reader::CompoundIterator::operator==(const Reader::CompoundIterator &other) const
{
   return m_current.id == other.m_current.id;
}

Reader::CompoundRange::CompoundRange(Reader &reader) :
    m_reader(reader)
{
}

Reader::CompoundIterator Reader::CompoundRange::begin()
{
   return {m_reader, m_reader.peek_tag()};
}

Reader::CompoundIterator Reader::CompoundRange::end()
{
   return {
           m_reader,
           {TagId::End, ""}
   };
}

}// namespace minecpp::nbt
