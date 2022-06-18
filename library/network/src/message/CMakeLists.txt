set(MINECPP_NETWORK_MESSAGE_INCLUDE_DIR ${MINECPP_NETWORK_DIR}/include/minecpp/network/message)
target_sources(minecpp_network PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Chunk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Clientbound.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Reader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Serverbound.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Writer.cpp

        # Header files
        ${MINECPP_NETWORK_MESSAGE_INCLUDE_DIR}/Chunk.h
        ${MINECPP_NETWORK_MESSAGE_INCLUDE_DIR}/Clientbound.h
        ${MINECPP_NETWORK_MESSAGE_INCLUDE_DIR}/File.h
        ${MINECPP_NETWORK_MESSAGE_INCLUDE_DIR}/Io.h
        ${MINECPP_NETWORK_MESSAGE_INCLUDE_DIR}/Message.h
        ${MINECPP_NETWORK_MESSAGE_INCLUDE_DIR}/Serverbound.h
        ${MINECPP_NETWORK_MESSAGE_INCLUDE_DIR}/Writer.h
)

