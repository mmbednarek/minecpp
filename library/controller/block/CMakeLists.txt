SET(MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR ${MINECPP_CONTROLLER_INCLUDE_DIR}/block)

target_sources(minecpp_controller PRIVATE
        # Header files
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Default.h
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Door.h
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Fence.h
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Wood.h

        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Default.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Door.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Fence.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Wood.cpp
)
