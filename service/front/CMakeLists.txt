add_executable(minecpp_front)

# Source subdirectory
add_subdirectory(src)

# Link Target
target_link_libraries(minecpp_front LINK_PUBLIC minecpp_utils minecpp_grpc minecpp_api_proto minecpp_service_engine_api minecpp_event minecpp_network minecpp_format minecpp_repository minecpp_chat yaml-cpp Boost::system grpc++ spdlog libmb)
