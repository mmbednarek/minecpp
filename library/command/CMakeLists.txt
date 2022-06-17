SET(MINECPP_COMMAND_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/command)

add_library(minecpp_command
        Command.cpp
        Parser.cpp
        RuntimeContext.cpp
        CommandManager.cpp
        StandardStream.cpp
        ${MINECPP_COMMAND_INCLUDE_DIR}/Object.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/Command.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/Parser.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/RuntimeContext.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/Result.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/CommandManager.h
        ${MINECPP_COMMAND_INCLUDE_DIR}/StandardStream.h
)

target_link_libraries(minecpp_command PRIVATE libmb fmt minecpp_lexer minecpp_format minecpp_game)

add_subdirectory(ast)
add_subdirectory(core)