#include <fmt/core.h>
#include <fstream>
#include <minecpp/nbt/chunk/v1/Chunk.nbt.h>

int main(int argc, char **argv)
{
   if (argc < 2) {
      fmt::print(stderr, "not enough arguments");
      return 1;
   }
   std::ifstream f(argv[1]);
   if (!f.is_open()) {
      fmt::print(stderr, "could not open file {}", argv[1]);
      return 1;
   }
   auto chunk = minecpp::nbt::chunk::v1::Chunk::deserialize(f);

   fmt::print("chunk is at x: {}, z: {}", chunk.level.x_pos, chunk.level.z_pos);
   return 0;
}