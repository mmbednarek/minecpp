#include "minecpp/container/BasicBuffer.hpp"
#include "minecpp/container/BasicBufferView.hpp"

#include <gtest/gtest.h>

using minecpp::container::Buffer;

TEST(BufferTest, BasicAllocation) {
   Buffer buffer(128);
   std::fill(buffer.data(), buffer.data() + 128, 10);
}