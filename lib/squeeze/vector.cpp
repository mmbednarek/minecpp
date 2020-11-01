#include "vector.h"

namespace Squeeze {

constexpr std::uint32_t bitsLimit(std::uint8_t bits) {
   return 1u << bits;
}

Vector::Vector(std::uint8_t bits, std::size_t size, std::vector<std::uint64_t> data) : m_data(std::move(data)), m_bits(bits), m_size(size) {}

Vector::Vector(std::uint8_t bits, std::size_t size, std::vector<std::int64_t> data) : m_bits(bits), m_size(size) {
   m_data.resize(data.size());
   std::copy(data.begin(), data.end(), m_data.begin());
}

Vector::Vector() : m_bits(4), m_size(0) {}

Vector::Vector(std::uint8_t bits, std::size_t size, std::function<std::int32_t()> gen) : m_data(64 % bits == 0 ? (bits * size / 64) : (bits * size / 64) + 1), m_bits(bits), m_size(size) {
   int per_pack = 64 / bits;
   uint32_t mask = (1u << bits) - 1u;

   std::generate(m_data.begin(), m_data.end(), [&gen, size, per_pack, bits, mask, i = 0]() mutable {
      uint64_t pack = 0;
      uint32_t shift = 0;
      for (int j = 1; j < per_pack; ++j) {
         pack |= static_cast<std::uint64_t>(gen() & mask) << shift;
         ++i;
         if (i >= size) {
            return pack;
         }
         shift += bits;
      }
      pack |= static_cast<std::uint64_t>(gen() & mask) << shift;
      ++i;
      return pack;
   });
}

std::int32_t Vector::at(std::size_t i) const {
   uint32_t parts = 64 / m_bits;
   auto pack = i / parts;
   uint32_t offset = (i % parts) * m_bits;
   uint64_t mask = ((1u << m_bits) - 1u);
   uint64_t full_pack = m_data[pack];
   return (full_pack >> offset) & mask;
}

std::int32_t Vector::operator[](std::size_t i) const {
   return at(i);
}

void Vector::set(std::size_t i, std::int32_t value) {
   while (static_cast<std::uint32_t>(value) >= bitsLimit(m_bits)) {
      inc_bits();
   }

   uint32_t parts = 64 / m_bits;
   auto pack = i / parts;
   uint32_t offset = (i % parts) * m_bits;
   uint64_t mask = ((1u << m_bits) - 1u);

   uint64_t full_pack = m_data[pack];
   full_pack &= ~(mask << offset);
   full_pack |= (value & mask) << offset;
   m_data[pack] = full_pack;
}

Vector::Iterator Vector::begin() {
   return Iterator{.vec = *this, .pack = 0, .offset = 0};
}

Vector::Iterator Vector::end() {
   uint32_t parts = 64 / m_bits;
   return Iterator{.vec = *this, .pack = m_size / parts, .offset = static_cast<uint32_t>((m_size % parts) * m_bits)};
}

void Vector::set_bits(std::uint8_t new_bits) {
   int per_pack = 64 / new_bits;
   uint32_t mask = (1u << new_bits) - 1u;

   auto new_packs = m_size / per_pack;
   if (m_size % per_pack != 0)
      new_packs++;

   std::vector<std::uint64_t> resized(new_packs);
   std::generate(resized.begin(), resized.end(), [iter = begin(), end = end(), per_pack, new_bits, mask]() mutable {
      uint64_t pack = 0;
      uint32_t shift = 0;
      for (int j = 1; j < per_pack; ++j) {
         std::uint32_t val = *iter;
         pack |= static_cast<std::uint64_t>(val & mask) << shift;
         ++iter;
         if (iter == end) {
            return pack;
         }
         shift += new_bits;
      }
     std::uint32_t val = *iter;
     pack |= static_cast<std::uint64_t>(val & mask) << shift;
      ++iter;
      return pack;
   });

   if (new_packs != m_data.size()) {
      m_data.resize(new_packs);
   }
   std::copy(resized.begin(), resized.end(), m_data.begin());
   m_bits = new_bits;
}

void Vector::inc_bits() {
   set_bits(m_bits + 1);
}

Vector::Iterator &Vector::Iterator::operator++() {
   offset += vec.m_bits;
   if (offset + vec.m_bits > 64) {
      offset = 0;
      pack++;
   }
   return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
   auto value = *this;
   ++(*this);
   return value;
}

bool Vector::Iterator::operator==(Vector::Iterator other) const {
   return pack == other.pack && offset == other.offset;
}

bool Vector::Iterator::operator!=(Vector::Iterator other) const {
   return pack != other.pack || offset != other.offset;
}

std::int32_t Vector::Iterator::operator*() const {
   return (vec.m_data[pack] >> offset) & ((1u << vec.m_bits) - 1u);
}
}// namespace Squeeze
