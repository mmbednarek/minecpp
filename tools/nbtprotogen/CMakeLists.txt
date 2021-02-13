project(minecpp_protonbt)

add_executable(minecpp_protonbt main.cpp lex.yy.cc lexer.cpp token_reader.cpp ast.h parser.cpp parser.h generator.cpp generator.h structgen.cpp structgen.h test.nbt.cpp)
target_link_libraries(minecpp_protonbt minecpp_error minecpp_nbt libmb fmt libmb_codegen Boost::program_options)