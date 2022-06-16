set(MINECPP_CONTROLLER_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/controller)

add_library(minecpp_controller
        # Header files
        ${MINECPP_CONTROLLER_INCLUDE_DIR}/BlockController.hpp
        ${MINECPP_CONTROLLER_INCLUDE_DIR}/BlockManager.h

        # Source files
        BlockManager.cpp
)

add_subdirectory("block")

target_link_libraries(minecpp_controller LINK_PUBLIC minecpp_game minecpp_repository)