#pragma once
#include "tag.h"
#include <cstdint>
#include <cstring>
#include <functional>
#include <mineutils/concepts.h>
#include <mineutils/format.h>
#include <mineutils/reader.h>
#include <numeric>
#include <string>

namespace NBT {

struct TagHeader {
   TagID id;
   std::string name;
};

class Reader : private Utils::Reader {
 public:
   explicit Reader(std::istream &s);

   typedef std::function<void(Reader &r, const TagID type, std::string name)>
       IterCallback;

   template <TagID t> tagid_type(t) must_find_tag(std::string name) {
      must_seek_tag<t>(name);
      return read_payload<t>();
   }

   template <TagID t> tagid_type(t) expect_tag(std::string name) {
      auto type = read_static(TagID::End);
      if (type == t) {
         throw Exception(
             Utils::format("[nbt] incorrect tag type expected {} got {}",
                           tagid_to_str(t), tagid_to_str(type)));
      }

      auto tag_name = read_string();
      if (tag_name != name) {
         throw Exception(Utils::format(
             "[nbt] incorrect tag name expected {} got {}", name, tag_name));
      }

      return read_payload<t>();
   }

   template <TagID t>
   tagid_type(t) find_value(std::string name, tagid_type(t) def) {
      if (!seek_tag<t>(name)) {
         return def;
      }
      return read_payload<t>();
   }

   template <TagID t> std::vector<tagid_type(t)> find_list(std::string name) {
      if (!seek_tag<t>(name)) {
         return std::vector<tagid_type(t)>();
      }
      return read_list_payload<t>();
   }

   template <TagID t> std::vector<tagid_type(t)> read_list_payload() {
      auto elm_type = read_static(TagID::End);
      if (elm_type != t) {
         throw Exception("invalid list type");
      }

      auto size = read_bswap<int>();
      std::vector<tagid_type(t)> result(size);
      for (int i = 0; i < size; i++) {
         result[i] = read_payload<t>();
      }

      return result;
   }

   void read_packed_ints(IndexAssignable auto &result, uint16_t bits,
                         size_t num_packets);

   void read_compound(
       std::function<void(Reader &r, TagID type, std::string key)> for_value);
   void read_list(std::function<void(Reader &)> for_elem);
   void foreach_long(std::function<void(long long value)> for_elem);

   bool find_bool_str(std::string name, bool def);
   void find_compound(std::string name);
   void leave_compound();
   void iter_compound(std::string name, const IterCallback &callback);
   void skip_payload(TagID tagid);
   TagHeader peek_tag();
   void check_signature();

   template <size_t s> std::array<uint8_t, s> read_array();

   template <size_t s> std::array<int, s> read_int_array();

   template <size_t s> std::array<uint64_t, s> read_long_array() {
      auto size = read_bswap<int>();
      assert(size == s);

      std::array<uint64_t, s> result;
      for (size_t i = 0; i < size; ++i) {
         result[i] = read_bswap<uint64_t>();
      }
      return result;
   }

   template <TagID t> inline tagid_type(t) read_payload() const = delete;

   inline std::istream &raw_stream();

 private:
#define payload_of(typeid, value)                                              \
   template <> inline tagid_type(typeid) read_payload<typeid>() const {        \
      return value;                                                            \
   }

   payload_of(TagID::Byte, read_static<uint8_t>(0));
   payload_of(TagID::Short, read_bswap<short>());
   payload_of(TagID::Int, read_bswap<int>());
   payload_of(TagID::Long, read_bswap<long long>());
   payload_of(TagID::Float, read_float());
   payload_of(TagID::Double, read_double());
   payload_of(TagID::ByteArray, read_byte_list());
   payload_of(TagID::String, read_string());
   payload_of(TagID::IntArray, read_int_list<int>());
   payload_of(TagID::LongArray, read_int_list<long long>());

   template <TagID t> bool seek_tag(std::string &name);

   template <TagID t> void must_seek_tag(std::string &name);
};

void Reader::read_packed_ints(IndexAssignable auto &result, uint16_t bits,
                              size_t num_packets) {
   uint8_t parts = bits / std::gcd(0x40, bits);
   auto cycles = num_packets / parts;

   size_t i = 0;
   for (uint32_t cycle = 0u; cycle < cycles; ++cycle) {
      uint16_t trail = 0u;
      uint8_t trail_size = 0u;
      for (uint8_t part = 0u; part < parts; ++part) {
         auto values = (0x40 + trail_size) / bits;
         auto packet = static_cast<uint64_t>(read_payload<NBT::Long>());
         uint16_t beg_bits = bits - trail_size;
         result[i++] =
             trail | ((packet & ((1u << beg_bits) - 1u)) << trail_size);
         packet >>= beg_bits;
         for (int n = 1u; n < values; ++n) {
            result[i++] = packet & ((1u << bits) - 1u);
            packet >>= bits;
         }
         trail = packet;
         trail_size = (0x40 + trail_size) % bits;
      }
   }
}

template <TagID t> void Reader::must_seek_tag(std::string &name) {
   if (!seek_tag<t>(name)) {
      std::string msg("could not find tag ");
      msg.append(name);
      throw Exception(msg);
   }
}

template <size_t s> std::array<uint8_t, s> Reader::read_array() {
   auto size = read_bswap<int>();
   assert(size == s);

   std::array<uint8_t, s> result;
   get_stream().read((char *)result.data(), s);
   return result;
}

template <size_t s> std::array<int, s> Reader::read_int_array() {
   auto size = read_bswap<int>();
   assert(size == s);

   std::array<int, s> result;
   for (size_t i = 0; i < size; ++i) {
      result[i] = read_bswap<int>();
   }
   return result;
}

template <TagID t> bool Reader::seek_tag(std::string &name) {
   for (;;) {
      auto type = read_static(TagID::End);
      if (type == TagID::End) {
         get_stream().seekg(-sizeof(TagID), std::ios_base::cur);
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
std::istream &Reader::raw_stream() { return get_stream(); }

} // namespace NBT
