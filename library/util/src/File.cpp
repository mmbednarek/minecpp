#include <minecpp/util/Cast.hpp>
#include <minecpp/util/Reader.h>

namespace minecpp::util {

Reader::Reader(std::istream &s) :
    m_stream(s)
{
}

std::vector<uint8_t> Reader::read_byte_vec() const
{
   auto size = read_big_endian<int>();
   std::vector<uint8_t> v(static_cast<std::size_t>(size));
   m_stream.read((char *) v.data(), size);
   return v;
}

std::string Reader::read_string() const
{
   auto size = static_cast<std::size_t>(read_big_endian<short>());
   std::string str(size, ' ');
   m_stream.read(str.data(), static_cast<int>(size));
   return str;
}

float Reader::read_float() const
{
   std::int32_t v;
   m_stream.read(reinterpret_cast<char *>(&v), sizeof(std::int32_t));
   v = boost::endian::big_to_native(v);
   return unsafe_cast<float>(v);
}

double Reader::read_double() const
{
   std::int64_t v;
   m_stream.read(reinterpret_cast<char *>(&v), sizeof(std::int64_t));
   v = boost::endian::big_to_native(v);
   return unsafe_cast<double>(v);
}

std::istream &Reader::get_stream()
{
   return m_stream;
}

}// namespace minecpp::util
