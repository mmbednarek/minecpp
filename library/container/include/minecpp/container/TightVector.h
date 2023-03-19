#pragma once
#include <algorithm>
#include <functional>
#include <mb/int.h>
#include <numeric>
#include <vector>

namespace minecpp::container {

class TightVector
{
 public:
   using value_type      = mb::i32;
   using size_type       = mb::size;
   using difference_type = ssize_t;
   using raw_value_type  = mb::u64;
   using bits_type       = mb::u8;

   template<typename TIter>
   TightVector(bits_type bits, TIter begin, TIter end) :
       m_bits{bits},
       m_size{static_cast<size_type>(end - begin)}
   {
      auto per_pack = 64u / bits;
      auto packs    = m_size / per_pack;
      if (m_size % per_pack != 0)
         ++packs;

      auto mask = (1u << bits) - 1u;

      m_data.resize(static_cast<size_type>(packs));

      auto at = begin;
      for (auto &pack : m_data) {
         pack          = 0;
         mb::u32 shift = 0;
         for (mb::u32 j{1}; j < per_pack; ++j) {
            pack |= (static_cast<mb::u64>(*at) & mask) << shift;
            ++at;

            if (at == end) {
               break;
            }

            shift += bits;
         }

         if (at == end) {
            break;
         }

         pack |= (static_cast<mb::u64>(*at) & mask) << shift;
         ++at;
      }
   }

   template<typename TIterator>
   TightVector(TIterator begin, TIterator end) :
       TightVector(
               std::accumulate(begin, end, bits_type{0u},
                               [](mb::u8 lhs, auto rhs) { return std::max(lhs, min_bits_to_encode(rhs)); }),
               begin, end)
   {
   }

   TightVector();

   template<typename TIterator>
   static TightVector from_raw(bits_type bits, size_type size, TIterator begin, TIterator end)
   {
      std::vector<raw_value_type> raw;
      raw.resize(static_cast<std::size_t>(end - begin));
      std::copy(begin, end, raw.begin());
      return {bits, size, std::move(raw)};
   }

   [[nodiscard]] constexpr size_type size() const
   {
      return m_size;
   }

   [[nodiscard]] constexpr bits_type bits() const
   {
      return m_bits;
   }

   [[nodiscard]] constexpr const std::vector<mb::u64> &raw() const
   {
      return m_data;
   }

   [[nodiscard]] value_type at(size_type i) const;
   [[nodiscard]] value_type operator[](size_type i) const;

   void push_back(value_type value);

   void set(size_type i, value_type value);
   void set_bits(mb::u8 new_bits);
   void increase_bits();

   void resize(size_type new_size);

   struct Iterator
   {
      using pointer           = TightVector::value_type *;
      using reference         = TightVector::value_type &;
      using iterator_category = std::forward_iterator_tag;

      const TightVector &vec;
      mb::size pack;
      mb::u32 offset;

      Iterator &operator++();
      const Iterator operator++(int);

      bool operator==(Iterator other) const;

      bool operator!=(Iterator other) const;

      [[nodiscard]] value_type operator*() const;
   };

   [[nodiscard]] Iterator begin() const;
   [[nodiscard]] Iterator end() const;

   [[nodiscard]] static constexpr mb::u8 min_bits_to_encode(mb::i32 value)
   {
      mb::u8 result = 1;
      while (value > 1) {
         ++result;
         value /= 2;
      }
      return result;
   }

 private:
   TightVector(bits_type bits, size_type size, std::vector<raw_value_type> data);

   std::vector<raw_value_type> m_data{};
   bits_type m_bits{};
   size_type m_size{};
};

}// namespace minecpp::container
