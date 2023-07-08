#pragma once

#include "IResponder.h"

#include "minecpp/proto/service/storage/Storage.pb.h"

namespace minecpp::service::storage {

class IHandler
{
 public:
   virtual ~IHandler() noexcept = default;

   virtual void handle_request(ConnectionId id, proto::service::storage::Request request) = 0;
};

}// namespace minecpp::service::storage