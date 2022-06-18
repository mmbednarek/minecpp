add_executable(minecpp_chunk_storage)

# Source files subdirectory
add_subdirectory(src)

# Linking
target_link_libraries(
  minecpp_chunk_storage LINK_PUBLIC
  minecpp_utils
  minecpp_game
  minecpp_net
  minecpp_region
  minecpp_api_proto
  minecpp_error
  minecpp_random
  minecpp_repository
  minecpp_world
  grpc++
  Boost::system
  spdlog
  libmb
)
