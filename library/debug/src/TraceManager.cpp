#include "TraceManager.h"

#include <cassert>

namespace minecpp::debug {

void TraceManager::initialize()
{
   m_file_stream.open("trace.bin");
   assert(m_file_stream.is_open());
}

void TraceManager::write_trace(TraceObject<> &&object)
{
   std::unique_lock lk{m_mutex};
   m_buffer.push_back(std::move(object));
}

void TraceManager::flush()
{
   std::unique_lock lk{m_mutex};
   for (const auto &trace : m_buffer) {
      trace.serialize(m_file_stream);
   }
   m_buffer.clear();
   m_file_stream.flush();
}

TraceManager &TraceManager::the()
{
   static TraceManager manager;
   return manager;
}

}// namespace minecpp::debug
