#include <fmt/core.h>
#include <minecpp/stream/Server.h>
#include <spdlog/spdlog.h>
#include <thread>

using minecpp::stream::Peer;
using minecpp::stream::Server;

class ExampleServer
{
 public:
   ExampleServer() :
       m_server(7800)
   {
      m_server.on_connected.connect<&ExampleServer::on_connected>(this);
      m_server.on_received.connect<&ExampleServer::on_received_message>(this);
      m_server.on_disconnected.connect<&ExampleServer::on_disconnected>(this);
   }

   void send_routine(Peer *peer)
   {
      for (int i{0}; i < 1000; ++i) {
         this->send_message(*peer);
      }
   }

   void on_connected(Peer *peer)
   {
      spdlog::info("connected peer: {}", peer->hostname());
      m_send_thread.emplace(&ExampleServer::send_routine, this, peer);
   }

   void on_received_message(minecpp::stream::Peer *peer,
                            minecpp::container::BufferView message)
   {
      spdlog::info("received message from peer: {} (id={}), message: {}", peer->hostname(), peer->id(),
                   message.to_string());
   }

   void on_disconnected(minecpp::stream::Peer *peer, bool *try_reconnect)
   {
      spdlog::info("disconnected peer: {} (id={})", peer->hostname(), peer->id());

      m_message_count = 0;
      *try_reconnect  = false;
   }

   void send_message(minecpp::stream::Peer &peer)
   {
      spdlog::info("sending message to peer: {}", m_message_count);

      auto msg = fmt::format("number {}", m_message_count);
      peer.send_reliable_message(
              minecpp::container::BufferView(reinterpret_cast<std::uint8_t *>(msg.data()), msg.size()));

      ++m_message_count;
   }

   void loop()
   {
      while (m_is_running) {
         using namespace std::chrono_literals;

         m_server.tick();
         std::this_thread::sleep_for(30ms);
      }
   }

 private:
   std::optional<std::thread> m_send_thread{};
   minecpp::stream::Server m_server;
   bool m_is_running{true};
   int m_message_count{};
};

int main()
{
   ExampleServer server;
   server.loop();
}