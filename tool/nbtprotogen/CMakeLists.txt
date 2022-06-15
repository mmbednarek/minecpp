project(minecpp_protonbt)

add_subdirectory(test)
add_subdirectory(benchmark)

add_executable(minecpp_protonbt Main.cpp Lex.yy.cc Lexer.cpp TokenReader.cpp Ast.h Parser.cpp Parser.h Generator.cpp Generator.h Structgen.cpp Structgen.h)
target_link_libraries(minecpp_protonbt minecpp_nbt libmb fmt libmb_codegen Boost::program_options)
