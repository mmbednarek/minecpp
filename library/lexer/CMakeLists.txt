SET(MINECPP_LEXER_INCLUDE_DIR ${MINECPP_INCLUDE_DIR}/lexer)

add_library(minecpp_lexer
        Lexer.cpp
        ${MINECPP_LEXER_INCLUDE_DIR}/Lexer.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Token.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Reader.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Error.h
)