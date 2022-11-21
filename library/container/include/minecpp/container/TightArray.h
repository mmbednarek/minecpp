#pragma once
#include <array>
#include <cstdint>
#include <cstdio>
#include <mb/int.h>
#include <utility>

namespace minecpp::container {

template<typename TValue, std::size_t CSize, typename TRaw, std::uint8_t CBits>
class TightArray
{
 public:
   using value_type      = TValue;
   using size_type       = mb::size;
   using difference_type = ssize_t;
   using raw_value_type  = TRaw;

   constexpr static auto items_per_pack = 8ull * sizeof(raw_value_type) / CBits;
   constexpr static auto raw_size =
           CSize % items_per_pack == 0 ? (CSize / items_per_pack) : (CSize / items_per_pack) + 1;
   constexpr static auto pack_count =
           (CSize % items_per_pack == 0) ? (CSize / items_per_pack) : (1 + CSize / items_per_pack);
   constexpr static auto bit_mask = (1ull << CBits) - 1u;

   TightArray() = default;

   template<typename TIterator>
   TightArray(TIterator begin, TIterator end)
   {
      auto at = begin;
      for (auto &pack : m_data) {
         pack          = 0;
         mb::u32 shift = 0;
         for (mb::u32 j{1}; j < items_per_pack; ++j) {
            pack |= static_cast<mb::u64>(*at & bit_mask) << shift;
            ++at;

            if (at == end) {
               break;
            }

            shift += CBits;
         }

         if (at == end) {
            break;
         }

         pack |= static_cast<mb::u64>(*at & bit_mask) << shift;
         ++at;
      }
   }

   [[nodiscard]] value_type at(std::size_t i) const
   {
      auto pack      = i / items_per_pack;
      auto offset    = (i % items_per_pack) * CBits;
      auto full_pack = m_data[pack];

      return (full_pack >> offset) & bit_mask;
   }

   [[nodiscard]] constexpr const std::array<raw_value_type, raw_size> &raw() const
   {
      return m_data;
   }

   [[nodiscard]] constexpr size_type size() const
   {
      return CSize;
   }

   void set(size_type i, value_type value)
   {
      auto pack   = i / items_per_pack;
      auto offset = (i % items_per_pack) * CBits;

      auto full_pack = m_data[pack];
      full_pack &= ~(bit_mask << offset);
      full_pack |= (static_cast<std::uint64_t>(value) & bit_mask) << offset;
      m_data[pack] = full_pack;
   }

   void reset()
   {
      std::fill(m_data.begin(), m_data.end(), 0);
   }

   void fill(int size, int value)
   {
      m_data.resize(size);
      std::fill(m_data.begin(), m_data.end(), value);
   }

   template<typename TIterator>
   static TightArray from_raw(TIterator begin, TIterator end)
   {
      TightArray result;
      std::copy(begin, end, result.m_data.begin());
      return result;
   }

 private:
   std::array<raw_value_type, raw_size> m_data{};
};

}// namespace minecpp::container