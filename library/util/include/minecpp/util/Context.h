#pragma once

#include <cstdint>

namespace minecpp::util {

using ContextId = std::uint32_t;

class Context
{
 public:
   Context();

   [[nodiscard]] ContextId id() const;

 private:
   ContextId m_id;
};

}// namespace minecpp::util