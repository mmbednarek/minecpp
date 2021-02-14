project(minecpp_protonbt_test)

add_executable(minecpp_protonbt_test test.cpp test.nbt.cpp)
target_link_libraries(minecpp_protonbt_test minecpp_nbt libmb gtest gtest_main)