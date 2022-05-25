add_executable(minecpp_service_discovery)

# Public include headers
target_include_directories(minecpp_service_discovery PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(api)

target_link_libraries(
  minecpp_service_discovery
  minecpp_api_proto
  minecpp_service_discovery_api
  libmb
  spdlog
)

