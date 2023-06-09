#pragma once
#include <cstdint>
#include <istream>
#include <memory>
#include <ostream>
#include <utility>

namespace minecpp::container {

class StreamBufferView : public std::streambuf
{
 public:
   template<typename TBuffer>
   explicit StreamBufferView(const TBuffer &buffer)
   {
      this->setg(reinterpret_cast<char *>(buffer.data()), reinterpret_cast<char *>(buffer.data()),
                 reinterpret_cast<char *>(buffer.data() + buffer.size()));
   }
};

template<typename TBuffer>
class InputStreamBufferView : public virtual StreamBufferView,
                              public std::istream
{
 public:
   explicit InputStreamBufferView(const TBuffer &buffer) :
       StreamBufferView(buffer),
       std::istream(static_cast<std::streambuf *>(this)),
       m_buffer(buffer.data(), buffer.size())
   {
   }

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextra"
#endif
   // Justification: warning occurs in libstdc++ code

   InputStreamBufferView(const InputStreamBufferView &other) :
       StreamBufferView(other.m_buffer),
       std::istream(static_cast<std::streambuf *>(this)),
       m_buffer(other.m_buffer.data(), other.m_buffer.size())
   {
   }

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

   InputStreamBufferView &operator=(const InputStreamBufferView &other)
   {
      m_buffer = {other.m_buffer.data(), other.m_buffer.size()};
      this->setg(reinterpret_cast<char *>(m_buffer.data()), reinterpret_cast<char *>(m_buffer.data()),
                 reinterpret_cast<char *>(m_buffer.data() + m_buffer.size()));
   }

 private:
   TBuffer m_buffer;
};

template<typename TByte>
class BasicBufferView
{
 public:
   BasicBufferView();
   BasicBufferView(TByte *data, std::size_t data_size);

   [[nodiscard]] constexpr TByte *data() const noexcept;
   [[nodiscard]] constexpr std::size_t size() const noexcept;

   void truncate(std::size_t new_size);
   void zero_memory();
   std::string to_string();
   void read_from(std::istream &stream);
   void write_to(std::ostream &stream);

   [[nodiscard]] InputStreamBufferView<BasicBufferView<TByte>> make_stream() const;

   static BasicBufferView from_string(std::string_view view);
   static BasicBufferView from_istream(std::istream &stream);

 private:
   std::size_t m_size{};
   TByte *m_data{};
};

template<typename TByte>
BasicBufferView<TByte>::BasicBufferView() :
    m_size{0},
    m_data{nullptr}
{
}

template<typename TByte>
BasicBufferView<TByte>::BasicBufferView(TByte *data, std::size_t data_size) :
    m_size{data_size},
    m_data{data}
{
}

template<typename TByte>
constexpr TByte *BasicBufferView<TByte>::data() const noexcept
{
   return m_data;
}

template<typename TByte>
constexpr std::size_t BasicBufferView<TByte>::size() const noexcept
{
   return m_size;
}

template<typename TByte>
void BasicBufferView<TByte>::truncate(std::size_t size)
{
   m_size = size;
}

template<typename TByte>
std::string BasicBufferView<TByte>::to_string()
{
   return {reinterpret_cast<char *>(m_data), reinterpret_cast<char *>(m_data + m_size)};
}

template<typename TByte>
void BasicBufferView<TByte>::zero_memory()
{
   std::fill(m_data, m_data + m_size, 0);
}

template<typename TByte>
BasicBufferView<TByte> BasicBufferView<TByte>::from_string(const std::string_view view)
{
   BasicBufferView<TByte> buff{view.size()};
   std::copy(view.begin(), view.end(), buff.m_data);
   return buff;
}

template<typename TByte>
void BasicBufferView<TByte>::read_from(std::istream &stream)
{
   stream.read(reinterpret_cast<char *>(m_data), static_cast<std::streamsize>(m_size));
}

template<typename TByte>
void BasicBufferView<TByte>::write_to(std::ostream &stream)
{
   stream.write(reinterpret_cast<char *>(m_data), static_cast<std::streamsize>(m_size));
}

template<typename TByte>
BasicBufferView<TByte> BasicBufferView<TByte>::from_istream(std::istream &stream)
{
   stream.seekg(0, std::ios::end);
   auto size = stream.tellg();
   BasicBufferView<TByte> buffer(static_cast<std::size_t>(size));
   stream.seekg(0, std::ios::beg);
   buffer.read_from(stream);
   return buffer;
}

template<typename TByte>
InputStreamBufferView<BasicBufferView<TByte>> BasicBufferView<TByte>::make_stream() const
{
   InputStreamBufferView<BasicBufferView<TByte>> stream(*this);
   return stream;
}

using BufferView = BasicBufferView<std::uint8_t>;

}// namespace minecpp::container