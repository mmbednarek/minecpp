#ifndef MINECPP_GRPC_BIDI_H
#define MINECPP_GRPC_BIDI_H

namespace minecpp::grpc {

enum class EventType {
   Accept,
   Write,
   Read,
   Disconnect,
};

}

#endif//MINECPP_GRPC_BIDI_H
