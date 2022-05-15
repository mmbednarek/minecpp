#include <fstream>
#include <iostream>
#include <minecpp/network/message/chunk.h>
#include <minecpp/region/file.h>
#include <minecpp/util/compression.h>

auto main(int argc, char *argv[]) -> int
{
   if (argc < 4) {
      std::cerr << "not enough arguments\n";
      return 1;
   }

   std::fstream stream;
   stream.open(argv[1]);
   if (!stream.is_open()) {
      std::cerr << "no such file or directory\n";
      return 1;
   }

   minecpp::region::RegionFile r(stream);

   uint32_t x = std::stoi(argv[2]);
   uint32_t z = std::stoi(argv[3]);
   auto data  = r.load_chunk(x, z).unwrap();

   std::istringstream ss(std::string((char *) data.data(), data.size()));
   minecpp::util::ZlibInputStream zlib_stream(ss);

   char buff[256];
   while (zlib_stream.read(buff, 256)) { std::cout.write(buff, 256); }

   //   minecpp::nbt::Reader cr(zlib_stream);
   //   cr.check_signature();
   //   cr.find_compound("Level");

   //   minecpp::game::Chunk chunk(cr);
   //   minecpp::chunk::NetChunk proto_chunk;
   //   chunk.as_proto(&proto_chunk);
   //
   //   minecpp::network::Message::Writer w;
   //   minecpp::network::Message::write_chunk(w, proto_chunk);
   //
   //   auto buff = w.buff();
   //   std::cout.write((char *)std::get<0>(buff), std::get<1>(buff));
}