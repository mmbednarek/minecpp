#include "producer.h"

namespace Engine {

Producer::Producer(const std::string &kafka_hosts) {
   cppkafka::Configuration config = {{"metadata.broker.list", kafka_hosts} };
   producer = new cppkafka::Producer(config);
}

}
