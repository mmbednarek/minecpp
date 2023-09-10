#pragma once
#include "BasicBufferView.hpp"
#include <cstdint>
#include <cstring>
#include <istream>
#include <memory>
#include <ostream>
#include <utility>

namespace minecpp::container {

class StreamBuffer : public std::streambuf
{
 public:
   template<typename TBuffer>
   explicit StreamBuffer(const TBuffer &buffer)
   {
      this->setg(reinterpret_cast<char *>(buffer.data()), reinterpret_cast<char *>(buffer.data()),
                 reinterpret_cast<char *>(buffer.data() + buffer.size()));
   }
};

template<typename TBuffer>
class InputStreamBuffer : public virtual StreamBuffer,
                          public std::istream
{
 public:
   explicit InputStreamBuffer(const TBuffer &buffer) :
       StreamBuffer(buffer),
       std::istream(static_cast<std::streambuf *>(this)),
       m_buffer(buffer.data(), buffer.size())
   {
   }

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextra"
#endif
   // Justification: warning occurs in libstdc++ code

   InputStreamBuffer(const InputStreamBuffer &other) :
       StreamBuffer(other.m_buffer),
       std::istream(static_cast<std::streambuf *>(this)),
       m_buffer(other.m_buffer.data(), other.m_buffer.size())
   {
   }

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

   InputStreamBuffer &operator=(const InputStreamBuffer &other)
   {
      m_buffer = {other.m_buffer.data(), other.m_buffer.size()};
      this->setg(reinterpret_cast<char *>(m_buffer.data()), reinterpret_cast<char *>(m_buffer.data()),
                 reinterpret_cast<char *>(m_buffer.data() + m_buffer.size()));
   }

 private:
   typename TBuffer::View m_buffer;
};

template<typename TByte, typename TAllocator = std::allocator<TByte>>
class BasicBuffer
{
 public:
   using View = BasicBufferView<TByte>;

   BasicBuffer();
   explicit BasicBuffer(BasicBufferView<TByte> view);
   explicit BasicBuffer(std::size_t data_size, TAllocator &&allocator = std::allocator<TByte>());
   ~BasicBuffer();

   BasicBuffer(const BasicBuffer &other);
   BasicBuffer &operator=(const BasicBuffer &other);
   BasicBuffer(BasicBuffer &&other) noexcept;
   BasicBuffer &operator=(BasicBuffer &&other) noexcept;

   [[nodiscard]] constexpr TByte *data() const noexcept;
   [[nodiscard]] constexpr std::size_t size() const noexcept;

   void truncate(std::size_t new_size);
   void zero_memory();
   std::string to_string();
   void read_from(std::istream &stream);
   void write_to(std::ostream &stream);
   void append(View data);

   [[nodiscard]] InputStreamBuffer<BasicBuffer<TByte, TAllocator>> make_stream() const;

   static BasicBuffer from_string(std::string_view view);
   static BasicBuffer from_istream(std::istream &stream);

   BasicBufferView<TByte> as_view() const;

 private:
   TAllocator m_allocator;
   std::size_t m_size{};
   std::size_t m_allocated_size{};
   TByte *m_data{};
};

template<typename TByte, typename TAllocator>
void BasicBuffer<TByte, TAllocator>::append(BasicBuffer::View data)
{
   auto new_size   = m_size + data.size();
   auto *new_data = m_allocator.allocate(new_size);

   std::memcpy(new_data, m_data, sizeof(TByte) * m_size);
   std::memcpy(new_data + m_size, data.data(), sizeof(TByte) * data.size());

   m_allocator.deallocate(m_data, m_allocated_size);

   m_data           = new_data;
   m_size           = new_size;
   m_allocated_size = new_size;
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer(BasicBufferView<TByte> view) :
    BasicBuffer(view.size())
{
   std::copy(view.data(), view.data() + view.size(), m_data);
}

template<typename TByte, typename TAllocator>
BasicBufferView<TByte> BasicBuffer<TByte, TAllocator>::as_view() const
{
   return BasicBufferView<TByte>(m_data, m_size);
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer() :
    m_allocator{},
    m_size{0},
    m_allocated_size{0},
    m_data{nullptr}
{
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer(std::size_t data_size, TAllocator &&allocator) :
    m_allocator(std::forward<TAllocator>(allocator)),
    m_size{data_size},
    m_allocated_size{data_size},
    m_data{m_allocator.allocate(m_size)}
{
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::~BasicBuffer()
{
   if (m_data == nullptr)
      return;

   m_allocator.deallocate(m_data, m_allocated_size);
}

template<typename TByte, typename TAllocator>
constexpr TByte *BasicBuffer<TByte, TAllocator>::data() const noexcept
{
   return m_data;
}

template<typename TByte, typename TAllocator>
constexpr std::size_t BasicBuffer<TByte, TAllocator>::size() const noexcept
{
   return m_size;
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer(const BasicBuffer &other) :
    m_allocator(other.m_allocator),
    m_size(other.m_size),
    m_allocated_size(other.m_size),
    m_data(m_allocator.allocate(m_allocated_size))
{
   std::copy(other.data(), other.data() + other.size(), m_data);
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator> &BasicBuffer<TByte, TAllocator>::operator=(const BasicBuffer &other)
{
   if (m_data != nullptr)
      m_allocator.deallocate(m_data, m_size);

   m_size           = other.m_size;
   m_allocated_size = other.m_size;
   m_data           = m_allocator.allocate(m_allocated_size);

   std::copy(other.data(), other.data() + other.size(), m_data);
   return *this;
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer(BasicBuffer &&other) noexcept :
    m_allocator(other.m_allocator),
    m_size(std::exchange(other.m_size, 0ull)),
    m_allocated_size(std::exchange(other.m_allocated_size, 0ull)),
    m_data(std::exchange(other.m_data, nullptr))
{
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator> &BasicBuffer<TByte, TAllocator>::operator=(BasicBuffer &&other) noexcept
{
   if (m_data != nullptr)
      m_allocator.deallocate(m_data, m_size);

   m_allocator      = other.m_allocator;
   m_size           = std::exchange(other.m_size, 0);
   m_allocated_size = std::exchange(other.m_allocated_size, 0);
   m_data           = std::exchange(other.m_data, nullptr);
   return *this;
}

template<typename TByte, typename TAllocator>
void BasicBuffer<TByte, TAllocator>::truncate(std::size_t size)
{
   m_size = size;
}

template<typename TByte, typename TAllocator>
std::string BasicBuffer<TByte, TAllocator>::to_string()
{
   return {reinterpret_cast<char *>(m_data), reinterpret_cast<char *>(m_data + m_size)};
}

template<typename TByte, typename TAllocator>
void BasicBuffer<TByte, TAllocator>::zero_memory()
{
   std::fill(m_data, m_data + m_size, 0);
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator> BasicBuffer<TByte, TAllocator>::from_string(const std::string_view view)
{
   BasicBuffer<TByte, TAllocator> buff{view.size()};
   std::copy(view.begin(), view.end(), buff.m_data);
   return buff;
}

template<typename TByte, typename TAllocator>
void BasicBuffer<TByte, TAllocator>::read_from(std::istream &stream)
{
   stream.read(reinterpret_cast<char *>(m_data), static_cast<std::streamsize>(m_size));
}

template<typename TByte, typename TAllocator>
void BasicBuffer<TByte, TAllocator>::write_to(std::ostream &stream)
{
   stream.write(reinterpret_cast<char *>(m_data), static_cast<std::streamsize>(m_size));
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator> BasicBuffer<TByte, TAllocator>::from_istream(std::istream &stream)
{
   static constexpr auto buffer_size = 4096;

   BasicBuffer<TByte, TAllocator> result;
   TByte data_part[buffer_size];
   std::streamsize n;

   while (n = stream.readsome(reinterpret_cast<char *>(data_part), static_cast<std::streamsize>(buffer_size)),
          n != 0) {
      result.append(View{data_part, static_cast<std::size_t>(n)});
   }

   return result;
}

template<typename TByte, typename TAllocator>
InputStreamBuffer<BasicBuffer<TByte, TAllocator>> BasicBuffer<TByte, TAllocator>::make_stream() const
{
   return InputStreamBuffer<BasicBuffer<TByte, TAllocator>>(*this);
}

using Buffer = BasicBuffer<std::uint8_t>;

}// namespace minecpp::container