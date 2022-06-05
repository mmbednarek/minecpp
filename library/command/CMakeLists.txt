SET(MINECPP_COMMAND_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/command)

add_library(minecpp_command
        command.cpp
        parser.cpp
        runtime_context.cpp
        command_manager.cpp
        standard_stream.cpp
        ${MINECPP_COMMAND_INCLUDE_DIR}/object.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/command.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/parser.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/runtime_context.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/result.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/command_manager.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/standard_stream.h
)

target_link_libraries(minecpp_command PRIVATE libmb fmt minecpp_lexer minecpp_format)

add_subdirectory(ast)
add_subdirectory(core)