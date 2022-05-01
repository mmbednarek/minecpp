project(minecpp_engine)

add_executable(minecpp_engine main.cpp players.cpp entities.cpp event_manager.cpp event_manager.h dispatcher.cpp dispatcher.h world.cpp world.h event_handler.h event_handler.cpp api.cpp)
target_link_libraries(minecpp_engine LINK_PUBLIC minecpp_utils minecpp_player minecpp_game minecpp_api_proto minecpp_nbt minecpp_chat minecpp_format minecpp_net minecpp_repository grpc++ Boost::system spdlog libmb gpr)
