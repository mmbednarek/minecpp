#pragma once

#include "IResponder.h"
#include <minecpp/proto/service/storage/v1/Storage.pb.h>

namespace minecpp::service::storage {

class IHandler
{
 public:
   virtual ~IHandler() noexcept = default;

   virtual void handle_request(ConnectionId id, const proto::service::storage::v1::Request &request) = 0;
};

}// namespace minecpp::service::storage