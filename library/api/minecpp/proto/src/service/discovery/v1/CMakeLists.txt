set(MINECPP_API_MINECPP_PROTO_SERVICE_DISCOVERY_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_PROTO_DIR}/include/minecpp/proto/service/discovery/v1)
target_sources(minecpp_api_proto PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Discovery.grpc.pb.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/Discovery.pb.cc

        # Header files
        ${MINECPP_API_MINECPP_PROTO_SERVICE_DISCOVERY_V1_INCLUDE_DIR}/Discovery.grpc.pb.h
        ${MINECPP_API_MINECPP_PROTO_SERVICE_DISCOVERY_V1_INCLUDE_DIR}/Discovery.pb.h
)

