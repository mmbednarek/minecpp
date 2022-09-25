#pragma once
#include "IHandler.h"
#include "IResponder.h"
#include <minecpp/grpc/server/Bidi.h>
#include <minecpp/proto/service/storage/v1/Storage.grpc.pb.h>

namespace minecpp::service::storage {

namespace storage_v1 = minecpp::proto::service::storage::v1;

MINECPP_DECLARE_BIDI_SERVER(StorageServer, storage_v1::StorageService::AsyncService, Join,
                            storage_v1::Response, storage_v1::Request)

using Stream = grpc::server::Stream<StorageServer>;

class Connection
{
 public:
   Connection(ConnectionId id, Stream stream, IHandler *handler);

   Connection(Connection &)                      = delete;
   Connection &operator=(Connection &)           = delete;
   Connection(Connection &&) noexcept            = delete;
   Connection &operator=(Connection &&) noexcept = delete;

   void send(const storage_v1::Response &response);

   void on_read(const storage_v1::Request &request);

 private:
   ConnectionId m_id;
   Stream m_stream;
   IHandler *m_handler;
};

class Server : public IResponder
{
 public:
   explicit Server(const std::string &bind_address);

   void on_connection(Stream stream);
   void send(ConnectionId id, const storage_v1::Response &response) override;
   void set_handler(IHandler *handler);

   void wait();

 private:
   StorageServer m_server;
   std::mutex m_mutex;
   std::map<ConnectionId, std::unique_ptr<Connection>> m_connections;
   ConnectionId m_top_connection_id{};
   IHandler *m_handler{};
};

}// namespace minecpp::service::storage