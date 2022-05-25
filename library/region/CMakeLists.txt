add_library(minecpp_region file.cpp)
target_link_libraries(minecpp_region PUBLIC Boost::iostreams libmb fmt)
