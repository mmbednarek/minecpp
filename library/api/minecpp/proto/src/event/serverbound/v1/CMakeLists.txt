set(MINECPP_API_MINECPP_PROTO_EVENT_SERVERBOUND_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_PROTO_DIR}/include/minecpp/proto/event/serverbound/v1)
target_sources(minecpp_api_proto PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Serverbound.pb.cc

        # Header files
        ${MINECPP_API_MINECPP_PROTO_EVENT_SERVERBOUND_V1_INCLUDE_DIR}/Serverbound.pb.h
)

