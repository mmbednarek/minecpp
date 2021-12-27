project(minecpp_front)
add_executable(minecpp_front main.cpp connection.cpp server.cpp protocol/protocol.cpp protocol/handler.h protocol/status_handler.cpp protocol/status_handler.h protocol/login_handler.cpp protocol/login_handler.h protocol/play_handler.cpp protocol/play_handler.h service.cpp config.h config.cpp event_handler.cpp event_handler.h ticks.cpp ticks.h)
target_link_libraries(minecpp_front LINK_PUBLIC minecpp_utils minecpp_api_proto minecpp_service_engine_api minecpp_player minecpp_event minecpp_net yaml-cpp Boost::system grpc++ spdlog libmb)
