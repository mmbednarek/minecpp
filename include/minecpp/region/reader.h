#pragma once
#include <cstdint>
#include <istream>
#include <memory>
#include <minecpp/error/result.h>
#include <vector>

namespace minecpp::region {

class Reader {
 public:
   explicit Reader(std::istream &s);

   result<std::vector<uint8_t>> load_chunk(int x, int z);

 private:
   std::istream &stream;
};

}// namespace minecpp::region
