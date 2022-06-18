set(MINECPP_COMMAND_CORE_INCLUDE_DIR ${MINECPP_COMMAND_DIR}/include/minecpp/command/core)
target_sources(minecpp_command PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Echo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Format.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Give.cpp

        # Header files
        ${MINECPP_COMMAND_CORE_INCLUDE_DIR}/Echo.h
        ${MINECPP_COMMAND_CORE_INCLUDE_DIR}/Format.h
        ${MINECPP_COMMAND_CORE_INCLUDE_DIR}/Give.h
)

