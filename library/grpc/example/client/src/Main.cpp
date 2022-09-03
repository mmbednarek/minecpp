#include <minecpp/grpc/client/Bidi.h>
#include <minecpp/proto/test/Test.grpc.pb.h>
#include <minecpp/proto/test/Test.pb.h>
#include <spdlog/spdlog.h>

using minecpp::grpc::client::ConnectionManager;
using minecpp::grpc::client::Stream;
using minecpp::proto::test::TestMessage;
using minecpp::proto::test::TestService;

using Manager = ConnectionManager<minecpp::proto::test::TestService::Stub, TestMessage, TestMessage>;

using ClientStream = Stream<Manager>;

/*
 Test Routine

 1. Obtain message 1, 2, 3
 2. Write message 1, 2, 3

 */

class Connection
{
 public:
   explicit Connection(ClientStream stream) :
       m_stream{std::move(stream)}
   {
      m_stream.bind_read_callback(this, &Connection::on_read);
   }

   void on_read(const TestMessage &msg)
   {
      spdlog::info("obtained message: {}", msg.value());

      if (m_value < 100) {
         TestMessage text_msg;
         text_msg.set_value(fmt::format("hello from client {}", m_value));
         m_stream.write(text_msg);

         ++m_value;
      }
   }

 private:
   ClientStream m_stream;
   int m_value{0};
};

class ClientManager
{
 public:
   ClientManager() :
       m_manager{&TestService::Stub::AsyncStartStream,
                 {"127.0.0.1:8080"},
                 this,
                 &ClientManager::on_connected,
                 8}
   {
   }

   void on_connected(ClientStream stream)
   {
      spdlog::info("received connection");

      std::unique_lock lock{m_mutex};
      TestMessage msg;
      msg.set_value("first hello from client");
      stream.write(msg);
      m_connections.emplace_back(std::move(stream));
   }

   void wait()
   {
      m_manager.wait();
   }

 private:
   std::mutex m_mutex;
   std::vector<Connection> m_connections;
   Manager m_manager;
};

int main()
{
   ClientManager manager;
   manager.wait();
}