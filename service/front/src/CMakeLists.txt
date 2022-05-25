target_sources(
        minecpp_front PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/connection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/connection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/event_handler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/event_handler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/server.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/service.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ticks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ticks.h
)

add_subdirectory(protocol)
