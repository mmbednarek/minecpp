add_library(minecpp_net msg/reader.cpp msg/writer.cpp msg/clientbound.cpp)
target_link_libraries(minecpp_net PUBLIC Boost::system)
