project(minecpp_protonbt)

add_subdirectory(test)

add_executable(minecpp_protonbt main.cpp lex.yy.cc lexer.cpp token_reader.cpp ast.h parser.cpp parser.h generator.cpp generator.h structgen.cpp structgen.h)
target_link_libraries(minecpp_protonbt minecpp_nbt libmb fmt libmb_codegen Boost::program_options)