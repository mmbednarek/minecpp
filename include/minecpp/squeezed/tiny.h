#include <cstdint>
#include <utility>
#include <vector>

namespace minecpp::squeezed {

template<std::uint8_t bits>
class TinyVec {
   std::vector<std::uint8_t> m_data;

 public:
   TinyVec();
   explicit TinyVec(std::vector<std::uint8_t> data);
   explicit TinyVec(std::size_t size);

   [[nodiscard]] std::int8_t at(std::size_t i) const;
   [[nodiscard]] const std::vector<std::uint8_t> &raw() const;
   [[nodiscard]] std::size_t size() const;
   [[nodiscard]] bool empty() const;
   void set(std::size_t i, std::int8_t value);
};

template<std::uint8_t bits>
TinyVec<bits>::TinyVec() = default;

template<std::uint8_t bits>
TinyVec<bits>::TinyVec(std::vector<std::uint8_t> data) : m_data(std::move(data)) {}

template<std::uint8_t bits>
TinyVec<bits>::TinyVec(std::size_t size) : m_data(size *  bits / 8) {}

template<std::uint8_t bits>
std::int8_t TinyVec<bits>::at(std::size_t i) const {
   constexpr auto parts = 8 / bits;
   constexpr auto mask = ((1u << bits) - 1u);

   auto pack = i / parts;
   auto offset = (i % parts) * bits;
   auto full_pack = m_data[pack];

   return (full_pack >> offset) & mask;
}

template<std::uint8_t bits>
void TinyVec<bits>::set(std::size_t i, std::int8_t value) {
   constexpr auto parts = 8 / bits;
   constexpr auto mask = ((1u << bits) - 1u);

   auto pack = i / parts;
   auto offset = (i % parts) * bits;

   if (pack >= m_data.size()) {
      m_data.resize(pack + 1);
   }

   auto full_pack = m_data[pack];
   full_pack &= ~(mask << offset);
   full_pack |= (value & mask) << offset;
   m_data[pack] = full_pack;
}

template<std::uint8_t bits>
const std::vector<std::uint8_t> &TinyVec<bits>::raw() const {
   return m_data;
}

template<std::uint8_t bits>
std::size_t TinyVec<bits>::size() const {
   return 0;
}

template<std::uint8_t bits>
bool TinyVec<bits>::empty() const {
   return m_data.empty();
}

}// namespace minecpp::squeezed