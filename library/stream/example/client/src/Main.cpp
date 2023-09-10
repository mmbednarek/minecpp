#include <minecpp/stream/Client.h>
#include <spdlog/spdlog.h>
#include <thread>

using minecpp::stream::Client;
using minecpp::stream::Peer;

class ExampleClient
{
 public:
   explicit ExampleClient(const minecpp::network::Endpoint &endpoint) :
       m_client(),
       m_peer(m_client.create_peer(endpoint))
   {
      m_client.on_connected.connect<&ExampleClient::on_connected>(this);
      m_client.on_received.connect<&ExampleClient::on_received_message>(this);
      m_client.on_disconnected.connect<&ExampleClient::on_disconnected>(this);
   }

   void send_routine(Peer *peer)
   {
      for (int i{0}; i < 1000; ++i) {
         this->send_message(*peer);
      }
   }

   void on_connected(Peer *peer)
   {
      spdlog::info("connected!");
      m_send_thread.emplace(&ExampleClient::send_routine, this, peer);
   }

   void on_received_message(Peer * /*peer*/, minecpp::container::BufferView message)
   {
      spdlog::info("received message: {}", message.to_string());
   }

   void on_disconnected(Peer * /*peer*/, bool *try_reconnect)
   {
      spdlog::info("disconnected");

      m_message_count = 0;
      *try_reconnect  = true;
   }

   void send_message(Peer &peer)
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

         m_client.tick();
         std::this_thread::sleep_for(300ms);
      }
   }

 private:
   std::optional<std::thread> m_send_thread{};
   minecpp::stream::Client m_client;
   std::shared_ptr<Peer> m_peer;
   bool m_is_running{true};
   int m_message_count{};
};

int main()
{
   auto endpoint = minecpp::network::Endpoint::from_host("localhost", 7800);
   if (endpoint.has_failed()) {
      return 1;
   }

   ExampleClient client(*endpoint);
   client.loop();
}
