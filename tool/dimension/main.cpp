#include <sstream>
#include <minecpp/game/dimension.h>
#include <minecpp/nbt/writer.h>
#include <minecpp/nbt/parser.h>

int main() {
   using namespace minecpp;

   std::stringstream ss;
   nbt::Writer w(ss);

   game::write_dimension_codec(w);

   ss.seekg(0, std::ios::beg);
   nbt::Parser parser(ss);
   for (;;) {
      auto tag = parser.read_tag();
      if (tag.content.empty())
         break;
      std::cout << tag.content.to_string();
   }
}