project(minecpp_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(minecpp_tests nbt_test.cpp utils_test.cpp packet_test.cpp)
target_link_libraries(minecpp_tests LINK_PUBLIC minecpp_utils minecpp_nbt minecpp_packet gtest gtest_main)
