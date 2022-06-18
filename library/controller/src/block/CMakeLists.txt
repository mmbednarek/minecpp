set(MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR ${MINECPP_CONTROLLER_DIR}/include/minecpp/controller/block)
target_sources(minecpp_controller PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Default.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Door.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Fence.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Stairs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Wood.cpp

        # Header files
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Default.h
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Door.h
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Fence.h
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Stairs.h
        ${MINECPP_CONTROLLER_BLOCK_INCLUDE_DIR}/Wood.h
)

