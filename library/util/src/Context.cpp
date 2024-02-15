#include "Context.h"

#include <atomic>

namespace minecpp::util {

namespace {

ContextId next_context_id()
{
   static std::atomic<ContextId> context_id{0};
   return ++context_id;
}

}// namespace

Context::Context() :
    m_id{next_context_id()}
{
}

ContextId Context::id() const
{
   return m_id;
}

}// namespace minecpp::util
