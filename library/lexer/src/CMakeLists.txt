set(MINECPP_LEXER_INCLUDE_DIR ${MINECPP_LEXER_DIR}/include/minecpp/lexer)
target_sources(minecpp_lexer PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.cpp

        # Header files
        ${MINECPP_LEXER_INCLUDE_DIR}/Error.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Lexer.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Reader.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Token.h
)

