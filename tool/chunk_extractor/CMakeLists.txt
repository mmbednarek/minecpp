project(minecpp_chunk_extractor)

add_executable(minecpp_chunk_extractor main.cpp)
target_link_libraries(minecpp_chunk_extractor LINK_PUBLIC minecpp_region minecpp_nbt minecpp_utils minecpp_game minecpp_net minecpp_proto grpc++)
