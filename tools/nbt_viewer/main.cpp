#include <fstream>
#include <iostream>
#include <mineutils/compression.h>
#include <nbt/parser.h>
#include <nbt/snbt.h>

auto main(int argc, char *argv[]) -> int {
   std::string filename;
   bool use_gzip = false;

   for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
         if (argv[i][1] == 'g') {
            use_gzip = true;
            continue;
         }
         if (argv[i][1] == 0) {
            continue;
         }

         std::cerr << "unknown flag -" << argv[i][1] << "\n";
         return 1;
      }
      filename = argv[i];
   }

   std::istream *stream;
   // freed by system :/

   if (!filename.empty()) {
      auto *f = new std::ifstream();
      f->open(filename);
      if (!f->is_open()) {
         delete f;
         std::cerr << "no such file or directory\n";
         return 2;
      }
      stream = f;
   } else {
      stream = &std::cin;
   }

   if (use_gzip) {
      stream = new Utils::GZipInputStream(*stream);
   }

   NBT::Parser parser(*stream);
   try {
      NBT::TagPtr tag;
      for (;;) {
         tag = parser.read_tag();
         if (tag == nullptr)
            break;
         NBT::encode_snbt(std::cout, tag);
      }
   } catch (NBT::Exception &e) {
      std::cerr << "nbt error: " << e.what() << '\n';
      return 3;
   }
   return 0;
}
