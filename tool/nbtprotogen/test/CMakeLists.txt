project(minecpp_protonbt_test)

add_executable(minecpp_protonbt_test Test.cpp Test.nbt.cpp)
target_link_libraries(minecpp_protonbt_test minecpp_nbt libmb gtest gtest_main)