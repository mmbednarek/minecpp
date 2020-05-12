#include "../common/game/level/level.h"
#include "../common/utils/compression.h"
#include <fstream>
#include <iostream>

std::string load_path() {
   auto path = std::getenv("MINECPP_PATH");
   if (path) {
      return std::string(path);
   }

   auto home = std::string(std::getenv("HOME"));
   home.append("/.minecraft");
   return home;
}

auto main() -> int {
   auto save = std::getenv("SAVE");
   if (!save) {
      std::cerr << "SAVE variable required\n";
      return 1;
   }

   auto path = load_path();
   path.append("/saves/");
   path.append(save);
   path.append("/level.dat");

   std::cerr << "reading file: " << path << "\n";

   std::ifstream level_file;
   level_file.open(path);
   if (!level_file.is_open()) {
      std::cerr << "could not open file " << path << "\n";
      return 2;
   }

   Utils::GZipInputStream gzip(level_file);
   Game::Level::Info level(gzip);

   level_file.close();
}
