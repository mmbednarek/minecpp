# THIS FILE HAS BEEN GENERATED BY THE BUILD CONFIGURATION SYSTEM - DO NOT EDIT

set(MINECPP_NBT_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(minecpp_nbt_test)

# Public include headers
target_include_directories(minecpp_nbt_test
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/minecpp/nbt_test
)

# Source subdirectory
add_subdirectory("src")

target_link_libraries(minecpp_nbt_test
        LINK_PUBLIC
        GTest::gtest
        GTest::gtest_main
        minecpp_nbt
)

add_test(NAME minecpp_nbt COMMAND minecpp_nbt_test)
