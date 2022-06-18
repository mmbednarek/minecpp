set(MINECPP_API_MINECPP_PROTO_SERVICE_ENGINE_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_PROTO_DIR}/include/minecpp/proto/service/engine/v1)
target_sources(minecpp_api_proto PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.grpc.pb.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.pb.cc

        # Header files
        ${MINECPP_API_MINECPP_PROTO_SERVICE_ENGINE_V1_INCLUDE_DIR}/Engine.grpc.pb.h
        ${MINECPP_API_MINECPP_PROTO_SERVICE_ENGINE_V1_INCLUDE_DIR}/Engine.pb.h
)

