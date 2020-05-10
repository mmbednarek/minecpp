add_library(minecpp_log log.cpp)
target_link_libraries(minecpp_log LINK_PUBLIC Boost::chrono)
target_include_directories(minecpp_log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
