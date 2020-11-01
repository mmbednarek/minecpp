project(minecpp_tests)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(minecpp_tests nbt_test.cpp utils_test.cpp packet_test.cpp position_test.cpp format_test.cpp random_test.cpp squeeze_test.cpp)
target_link_libraries(minecpp_tests LINK_PUBLIC minecpp_squeeze minecpp_utils minecpp_nbt minecpp_net minecpp_game minecpp_format minecpp_rand gtest gtest_main)
