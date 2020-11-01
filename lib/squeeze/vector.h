#pragma once
#include <array>
#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace Squeeze {

class Vector {
   std::vector<std::uint64_t> m_data;
   std::uint8_t m_bits;
   std::size_t m_size;

 public:
   template<typename I>
   Vector(std::uint8_t bits, std::vector<I> values) : m_bits(bits), m_size(values.size()) {
      int per_pack = 64 / bits;
      int packs = values.size() / per_pack;
      if (values.size() % per_pack != 0)
         ++packs;
      uint32_t mask = (1u << bits) - 1u;

      m_data.resize(packs);
      std::generate(m_data.begin(), m_data.end(), [&values, per_pack, bits, mask, i = 0]() mutable {
         uint64_t pack = 0;
         uint32_t shift = 0;
         for (int j = 1; j < per_pack; ++j) {
            pack |= static_cast<std::uint64_t>(values[i] & mask) << shift;
            ++i;
            if (i >= values.size()) {
               return pack;
            }
            shift += bits;
         }
         pack |= static_cast<std::uint64_t>(values[i] & mask) << shift;
         ++i;
         return pack;
      });
   }

   Vector();
   Vector(std::uint8_t bits, std::size_t size, std::vector<std::uint64_t> data);
   Vector(std::uint8_t bits, std::size_t size, std::vector<std::int64_t> i_data);
   Vector(std::uint8_t bits, std::size_t size, std::function<std::int32_t()> gen);

   [[nodiscard]] constexpr std::size_t size() const {
      return m_size;
   }
   [[nodiscard]] constexpr std::int8_t bits() const {
      return m_bits;
   }
   [[nodiscard]] constexpr const std::vector<uint64_t> &raw() const {
      return m_data;
   }

   [[nodiscard]] std::int32_t at(std::size_t i) const;
   [[nodiscard]] std::int32_t operator[](std::size_t i) const;

   void set(std::size_t i, std::int32_t value);
   void set_bits(std::uint8_t new_bits);
   void inc_bits();

   struct Iterator {
      Vector &vec;
      std::size_t pack;
      uint32_t offset;

      Iterator &operator++();

      Iterator operator++(int);

      bool operator==(Iterator other) const;

      bool operator!=(Iterator other) const;

      [[nodiscard]] std::int32_t operator*() const;

      using difference_type = Vector;
      using value_type = Vector;
      using pointer = const Vector *;
      using reference = const Vector &;
      using iterator_category = std::forward_iterator_tag;
   };

   Iterator begin();
   Iterator end();
};

}// namespace Squeeze