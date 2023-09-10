#pragma once

#include "IResponder.h"

#include "minecpp/container/BasicBuffer.hpp"

namespace minecpp::service::storage {

class IHandler
{
 public:
   virtual ~IHandler() noexcept = default;

   virtual void handle_request(ConnectionId id, container::Buffer request) = 0;
};

}// namespace minecpp::service::storage