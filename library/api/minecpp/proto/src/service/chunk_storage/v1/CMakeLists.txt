set(MINECPP_API_MINECPP_PROTO_SERVICE_CHUNK_STORAGE_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_PROTO_DIR}/include/minecpp/proto/service/chunk_storage/v1)
target_sources(minecpp_api_proto PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/ChunkStorage.grpc.pb.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/ChunkStorage.pb.cc

        # Header files
        ${MINECPP_API_MINECPP_PROTO_SERVICE_CHUNK_STORAGE_V1_INCLUDE_DIR}/ChunkStorage.grpc.pb.h
        ${MINECPP_API_MINECPP_PROTO_SERVICE_CHUNK_STORAGE_V1_INCLUDE_DIR}/ChunkStorage.pb.h
)

