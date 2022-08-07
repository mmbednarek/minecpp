#include <minecpp/container/TightVector.h>

namespace minecpp::container {

TightVector::TightVector(bits_type bits, size_type size, std::vector<std::uint64_t> data) :
    m_data(std::move(data)),
    m_bits(bits),
    m_size(size)
{
}

TightVector::TightVector() :
    m_bits(4),
    m_size(0)
{
}

TightVector::value_type TightVector::at(size_type i) const
{
   uint32_t parts     = 64 / m_bits;
   auto pack          = i / parts;
   uint32_t offset    = (i % parts) * m_bits;
   uint64_t mask      = ((1u << m_bits) - 1u);
   uint64_t full_pack = m_data[pack];
   return static_cast<value_type>((full_pack >> offset) & mask);
}

std::int32_t TightVector::operator[](std::size_t i) const
{
   return at(i);
}

void TightVector::set(std::size_t i, std::int32_t value)
{
   auto min_bits = min_bits_to_encode(value);
   if (min_bits > m_bits) {
      set_bits(min_bits);
   }

   uint32_t parts  = 64 / m_bits;
   auto pack       = i / parts;
   uint32_t offset = (i % parts) * m_bits;
   uint64_t mask   = ((1u << m_bits) - 1u);

   if (i >= m_size) {
      m_size = i + 1;
   }
   if (m_data.size() <= pack) {
      m_data.resize(pack + 1);
   }

   uint64_t full_pack = m_data[pack];
   full_pack &= ~(mask << offset);
   full_pack |= (static_cast<mb::u32>(value) & mask) << offset;
   m_data[pack] = full_pack;
}

TightVector::Iterator TightVector::begin() const
{
   return Iterator{.vec = *this, .pack = 0, .offset = 0};
}

TightVector::Iterator TightVector::end() const
{
   uint32_t parts = 64 / m_bits;
   return Iterator{.vec    = *this,
                   .pack   = m_size / parts,
                   .offset = static_cast<uint32_t>((m_size % parts) * m_bits)};
}

void TightVector::set_bits(std::uint8_t new_bits)
{
   mb::u32 per_pack = 64 / new_bits;
   mb::u32 mask     = (1u << new_bits) - 1u;

   auto new_packs = m_size / static_cast<mb::u32>(per_pack);
   if (m_size % per_pack != 0)
      new_packs++;

   std::vector<raw_value_type> resized(new_packs);
   std::generate(resized.begin(), resized.end(),
                 [iter = begin(), end = end(), per_pack, new_bits, mask]() mutable {
                    raw_value_type pack{0u};
                    mb::u32 shift{0u};
                    for (mb::u32 j{1}; j < per_pack; ++j) {
                       auto val = static_cast<mb::u32>(*iter);
                       pack |= static_cast<raw_value_type>(val & mask) << shift;
                       ++iter;
                       if (iter == end) {
                          return pack;
                       }
                       shift += new_bits;
                    }
                    auto val = static_cast<mb::u32>(*iter);
                    pack |= static_cast<raw_value_type>(val & mask) << shift;
                    ++iter;
                    return pack;
                 });

   m_data = resized;
   m_bits = new_bits;
}

void TightVector::increase_bits()
{
   set_bits(m_bits + 1);
}

void TightVector::push_back(TightVector::value_type value)
{
   set(size(), value);
}

void TightVector::resize(TightVector::size_type new_size)
{
   if(m_size >= new_size)
      return;

   uint32_t parts  = 64 / m_bits;
   auto pack_count = (new_size / parts) + 1;
   m_data.resize(pack_count);
   m_size = new_size;
}

TightVector::Iterator &TightVector::Iterator::operator++()
{
   offset += vec.m_bits;
   if (offset + vec.m_bits > 64) {
      offset = 0;
      pack++;
   }
   return *this;
}

TightVector::Iterator TightVector::Iterator::operator++(int)
{
   TightVector::Iterator copy{*this};
   this->operator++();
   return copy;
}

bool TightVector::Iterator::operator==(TightVector::Iterator other) const
{
   return pack == other.pack && offset == other.offset;
}

bool TightVector::Iterator::operator!=(TightVector::Iterator other) const
{
   return pack != other.pack || offset != other.offset;
}

TightVector::value_type TightVector::Iterator::operator*() const
{
   return static_cast<int32_t>((vec.m_data[pack] >> offset) & ((1u << vec.m_bits) - 1u));
}

}// namespace minecpp::container