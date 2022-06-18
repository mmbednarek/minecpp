set(MINECPP_NETWORK_INCLUDE_DIR ${MINECPP_NETWORK_DIR}/include/minecpp/network)
target_sources(minecpp_network PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Chat.cpp

        # Header files
        ${MINECPP_NETWORK_INCLUDE_DIR}/Chat.h
)

# Subdirectories
add_subdirectory("message")

