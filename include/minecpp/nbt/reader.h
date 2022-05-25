#pragma once
#include "tag.h"
#include <cstdint>
#include <cstring>
#include <functional>
#include <minecpp/error/result.h>
#include <minecpp/util/concepts.h>
#include <minecpp/util/format.h>
#include <minecpp/util/reader.h>
#include <minecpp/util/vec.h>
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
      auto size = read_bswap<int>();
      std::vector<float> result(size);
      std::generate(result.begin(), result.end(), [this]() { return read_float32(); });
      return result;
   }

   void read_packed_ints(auto &result, uint16_t bits, size_t num_packets);

   template<typename TFunction>
   void read_compound(TFunction for_elem)
   {
      for (;;) {
         auto header = peek_tag();
         if (header.id == nbt::TagId::End)
            return;
         for_elem(*this, header.id, header.name);
      }
   }

   result<empty>
   try_read_compound(std::function<result<empty>(Reader &r, TagId type, std::string key)> for_value);
   void read_list(std::function<void(Reader &)> for_elem);
   void foreach_long(std::function<void(long long value)> for_elem);

   bool find_bool_str(std::string name, bool def);
   void find_compound(std::string name);
   void leave_compound();
   void iter_compound(std::string name, const IterCallback &callback);
   void skip_payload(TagId tagid);
   TagHeader peek_tag();
   ListHeader peek_list();
   void check_signature();
   minecpp::util::Vec3 read_vec3();

   template<std::size_t s>
   std::array<uint8_t, s> read_array();

   template<std::size_t s>
   std::array<int, s> read_int_array();

   template<std::size_t s>
   std::array<uint64_t, s> read_long_array()
   {
      std::size_t size = read_bswap<int>();
      assert(size == s);

      std::array<uint64_t, s> result;
      for (std::size_t i = 0; i < size; ++i) {
         result[i] = read_bswap<uint64_t>();
      }
      return result;
   }

   uint8_t read_byte()
   {
      return read_static<uint8_t>(0);
   }

   int16_t read_short()
   {
      return read_bswap<short>();
   }

   int32_t read_int()
   {
      return read_bswap<int>();
   }

   int64_t read_long()
   {
      return read_bswap<long long>();
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

void Reader::read_packed_ints(auto &result, uint16_t bits, size_t num_packets)
{
   uint8_t parts = bits / std::gcd(0x40, bits);
   auto cycles   = num_packets / parts;

   size_t i = 0;
   for (uint32_t cycle = 0u; cycle < cycles; ++cycle) {
      uint16_t trail     = 0u;
      uint8_t trail_size = 0u;
      for (uint8_t part = 0u; part < parts; ++part) {
         auto values       = (0x40 + trail_size) / bits;
         auto packet       = static_cast<uint64_t>(read_long());
         uint16_t beg_bits = bits - trail_size;
         result[i++]       = trail | ((packet & ((1u << beg_bits) - 1u)) << trail_size);
         packet >>= beg_bits;
         for (int n = 1u; n < values; ++n) {
            result[i++] = packet & ((1u << bits) - 1u);
            packet >>= bits;
         }
         trail      = packet;
         trail_size = (0x40 + trail_size) % bits;
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
   auto size = read_bswap<int>();
   assert(size == s);

   std::array<uint8_t, s> result;
   get_stream().read((char *) result.data(), s);
   return result;
}

template<size_t s>
std::array<int, s> Reader::read_int_array()
{
   std::size_t size = read_bswap<int>();
   assert(size == s);

   std::array<int, s> result;
   for (size_t i = 0; i < size; ++i) {
      result[i] = read_bswap<int>();
   }
   return result;
}

template<TagId t>
bool Reader::seek_tag(std::string &name)
{
   for (;;) {
      auto type = read_static(TagId::End);
      if (type == TagId::End) {
         get_stream().seekg(-sizeof(TagId), std::ios_base::cur);
         return false;
      }

      auto name_size = read_bswap<short>();
      if (type != t || name_size != static_cast<short>(name.size())) {
         get_stream().seekg(name_size, std::ios_base::cur);
         skip_payload(type);
         continue;
      }

      char tag_name[name_size];
      get_stream().read(tag_name, name_size);

      if (memcmp(tag_name, name.data(), name_size) != 0) {
         skip_payload(type);
         continue;
      }

      return true;
   }
}

}// namespace minecpp::nbt
