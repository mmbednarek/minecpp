add_library(minecpp_service_engine_api Api.cpp)
target_link_libraries(minecpp_service_engine_api PRIVATE minecpp_api_proto minecpp_event minecpp_game minecpp_grpc grpc++ libmb fmt spdlog)
target_include_directories(minecpp_service_engine_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
