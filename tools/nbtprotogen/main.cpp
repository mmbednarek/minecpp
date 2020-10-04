#include "generator.h"
#include "lexer.h"
#include "parser.h"
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <mineutils/time.h>
#include <nbt/parser.h>

//#define TEST

#ifdef TEST
#include "test.h"
#endif

int main(int argc, char *argv[]) {
   if (argc != 4) {
      std::cerr << "invalid number of input params";
      return 1;
   }

   std::ifstream s(argv[1]);
   if (!s.is_open()) {
      std::cerr << "could not open file";
      return 1;
   }

   auto tkn_reader = Lex::lex(s);
   auto parser = Syntax::Parser(tkn_reader);
   auto nodes_res = parser.parse();
   if (!nodes_res.ok()) {
      std::cerr << nodes_res.msg() << '\n';
      return 2;
   }
   auto nodes = nodes_res.unwrap();
   auto structure = Semantics::Structure(nodes);

   std::string header_file(argv[2]);

#ifdef TEST
   proto::nbt::test::Foo f;
   f.value = "foo";
   f.stuff.emplace_back(std::vector<uint8_t>{1, 2});
   f.stuff.emplace_back(std::vector<uint8_t>{2});

   proto::nbt::test::Test t;
   t.x = 23;
   t.val = "hello";
   t.testval.emplace_back(45);
   t.testval.emplace_back(67);
   t.values.emplace_back(std::vector<proto::nbt::test::Foo>{f});
   t.values.emplace_back(std::vector<proto::nbt::test::Foo>{f, f});

   std::stringstream ss;

   t.serialize(ss);

   NBT::Parser p(ss);

   //   auto start = Utils::now_milis();
   //   for (int i = 0; i < 100000; ++i) {
   //      ss.seekg(0, std::ios::beg);
   //      auto compound = p.read_tag();
   //   }
   //
   //   start = Utils::now_milis();
   //   for (int i = 0; i < 100000; ++i) {
   //      ss.seekg(0, std::ios::beg);
   //      auto test = proto::nbt::test::Test::deserialize(ss);
   //   }

   proto::nbt::test::User user;
   user.name = "Adam";
   user.surname = "Smith";

   std::ofstream ss2("user.bin");
   user.serialize(ss2);
   ss2.close();

//   std::ifstream ifile("user.bin");
//   auto user2 = proto::nbt::test::User::deserialize(ifile);
//   ifile.close();
//
//   fmt::print("name {}, surname: {}\n", user2.name, user2.surname);
#else
   std::ofstream out_header(header_file);
   Semantics::generate_header(structure, out_header);
   out_header.close();
   std::ofstream out_cpp(argv[3]);
   Semantics::generate_cpp(structure, out_cpp, header_file);
   out_cpp.close();
#endif
   return 0;
}