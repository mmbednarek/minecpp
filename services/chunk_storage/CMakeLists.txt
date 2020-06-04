project(minecpp_chunk_storage)

add_executable(minecpp_chunk_storage service.cpp main.cpp )
target_link_libraries(minecpp_chunk_storage LINK_PUBLIC minecpp_utils minecpp_game minecpp_net minecpp_region minecpp_proto grpc++)
