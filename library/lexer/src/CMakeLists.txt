# THIS FILE HAS BEEN GENERATED BY THE BUILD CONFIGURATION SYSTEM - DO NOT EDIT

set(MINECPP_LEXER_INCLUDE_DIR ${MINECPP_LEXER_DIR}/include/minecpp/lexer)
target_sources(minecpp_lexer
    # Source files
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/IStreamReader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.cpp

    # Header files
    PUBLIC
        ${MINECPP_LEXER_INCLUDE_DIR}/Core.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Error.h
        ${MINECPP_LEXER_INCLUDE_DIR}/IReader.h
        ${MINECPP_LEXER_INCLUDE_DIR}/IStreamReader.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Lexer.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Reader.h
        ${MINECPP_LEXER_INCLUDE_DIR}/TokenFeed.h
        ${MINECPP_LEXER_INCLUDE_DIR}/Token.h
)

