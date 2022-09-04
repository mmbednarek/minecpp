#include <minecpp/grpc/server/Bidi.h>
#include <minecpp/proto/test/Test.grpc.pb.h>
#include <minecpp/proto/test/Test.pb.h>
#include <spdlog/spdlog.h>

#include <utility>

using minecpp::grpc::server::BidiServer;
using minecpp::grpc::server::Stream;
using minecpp::proto::test::TestMessage;
using minecpp::proto::test::TestService;

MINECPP_DECLARE_BIDI_SERVER(Server, TestService::AsyncService, StartStream, TestMessage, TestMessage);

using ServerStream = Stream<Server>;

class Connection {
 public:
   explicit Connection(ServerStream stream) :
       m_stream{std::move(stream)}
   {
      m_stream.bind_read_callback(this, &Connection::on_read);
   }

   void on_read(const TestMessage &msg)
   {
      spdlog::info("obtained message: {}", msg.value());

      if (m_index < 100) {
         TestMessage text_msg;
         text_msg.set_value(fmt::format("hello from the server {}", m_index));
         m_stream.write(text_msg);

         ++m_index;
      }
   }

 private:
   ServerStream m_stream;
   int m_index{0};
};

class Manager
{
 public:
   Manager() :
       m_server("127.0.0.1:8080", this, &Manager::on_connected, 8)
   {
   }

   void on_connected(ServerStream stream)
   {
      spdlog::info("received connection");

      TestMessage msg;
      msg.set_value("first hello from the server");
      stream.write(msg);
      m_connections.emplace_back(std::move(stream));
   };

   void wait() {
      m_server.accept();
      m_server.wait();
   }

 private:
   Server m_server;
   std::vector<Connection> m_connections;
};

int main()
{
   Manager manager;
   manager.wait();
}