# THIS FILE HAS BEEN GENERATED BY THE BUILD CONFIGURATION SYSTEM - DO NOT EDIT

set(MINECPP_UTIL_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(minecpp_utils_test)

# Public include headers
target_include_directories(minecpp_utils_test
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/minecpp/util_test
)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_utils_test
        LINK_PUBLIC
        GTest::gtest
        GTest::gtest_main
        minecpp_utils
)

add_test(NAME minecpp_utils COMMAND minecpp_utils_test)
