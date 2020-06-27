project(minecpp_engine)

add_executable(minecpp_engine main.cpp players.cpp entities.cpp service.cpp event_manager.cpp event_manager.h)
target_link_libraries(minecpp_engine LINK_PUBLIC minecpp_utils minecpp_game minecpp_proto minecpp_nbt minecpp_net grpc++ Boost::system spdlog)
