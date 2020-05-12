project(minecpp_front)
add_executable(minecpp_front main.cpp connection.cpp server.cpp ../common/packet/reader.cpp protocol/protocol.cpp protocol/handler.h ../common/packet/writer.cpp ../common/packet/writer.h protocol/status_handler.cpp protocol/status_handler.h protocol/login_handler.cpp protocol/login_handler.h players.cpp players.h protocol/play_handler.cpp protocol/play_handler.h protocol/play_client.cpp protocol/play_client.h service.cpp)
target_link_libraries(minecpp_front LINK_PUBLIC minecpp_utils minecpp_proto yaml-cpp Boost::system Boost::log grpc++)
