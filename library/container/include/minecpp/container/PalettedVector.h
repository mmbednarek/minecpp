#pragma once
#include "TightVector.h"
#include <algorithm>
#include <map>
#include <stdexcept>

namespace minecpp::container {

template<typename TValue>
class PalettedVector
{
 public:
   using value_type      = TValue;
   using size_type       = TightVector::size_type;
   using difference_type = TightVector::difference_type;
   using index_type      = TightVector::value_type;

   PalettedVector() = default;

   template<typename TIterator>
   PalettedVector(TIterator begin, TIterator end)
   {
      std::map<value_type, size_type> unique_values;
      std::for_each(begin, end, [&unique_values, index = 0](auto item_value) mutable {
         auto value = static_cast<value_type>(item_value);

         if (unique_values.contains(value))
            return;

         unique_values.emplace(value, index++);
      });

      m_palette.resize(unique_values.size());
      for (auto pair : unique_values) {
         m_palette[pair.second] = pair.first;
      }

      const auto data_size = static_cast<size_type>(end - begin);
      m_data.resize(data_size);

      auto at = begin;
      for (size_type i{0}; i < data_size; ++i) {
         m_data.set(i, static_cast<index_type>(unique_values[*at]));
         ++at;
      }
   }

   [[nodiscard]] constexpr value_type at(size_type index) const
   {
      auto palette_index = static_cast<size_type>(m_data.at(index));
      return m_palette.at(palette_index);
   }

   [[nodiscard]] constexpr value_type operator[](size_type index) const
   {
      return at(index);
   }

   void set(size_type index, const value_type &value)
   {
      auto palette_index = std::find(m_palette.begin(), m_palette.end(), value);
      if (palette_index == m_palette.end()) {
         m_palette.push_back(value);
         m_data.set(index, static_cast<index_type>(m_palette.size() - 1ul));
         return;
      }
      m_data.set(index, static_cast<index_type>(palette_index - m_palette.begin()));
   }

   [[nodiscard]] constexpr size_type size() const
   {
      return m_data.size();
   }

   template<typename TPaletteIterator, typename TIndexIterator>
   [[nodiscard]] static PalettedVector from_raw(TightVector::bits_type bits, TightVector::size_type size,
                                                TIndexIterator indices_begin, TIndexIterator indices_end,
                                                TPaletteIterator palette_begin, TPaletteIterator palette_end)
   {
      PalettedVector result;

      result.m_palette.resize(static_cast<std::size_t>(palette_end - palette_begin));
      std::copy(palette_begin, palette_end, result.m_palette.begin());

      result.m_data = TightVector::from_raw(bits, size, indices_begin, indices_end);

      return result;
   }

   template<typename TPaletteIterator, typename TIndexIterator>
   [[nodiscard]] static PalettedVector from_raw(TightVector::size_type size, TIndexIterator indices_begin,
                                                TIndexIterator indices_end, TPaletteIterator palette_begin,
                                                TPaletteIterator palette_end)
   {
      PalettedVector result;

      const auto palette_size = palette_end - palette_begin;

      result.m_palette.resize(static_cast<std::size_t>(palette_size));
      std::copy(palette_begin, palette_end, result.m_palette.begin());

      result.m_data =
              TightVector::from_raw(TightVector::min_bits_to_encode(static_cast<mb::i32>(palette_size)), size,
                                    indices_begin, indices_end);

      return result;
   }

   class Iterator
   {
    public:
      using iterator_category = std::forward_iterator_tag;

      PalettedVector &m_vector;
      TightVector::Iterator m_at;

      Iterator &operator++()
      {
         ++m_at;
         return *this;
      }

      Iterator operator++(int)
      {
         Iterator copy{*this};
         ++m_at;
         return copy;
      }

      bool operator==(Iterator other) const
      {
         return m_at == other.m_at;
      }

      bool operator!=(Iterator other) const
      {
         return m_at != other.m_at;
      }

      [[nodiscard]] value_type operator*() const
      {
         return m_vector.palette().at(static_cast<std::size_t>(*m_at));
      }
   };

   constexpr Iterator begin()
   {
      return Iterator{*this, m_data.begin()};
   }

   constexpr Iterator end()
   {
      return Iterator{*this, m_data.end()};
   }

   [[nodiscard]] constexpr const std::vector<value_type> &palette() const
   {
      return m_palette;
   }

   [[nodiscard]] constexpr const TightVector &indices() const
   {
      return m_data;
   }

   [[nodiscard]] constexpr TightVector &indices()
   {
      return m_data;
   }

 private:
   TightVector m_data;
   std::vector<value_type> m_palette;
};

}// namespace minecpp::container