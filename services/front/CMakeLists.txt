project(minecpp_front)
add_executable(minecpp_front main.cpp connection.cpp server.cpp ../../lib/minenet/msg/reader.cpp protocol/protocol.cpp protocol/handler.h ../../lib/minenet/msg/writer.cpp ../../lib/minenet/msg/writer.h protocol/status_handler.cpp protocol/status_handler.h protocol/login_handler.cpp protocol/login_handler.h players.cpp players.h protocol/play_handler.cpp protocol/play_handler.h service.cpp)
target_link_libraries(minecpp_front LINK_PUBLIC minecpp_utils minecpp_proto minecpp_net yaml-cpp Boost::system Boost::log grpc++)
