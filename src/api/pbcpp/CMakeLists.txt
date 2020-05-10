add_library(minecpp_proto engine.grpc.pb.cc engine.pb.cc)
target_include_directories(minecpp_proto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
