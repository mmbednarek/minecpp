set(MINECPP_GRPC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(minecpp_grpc INTERFACE)

# Public include headers
target_include_directories(minecpp_grpc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(minecpp_grpc
        INTERFACE
        minecpp_utils
)
