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
   char s[size];
   m_stream.read(s, static_cast<int>(size));
   return {s, size};
}

float Reader::read_float() const
{
   int v;
   m_stream.read((char *) &v, sizeof(int));
   v = boost::endian::big_to_native(v);
   return *reinterpret_cast<float *>(&v);
}

double Reader::read_double() const
{
   long long v;
   m_stream.read((char *) &v, sizeof(long long));
   v = boost::endian::big_to_native(v);
   return *reinterpret_cast<double *>(&v);
}

std::istream &Reader::get_stream()
{
   return m_stream;
}

}// namespace minecpp::util
