#pragma once
#include <cstdint>
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
   TBuffer m_buffer;
};

template<typename TByte, typename TAllocator = std::allocator<std::uint8_t>>
class BasicBuffer
{
 public:
   BasicBuffer();
   explicit BasicBuffer(std::size_t data_size, TAllocator &&allocator = std::allocator<TByte>());
   BasicBuffer(TByte *data, std::size_t data_size);
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
   void de_own();
   void read_from(std::istream &stream);
   void write_to(std::ostream &stream);

   [[nodiscard]] InputStreamBuffer<BasicBuffer<TByte, TAllocator>> make_stream() const;

   static BasicBuffer from_string(std::string_view view);
   static BasicBuffer from_istream(std::istream &stream);

 private:
   TAllocator m_allocator;
   std::size_t m_size{};
   std::size_t m_allocated_size{};
   TByte *m_data{};
   bool m_owning{};
};

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer() :
    m_allocator{},
    m_size{0},
    m_allocated_size{0},
    m_data{nullptr},
    m_owning{false}
{
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer(std::size_t data_size, TAllocator &&allocator) :
    m_allocator(std::forward<TAllocator>(allocator)),
    m_size{data_size},
    m_allocated_size{data_size},
    m_data{m_allocator.allocate(m_size)},
    m_owning{true}
{
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer(TByte *data, std::size_t data_size) :
    m_allocator{},
    m_size{data_size},
    m_allocated_size{data_size},
    m_data{data},
    m_owning{false}
{
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::~BasicBuffer()
{
   if (not m_owning)
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
    m_data(m_allocator.allocate(m_allocated_size)),
    m_owning(true)
{
   std::copy(other.data(), other.data() + other.size(), m_data);
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator> &BasicBuffer<TByte, TAllocator>::operator=(const BasicBuffer &other)
{
   if (m_owning) {
      m_allocator.deallocate(m_data, m_size);
   }

   m_size           = other.m_size;
   m_allocated_size = other.m_size;
   m_data           = m_allocator.allocate(m_allocated_size);
   m_owning         = true;

   std::copy(other.data(), other.data() + other.size(), m_data);

   return *this;
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator>::BasicBuffer(BasicBuffer &&other) noexcept :
    m_allocator(other.m_allocator),
    m_size(std::exchange(other.m_size, 0ull)),
    m_allocated_size(std::exchange(other.m_allocated_size, 0ull)),
    m_data(std::exchange(other.m_data, nullptr)),
    m_owning(std::exchange(other.m_owning, false))
{
}

template<typename TByte, typename TAllocator>
BasicBuffer<TByte, TAllocator> &BasicBuffer<TByte, TAllocator>::operator=(BasicBuffer &&other) noexcept
{
   m_allocator      = other.m_allocator;
   m_size           = std::exchange(other.m_size, 0);
   m_allocated_size = std::exchange(other.m_allocated_size, 0);
   m_data           = std::exchange(other.m_data, nullptr);
   m_owning         = std::exchange(other.m_owning, false);
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
void BasicBuffer<TByte, TAllocator>::de_own()
{
   m_owning = false;
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
   stream.seekg(0, std::ios::end);
   auto size = stream.tellg();
   BasicBuffer<TByte, TAllocator> buffer(static_cast<std::size_t>(size));
   stream.seekg(0, std::ios::beg);
   buffer.read_from(stream);
   return buffer;
}

template<typename TByte, typename TAllocator>
InputStreamBuffer<BasicBuffer<TByte, TAllocator>> BasicBuffer<TByte, TAllocator>::make_stream() const
{
   InputStreamBuffer<BasicBuffer<TByte, TAllocator>> stream(*this);
   return stream;
}

using Buffer = BasicBuffer<std::uint8_t>;

}// namespace minecpp::container