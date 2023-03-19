#pragma once
#include "Tag.h"
#include <cstdint>
#include <cstring>
#include <functional>
#include <mb/result.h>
#include <minecpp/util/Concepts.h>
#include <minecpp/util/Reader.h>
#include <numeric>
#include <string>

namespace minecpp::nbt {

struct TagHeader
{
   TagId id;
   std::string name;
};

struct ListHeader
{
   TagId tagid;
   std::size_t size;
};

class Reader : private minecpp::util::Reader
{
 public:
   explicit Reader(std::istream &s);

   typedef std::function<void(Reader &r, const TagId type, std::string name)> IterCallback;

   std::vector<float> read_float_list()
   {
      if (read_static(TagId::End) != TagId::Float) {
         throw std::runtime_error("invalid tag reading float list");
      }
      auto size = read_big_endian<int>();
      std::vector<float> result(static_cast<std::size_t>(size));
      std::generate(result.begin(), result.end(), [this]() { return read_float32(); });
      return result;
   }

   void read_packed_ints(auto &result, int bits, int num_packets);

   template<typename TFunction>
   void read_compound(TFunction for_elem);

   template<typename TCallback>
   mb::emptyres try_read_compound(TCallback for_value);

   template<typename TCallback>
   void read_list(TCallback for_elem);

   template<typename TCallback>
   void foreach_long(TCallback for_elem)
   {
      auto size = read_big_endian<int>();
      for (int i = 0; i < size; i++) {
         for_elem(read_big_endian<long long>());
      }
   }

   bool find_bool_str(std::string name, bool def);
   void find_compound(std::string name);
   void leave_compound();
   void iter_compound(std::string name, const IterCallback &callback);
   void skip_payload(TagId tagid);
   TagHeader peek_tag();
   ListHeader peek_list();
   void check_signature();

   template<std::size_t s>
   std::array<uint8_t, s> read_array();

   template<std::size_t s>
   std::array<int, s> read_int_array();

   template<std::size_t s>
   std::array<uint64_t, s> read_long_array()
   {
      auto size = static_cast<std::size_t>(read_big_endian<int>());
      assert(size == s);

      std::array<uint64_t, s> result;
      for (std::size_t i = 0; i < size; ++i) {
         result[i] = read_big_endian<uint64_t>();
      }
      return result;
   }

   int8_t read_byte()
   {
      return read_static<int8_t>(0);
   }

   int16_t read_short()
   {
      return read_big_endian<short>();
   }

   int32_t read_int()
   {
      return read_big_endian<int>();
   }

   int64_t read_long()
   {
      return read_big_endian<long long>();
   }

   float read_float32()
   {
      return read_float();
   }

   double read_float64()
   {
      return read_double();
   }

   std::vector<uint8_t> read_byte_vector()
   {
      return read_byte_vec();
   }

   std::string read_str()
   {
      return read_string();
   }

   std::vector<int32_t> read_int_vec()
   {
      return read_int_list<int>();
   }

   std::vector<int64_t> read_long_vec()
   {
      return read_int_list<int64_t>();
   }

   CompoundContent read_compound_content();

   std::istream &raw_stream();

 private:
   template<TagId t>
   bool seek_tag(std::string &name);

   template<TagId t>
   void must_seek_tag(std::string &name);
};

void Reader::read_packed_ints(auto &result, int bits, int num_packets)
{
   int parts{bits / std::gcd(0x40, bits)};
   int cycles{num_packets / parts};

   size_t i = 0;
   for (int cycle{0}; cycle < cycles; ++cycle) {
      std::uint64_t trail{0u};
      int trail_size{0};
      for (int part{0}; part < parts; ++part) {
         int values{(64 + trail_size) / bits};

         auto packet = static_cast<std::uint64_t>(read_long());
         int beg_bits{bits - trail_size};
         result[i++] = trail | ((packet & ((1u << beg_bits) - 1u)) << trail_size);
         packet >>= beg_bits;
         for (int n = 1u; n < values; ++n) {
            result[i++] = packet & ((1u << bits) - 1u);
            packet >>= bits;
         }
         trail      = packet;
         trail_size = (64 + trail_size) % bits;
      }
   }
}

template<TagId t>
void Reader::must_seek_tag(std::string &name)
{
   if (!seek_tag<t>(name)) {
      std::string msg("could not find tag ");
      msg.append(name);
      throw std::runtime_error(msg);
   }
}

template<size_t s>
std::array<uint8_t, s> Reader::read_array()
{
   auto size = read_big_endian<int>();
   assert(size == s);

   std::array<uint8_t, s> result;
   get_stream().read((char *) result.data(), size);
   return result;
}

template<size_t s>
std::array<int, s> Reader::read_int_array()
{
   int size{read_big_endian<int>()};
   assert(size == s);

   std::array<int, s> result;
   for (int i{0}; i < size; ++i) {
      result[i] = read_big_endian<int>();
   }
   return result;
}

template<TagId t>
bool Reader::seek_tag(std::string &name)
{
   for (;;) {
      auto type = read_static(TagId::End);
      if (type == TagId::End) {
         get_stream().seekg(-static_cast<int>(sizeof(TagId)), std::ios_base::cur);
         return false;
      }

      auto name_size = read_big_endian<short>();
      if (type != t || name_size != static_cast<short>(name.size())) {
         get_stream().seekg(name_size, std::ios_base::cur);
         skip_payload(type);
         continue;
      }

      assert(name_size > 0);

      std::string tag_name;
      tag_name.resize(static_cast<std::size_t>(name_size));
      get_stream().read(tag_name.data(), name_size);

      if (name != tag_name) {
         skip_payload(type);
         continue;
      }

      return true;
   }
}

template<typename TCallback>
mb::emptyres Reader::try_read_compound(TCallback for_value)
{
   for (;;) {
      auto header = peek_tag();
      if (header.id == nbt::TagId::End)
         return mb::ok;
      auto result = for_value(*this, header.id, header.name);
      MB_VERIFY(result);
   }
}

template<typename TCallback>
void Reader::read_list(TCallback for_elem)
{
   auto tagid = read_static(TagId::End);
   auto size  = read_big_endian<int>();
   if (tagid == TagId::End)
      return;

   for (int i = 0; i < size; i++) {
      for_elem(*this);
   }
}

template<typename TFunction>
void Reader::read_compound(TFunction for_elem)
{
   for (;;) {
      auto header = peek_tag();
      if (header.id == nbt::TagId::End)
         return;
      for_elem(*this, header.id, header.name);
   }
}

}// namespace minecpp::nbt
