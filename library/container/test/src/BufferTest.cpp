#include "minecpp/container/BasicBuffer.hpp"
#include "minecpp/container/BasicBufferView.hpp"

#include <gtest/gtest.h>
#include <sstream>

using minecpp::container::Buffer;

TEST(BufferTest, BasicAllocation)
{
   Buffer buffer(128);
   std::fill(buffer.data(), buffer.data() + 128, 10);
}

TEST(BufferTest, Stream)
{
   std::stringstream ss;
   ss << "Hello World!";

   auto buffer = Buffer::from_istream(ss);

   EXPECT_EQ(buffer.to_string(), "Hello World!");
}

TEST(BufferTest, StreamFromBufferStream)
{
   std::stringstream ss;
   ss << "Hello World!";

   auto buffer1 = Buffer::from_istream(ss);
   auto stream  = buffer1.make_stream();
   auto buffer2 = Buffer::from_istream(stream);

   EXPECT_EQ(buffer2.to_string(), "Hello World!");
}
