# THIS FILE HAS BEEN GENERATED BY THE BUILD CONFIGURATION SYSTEM - DO NOT EDIT

set(MINECPP_COMMAND_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(minecpp_command_test)

# Public include headers
target_include_directories(minecpp_command_test
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/minecpp/command_test
)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_command_test
        LINK_PUBLIC
        GTest::gtest
        GTest::gtest_main
        minecpp_command
        minecpp_repository
)

add_test(NAME minecpp_command COMMAND minecpp_command_test)
