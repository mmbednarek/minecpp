add_library(minecpp_utils reader.cpp vec2.cpp format.cpp compression.cpp random.cpp)
target_link_libraries(minecpp_utils Boost::iostreams)
