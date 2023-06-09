#pragma once

#include <array>

namespace minecpp::util {

enum class ThreadType : int
{
   TickThread   = 0,
   WorkerThread = 1,
};

void set_debug_thread_info(ThreadType type, std::size_t index);

}// namespace minecpp::util
