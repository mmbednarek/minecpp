#include <minecpp/service/storage/Storage.h>

namespace minecpp::service::storage {

void StorageClient::subscribe_chunk(game::ChunkPosition position)
{
   proto::service::storage::v1::Request request;
   *request.mutable_chunk_subscription()->mutable_position() = position.to_proto();

   await_connection();
   {
      std::shared_lock lock{m_streams_mutex};
      m_streams.front()->send(request);
   }
}

void StorageClient::push_chunk(const world::Chunk &chunk)
{
   proto::service::storage::v1::Request request;
   *request.mutable_chunk_data()->mutable_chunk_data() = chunk.to_proto();

   await_connection();

   {
      std::shared_lock lock{m_streams_mutex};
      m_streams.front()->send(request);
   }
}

void StorageClient::on_connected(RawStream stream)
{
   // Send client ID information
   proto::service::storage::v1::Request request;
   request.mutable_set_client_id()->mutable_client_id()->set_value(m_client_id);
   stream.write(request);

   // Add stream to stream list
   std::unique_lock lock{m_streams_mutex};
   m_streams.push_back(std::make_unique<Stream>(m_handler, std::move(stream)));
   m_connection_cond.notify_one();
}

Stream::Stream(IResponseHandler *handler, RawStream stream) :
    m_handler(handler),
    m_stream(std::move(stream))
{
   m_stream.bind_read_callback(this, &Stream::on_read);
}

void Stream::send(const Request &req)
{
   m_stream.write(req);
}

void Stream::on_read(const Response &response)
{
   if (m_handler == nullptr)
      return;

   switch (response.message_case()) {
   case Response::kChunkData: m_handler->handle_chunk_data(response.chunk_data()); break;
   default: break;
   }
}

StorageClient::StorageClient(ClientId client_id, IResponseHandler *handler,
                             const std::vector<std::string> &addresses) :
    m_client_id(client_id),
    m_handler(handler),
    m_manager(&StorageService::Stub::AsyncJoin, addresses, this, &StorageClient::on_connected, 8)
{
}

void StorageClient::wait()
{
   m_manager.wait();
}

void StorageClient::await_connection()
{
   {
      std::shared_lock lock{m_streams_mutex};
      if (not m_streams.empty())
         // There's already a connection available
         return;
   }

   std::unique_lock lock{m_cond_mutex};
   m_connection_cond.wait(lock);
}

}// namespace minecpp::service::storage