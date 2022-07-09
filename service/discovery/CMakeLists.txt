set(MINECPP_DISCOVERY_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(minecpp_discovery)

# Public include headers
target_include_directories(minecpp_discovery PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_discovery
        LINK_PUBLIC
        minecpp_service_discovery
        minecpp_api_proto
        minecpp_service_discovery_api
        libmb
        spdlog
)

add_subdirectory("api")
