add_library(minecpp_service_engine_api Api.cpp)
target_link_libraries(minecpp_service_engine_api PRIVATE minecpp_api_proto grpc++ libmb fmt spdlog  minecpp_game)
target_include_directories(minecpp_service_engine_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
