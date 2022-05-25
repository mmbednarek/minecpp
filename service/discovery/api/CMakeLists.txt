add_library(minecpp_service_discovery_api api.cpp)

# Public include headers
target_include_directories(minecpp_service_discovery_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(minecpp_service_discovery_api minecpp_api_proto grpc++ libmb fmt)