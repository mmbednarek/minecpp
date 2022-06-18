set(MINECPP_COMMAND_AST_INCLUDE_DIR ${MINECPP_COMMAND_DIR}/include/minecpp/command/ast)
target_sources(minecpp_command PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Command.cpp

        # Header files
        ${MINECPP_COMMAND_AST_INCLUDE_DIR}/Ast.h
)

