# THIS FILE HAS BEEN GENERATED BY THE BUILD CONFIGURATION SYSTEM - DO NOT EDIT

set(MINECPP_DEBUG_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(minecpp_debug_test)

# Public include headers
target_include_directories(minecpp_debug_test
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/minecpp/debug_test
)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_debug_test
        LINK_PUBLIC
        GTest::gtest
        GTest::gtest_main
        minecpp_debug
)

add_test(NAME minecpp_debug COMMAND minecpp_debug_test)
