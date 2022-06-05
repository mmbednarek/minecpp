add_executable(minecpp_engine)

# Public include headers
target_include_directories(minecpp_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
add_subdirectory(src)

# API files
add_subdirectory(api)

# Link targets
target_link_libraries(
  minecpp_engine LINK_PUBLIC
  minecpp_utils
  minecpp_player
  minecpp_game
  minecpp_api_proto
  minecpp_nbt
  minecpp_chat
  minecpp_format
  minecpp_net
  minecpp_repository
  minecpp_command
  minecpp_lexer
  grpc++
  Boost::system
  spdlog
  libmb
  gpr
)
