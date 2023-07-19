#pragma once

#include "protocol/Handler.h"
#include "protocol/Protocol.h"

#include "minecpp/crypto/AESKey.h"
#include "minecpp/game/ChunkPosition.h"
#include "minecpp/network/message/Io.h"
#include "minecpp/util/StaticQueue.h"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/uuid/uuid.hpp>
#include <mb/int.h>
#include <memory>
#include <optional>
#include <queue>
#include <spdlog/spdlog.h>
#include <tuple>

namespace minecpp::service::front {

using boost::asio::ip::tcp;
class Server;

using ConnectionId = mb::size;

class Connection : public std::enable_shared_from_this<Connection>
{
   friend Server;

 public:
   using Ptr = std::shared_ptr<Connection>;

   explicit Connection(boost::asio::io_context &ctx, Server *server);
   ~Connection();

   void set_non_blocking();

   void async_write_then_read(container::Buffer buffer, protocol::Handler &handler);
   void async_write(container::Buffer buffer);
   void async_write_then_disconnect(container::Buffer buffer);

   void send(minecpp::network::message::Writer &w);
   void send_and_read(minecpp::network::message::Writer &w, protocol::Handler &h);
   void send_and_disconnect(minecpp::network::message::Writer &w);

   void async_read_varint(mb::u32 result, mb::u32 shift, const std::function<void(mb::u32)> &callback);
   void async_read_packet(protocol::Handler &handler);

   void set_encryption(container::BufferView key);
   [[nodiscard]] crypto::AESKey *encryption_key() const;

   Server *get_server();

   protocol::State state();
   void set_state(protocol::State s);
   void set_compression_threshold(std::size_t threshold);
   void set_service_id(boost::uuids::uuid id);
   boost::uuids::uuid service_id();

   void set_uuid(boost::uuids::uuid uuid);

   [[nodiscard]] const boost::uuids::uuid &uuid() const;
   [[nodiscard]] std::optional<ConnectionId> id() const;
   [[nodiscard]] mb::size compression_threshold() const;

   void push_chunk(int x, int z);
   minecpp::game::ChunkPosition pop_chunk();
   bool has_chunks();

   [[nodiscard]] tcp::socket &socket();

   mb::u8 *alloc_byte();
   void free_byte(mb::u8 *byte);

   template<typename TMessage>
   void send_message(const TMessage &msg)
   {
      minecpp::network::message::Writer writer;
      msg.serialize(writer);
      this->send(writer);
   }

   template<typename TMessage>
   void send_message_then_read(const TMessage &msg, protocol::Handler &handler)
   {
      minecpp::network::message::Writer writer;
      msg.serialize(writer);
      this->send_and_read(writer, handler);
   }

   template<typename TMessage>
   void send_message_then_disconnect(const TMessage &msg)
   {
      minecpp::network::message::Writer writer;
      msg.serialize(writer);
      this->send_and_disconnect(writer);
   }

   std::string user_name;
   std::atomic_int initial_chunk_count{};

 private:
   std::optional<ConnectionId> m_id;
   tcp::socket m_socket;

   boost::uuids::uuid m_player_id{};
   boost::uuids::uuid m_engine_service_id{};

   Server *m_server;
   protocol::State m_state;
   mb::size m_compression_threshold = 0;
   boost::object_pool<mb::u8> m_byte_pool;
   minecpp::util::StaticQueue<minecpp::game::ChunkPosition, 200> m_chunk_queue{};

   std::unique_ptr<crypto::AESKey> m_encryption_key{};
};

}// namespace minecpp::service::front
