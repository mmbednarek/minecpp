include(api.cmake)
add_library(minecpp_api_proto ${proto_api_sources})
target_link_libraries(minecpp_api_proto LINK_PUBLIC grpc++ protobuf absl::base absl::synchronization)
