project(minecpp_recipes)
add_executable(minecpp_recipes main.cpp)
target_link_libraries(minecpp_recipes minecpp_net minecpp_game minecpp_repository Boost::program_options Boost::iostreams)