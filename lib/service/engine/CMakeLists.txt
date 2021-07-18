add_library(minecpp_service_engine_api api.cpp)
target_link_libraries(minecpp_service_engine_api minecpp_api_proto grpc++ libmb fmt)
