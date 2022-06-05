SET(MINECPP_LEXER_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/lexer)

add_library(minecpp_lexer
        lexer.cpp
        ${MINECPP_LEXER_INCLUDE_DIR}/lexer.h
        ${MINECPP_LEXER_INCLUDE_DIR}/token.h
        ${MINECPP_LEXER_INCLUDE_DIR}/reader.h
        ${MINECPP_LEXER_INCLUDE_DIR}/error.h
)