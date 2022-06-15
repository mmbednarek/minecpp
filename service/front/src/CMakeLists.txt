target_sources(
        minecpp_front PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Connection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Server.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Service.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Service.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Ticks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Ticks.h
)

add_subdirectory(protocol)
