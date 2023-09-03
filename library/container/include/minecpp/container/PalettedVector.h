#pragma once
#include "TightVector.h"

#include "minecpp/net/Chunk.schema.h"

#include <algorithm>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>

namespace minecpp::container {

enum class PaletteType
{
   Empty,
   SingleValue,
   Indirect,
   Direct
};

template<typename TValue, std::size_t CIndirectLimit>
class PalettedVector
{
 public:
   using value_type      = TValue;
   using size_type       = TightVector::size_type;
   using difference_type = TightVector::difference_type;
   using index_type      = TightVector::value_type;

   class Iterator
   {
    public:
      using iterator_category = std::forward_iterator_tag;

      PalettedVector &m_vector;
      TightVector::Iterator m_at;
      std::size_t m_at_index{};

      Iterator &operator++()
      {
         ++m_at;
         ++m_at_index;
         return *this;
      }

      Iterator operator++(int)
      {
         Iterator copy{*this};
         ++m_at;
         ++m_at_index;
         return copy;
      }

      bool operator==(Iterator other) const
      {
         if (m_vector.m_type == PaletteType::SingleValue)
            return m_at_index == other.m_at_index;

         return m_at == other.m_at;
      }

      bool operator!=(Iterator other) const
      {
         if (m_vector.m_type == PaletteType::SingleValue)
            return m_at_index != other.m_at_index;

         return m_at != other.m_at;
      }

      [[nodiscard]] value_type operator*() const
      {
         std::shared_lock lk{m_vector.m_mutex};

         switch (m_vector.m_type) {
         case PaletteType::SingleValue: {
            return m_vector.m_palette[0];
         }
         case PaletteType::Indirect: {
            return m_vector.palette().at(static_cast<std::size_t>(*m_at));
         }
         case PaletteType::Direct: {
            return *m_at;
         }
         default: throw std::runtime_error("paletted-vector: no such item");
         }
      }
   };

   PalettedVector() = default;

   PalettedVector(const PalettedVector &other) :
       m_data(other.m_data),
       m_palette(other.m_palette),
       m_type(other.m_type),
       m_size(other.m_size)
   {
   }

   PalettedVector &operator=(const PalettedVector &other)
   {
      m_data    = other.m_data;
      m_palette = other.m_palette;
      m_type    = other.m_type;
      m_size    = other.m_size;
      return *this;
   }

   PalettedVector(PalettedVector &&other) noexcept :
           m_data(std::move(other.m_data)),
           m_palette(std::move(other.m_palette)),
           m_type(std::move(other.m_type)),
           m_size(std::move(other.m_size))
   {
   }

   PalettedVector &operator=(PalettedVector &&other) noexcept
   {
      m_data    = std::move(other.m_data);
      m_palette = std::move(other.m_palette);
      m_type    = std::move(other.m_type);
      m_size    = std::move(other.m_size);
      return *this;
   }

   template<typename TIterator>
   PalettedVector(TIterator begin, TIterator end)
   {
      if (begin == end)
         return;

      // -- DETERMINE THE UNIQUE VALUES --

      std::map<value_type, size_type> unique_values;
      std::for_each(begin, end, [&unique_values, index = 0](auto item_value) mutable {
         auto value = static_cast<value_type>(item_value);

         if (unique_values.contains(value))
            return;

         unique_values.emplace(value, index++);
      });

      // -- DIRECT VALUES --

      if (unique_values.size() > (1 << CIndirectLimit)) {
         m_type = PaletteType::Direct;

         const auto data_size = static_cast<size_type>(end - begin);
         m_data.resize(data_size);

         auto at = begin;
         for (size_type i{0}; i < data_size; ++i) {
            m_data.set(i, *at);
            ++at;
         }

         return;
      }

      m_palette.resize(unique_values.size());
      for (auto pair : unique_values) {
         m_palette[pair.second] = pair.first;
      }

      // -- SINGLE VALUE --

      if (m_palette.size() == 1) {
         m_type = PaletteType::SingleValue;
         m_size = end - begin;
         return;
      }

      // -- PALETTED VALUES --
      m_type = PaletteType::Indirect;

      const auto data_size = static_cast<size_type>(end - begin);
      m_data.resize(data_size);

      auto at = begin;
      for (size_type i{0}; i < data_size; ++i) {
         m_data.set(i, static_cast<index_type>(unique_values[*at]));
         ++at;
      }
   }

   [[nodiscard]] value_type at_internal(size_type index) const
   {
      switch (m_type) {
      case PaletteType::SingleValue: {
         return m_palette[0];
      }
      case PaletteType::Indirect: {
         auto palette_index = static_cast<size_type>(m_data.at(index));
         assert(palette_index < m_palette.size());
         return m_palette.at(palette_index);
      }
      case PaletteType::Direct: {
         return m_data.at(index);
      }
      default: throw std::runtime_error("paletted-vector: no such item");
      }
   }

   [[nodiscard]] value_type at(size_type index) const
   {
      std::shared_lock lk{m_mutex};
      return this->at_internal(index);
   }

   [[nodiscard]] constexpr value_type operator[](size_type index) const
   {
      return at(index);
   }

   void set(size_type index, const value_type &value)
   {
      std::unique_lock lk{m_mutex};

      switch (m_type) {
      case PaletteType::Empty: {
         m_size = 1;
         m_type = PaletteType::SingleValue;
         m_palette.push_back(value);
         break;
      }
      case PaletteType::SingleValue: {
         m_size                  = std::max(m_size, index + 1);
         const auto single_value = m_palette[0];
         if (value != single_value) {
            if constexpr (CIndirectLimit <= 4) {
               // straight to direct
               m_palette.clear();
               m_type = PaletteType::Direct;
               m_data.resize(m_size);
               for (size_type i{}; i < m_data.size(); ++i) {
                  if (i == index) {
                     m_data.set(i, value);
                  } else {
                     m_data.set(i, single_value);
                  }
               }
            } else {
               m_palette.push_back(value);
               m_type = PaletteType::Indirect;
               m_data.resize(m_size);
               for (size_type i{}; i < m_data.size(); ++i) {
                  if (i == index) {
                     m_data.set(i, 1);
                  } else {
                     m_data.set(i, 0);
                  }
               }
            }
         }
         break;
      }
      case PaletteType::Indirect: {
         auto palette_index = std::find(m_palette.begin(), m_palette.end(), value);
         if (palette_index == m_palette.end()) {
            if ((m_palette.size() + 1) > (1 << CIndirectLimit)) {
               for (size_type i{}; i < m_data.size(); ++i) {
                  if (index == i) {
                     m_data.set(i, value);
                  } else {
                     m_data.set(i, this->at_internal(i));
                  }
               }
               m_palette.clear();
               m_type = PaletteType::Direct;
               m_data.set(index, value);
            } else {
               m_palette.push_back(value);
               m_data.set(index, static_cast<index_type>(m_palette.size() - 1ul));
            }
            return;
         }
         m_data.set(index, static_cast<index_type>(palette_index - m_palette.begin()));
         break;
      }
      case PaletteType::Direct: {
         m_data.set(index, value);
         break;
      }
      }
   }

   static PalettedVector from_net(const net::PalettedContainer &container, std::size_t size)
   {
      PalettedVector result;
      if (container.single_value_data.has_value()) {
         result.m_type = PaletteType::SingleValue;
         result.m_palette.push_back(container.single_value_data->value);
         result.m_size = size;
      }
      if (container.indirect_data.has_value()) {
         result.m_type = PaletteType::Indirect;

         result.m_palette.resize(container.indirect_data->palette.size());
         std::copy(container.indirect_data->palette.begin(), container.indirect_data->palette.end(),
                   result.m_palette.begin());

         result.m_data =
                 TightVector::from_raw(container.bits_per_entry, size, container.indirect_data->data.begin(),
                                       container.indirect_data->data.end());
      }
      if (container.direct_data.has_value()) {
         result.m_type = PaletteType::Direct;
         result.m_data =
                 TightVector::from_raw(container.bits_per_entry, size, container.direct_data->data.begin(),
                                       container.direct_data->data.end());
      }
      return result;
   }

   [[nodiscard]] constexpr size_type size() const
   {
      return m_data.size();
   }

   constexpr Iterator begin()
   {
      return Iterator{*this, m_data.begin(), 0};
   }

   constexpr Iterator end()
   {
      return Iterator{*this, m_data.end(), m_size};
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

   [[nodiscard]] PaletteType type() const
   {
      return m_type;
   }

 private:
   TightVector m_data;
   std::vector<value_type> m_palette;
   PaletteType m_type{PaletteType::Empty};
   std::size_t m_size{};// used only for single value
   mutable std::shared_mutex m_mutex;
};

}// namespace minecpp::container