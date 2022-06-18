set(MINECPP_API_MINECPP_PROTO_PLAYER_V1_INCLUDE_DIR ${MINECPP_API_MINECPP_PROTO_DIR}/include/minecpp/proto/player/v1)
target_sources(minecpp_api_proto PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Id.pb.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/Player.pb.cc

        # Header files
        ${MINECPP_API_MINECPP_PROTO_PLAYER_V1_INCLUDE_DIR}/Id.pb.h
        ${MINECPP_API_MINECPP_PROTO_PLAYER_V1_INCLUDE_DIR}/Player.pb.h
)

