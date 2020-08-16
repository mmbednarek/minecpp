add_library(minecpp_utils reader.cpp vec.cpp format.cpp compression.cpp packed.cpp packed.h enum.h uuid.cpp uuid.h hex.cpp hex.h string.cpp string.h time.cpp time.h format.h)
target_link_libraries(minecpp_utils Boost::iostreams)
