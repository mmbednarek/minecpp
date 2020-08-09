#include <fstream>
#include <game/chunk/chunk.h>
#include <iostream>
#include <minenet/msg/chunk.h>
#include <mineutils/compression.h>
#include <region/reader.h>

auto main(int argc, char *argv[]) -> int {
   if (argc < 4) {
      std::cerr << "not enough arguments\n";
      return 1;
   }

   std::ifstream stream;
   stream.open(argv[1]);
   if (!stream.is_open()) {
      std::cerr << "no such file or directory\n";
      return 1;
   }

   Region::Reader r(stream);

   uint32_t x = std::stoi(argv[2]);
   uint32_t z = std::stoi(argv[3]);
   auto data = r.load_chunk(x, z);

   std::istringstream ss(std::string((char *)data.data(), data.size()));
   Utils::ZlibInputStream zlib_stream(ss);

   NBT::Reader cr(zlib_stream);
   cr.check_signature();
   cr.find_compound("Level");

   Game::Chunk chunk(cr);
   minecpp::chunk::NetChunk proto_chunk;
   chunk.as_proto(&proto_chunk);

   MineNet::Message::Writer w;
   MineNet::Message::write_chunk(w, proto_chunk);

   auto buff = w.buff();
   std::cout.write((char *)std::get<0>(buff), std::get<1>(buff));
}