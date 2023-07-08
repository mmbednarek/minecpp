#pragma once
#include <cstdint>
#include <minecpp/proto/service/storage/Storage.pb.h>

namespace minecpp::service::storage {

using ConnectionId = std::size_t;

class IResponder
{
 public:
   virtual ~IResponder() noexcept = default;

   virtual void send(ConnectionId id, const proto::service::storage::Response &response) = 0;
};

}// namespace minecpp::service::storage