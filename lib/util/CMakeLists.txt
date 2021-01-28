add_library(minecpp_utils reader.cpp vec.cpp format.cpp compression.cpp packed.cpp uuid.cpp hex.cpp string.cpp time.cpp scriptw.cpp loop.cpp)
target_link_libraries(minecpp_utils Boost::iostreams fmt)