add_library(minecpp_region File.cpp)
target_link_libraries(minecpp_region PUBLIC Boost::iostreams libmb fmt)
