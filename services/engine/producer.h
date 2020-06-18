#pragma once
#include <cppkafka/cppkafka.h>
#include <string>

template <typename T> concept Message = requires(T msg, std::string s) {
   s = msg.GetTypeName();
   s = msg.SerializeAsString();
};

namespace Engine {

class Producer {
   cppkafka::Producer *producer;
   std::string topic = "minecpp";

 public:
   Producer(const std::string &kafka_hosts);

   void post(Message auto &msg) {
      cppkafka::MessageBuilder result_msg(topic);

      auto key_str = msg.GetTypeName().substr(15);
      auto payload_str = msg.SerializeAsString();
      cppkafka::Buffer key(key_str.data(), key_str.size());
      result_msg.key(key);

      cppkafka::Buffer payload(payload_str.data(), payload_str.size());
      result_msg.payload(payload);

      producer->produce(result_msg);
   }
};

} // namespace Engine
