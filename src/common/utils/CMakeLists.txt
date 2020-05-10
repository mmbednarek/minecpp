add_library(minecpp_utils reader.cpp vec2.cpp format.cpp compression.cpp random.cpp membuf.cpp)
target_include_directories(minecpp_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(minecpp_utils Boost::iostreams)
