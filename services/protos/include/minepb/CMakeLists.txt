add_library(minecpp_proto engine.grpc.pb.cc engine.pb.cc chunk.pb.cc chunk_storage.grpc.pb.cc chunk_storage.pb.cc game.pb.cc player.pb.cc events.pb.cc)
target_link_libraries(minecpp_proto PUBLIC grpc++)
