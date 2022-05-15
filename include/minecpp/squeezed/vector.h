#pragma once
#include <array>
#include <functional>
#include <mb/int.h>
#include <utility>
#include <vector>

namespace minecpp::squeezed {

class Vector
{
   std::vector<mb::u64> m_data;
   mb::u8 m_bits;
   mb::size m_size;

 public:
   template<typename I>
   Vector(mb::u8 bits, std::vector<I> values) :
       m_bits(bits),
       m_size(values.size())
   {
      int per_pack = 64 / bits;
      int packs    = values.size() / per_pack;
      if (values.size() % per_pack != 0)
         ++packs;
      mb::u32 mask = (1u << bits) - 1u;

      m_data.resize(packs);
      std::generate(m_data.begin(), m_data.end(), [&values, per_pack, bits, mask, i = 0]() mutable {
         mb::u64 pack  = 0;
         mb::u32 shift = 0;
         for (int j = 1; j < per_pack; ++j) {
            pack |= static_cast<mb::u64>(values[i] & mask) << shift;
            ++i;
            if (i >= values.size()) {
               return pack;
            }
            shift += bits;
         }
         pack |= static_cast<mb::u64>(values[i] & mask) << shift;
         ++i;
         return pack;
      });
   }

   Vector();
   Vector(mb::u8 bits, mb::size size, std::vector<mb::u64> data);
   Vector(mb::u8 bits, mb::size size, std::vector<mb::i64> i_data);
   Vector(mb::u8 bits, mb::size size, std::function<mb::i32()> gen);

   [[nodiscard]] constexpr mb::size size() const { return m_size; }

   [[nodiscard]] constexpr mb::i8 bits() const { return m_bits; }

   [[nodiscard]] constexpr const std::vector<mb::u64> &raw() const { return m_data; }

   [[nodiscard]] mb::i32 at(mb::size i) const;
   [[nodiscard]] mb::i32 operator[](mb::size i) const;

   void set(mb::size i, mb::i32 value);
   void set_bits(mb::u8 new_bits);
   void inc_bits();

   struct Iterator
   {
      Vector &vec;
      mb::size pack;
      mb::u32 offset;

      Iterator &operator++();

      Iterator operator++(int);

      bool operator==(Iterator other) const;

      bool operator!=(Iterator other) const;

      [[nodiscard]] mb::i32 operator*() const;

      using difference_type   = Vector;
      using value_type        = Vector;
      using pointer           = const Vector *;
      using reference         = const Vector &;
      using iterator_category = std::forward_iterator_tag;
   };

   Iterator begin();
   Iterator end();
};

}// namespace minecpp::squeezed