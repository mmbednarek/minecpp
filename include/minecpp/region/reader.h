#pragma once
#include <cstdint>
#include <istream>
#include <memory>
#include <minecpp/error/result.h>
#include <vector>

namespace Region {

class Reader {
 public:
   explicit Reader(std::istream &s);

   result<std::vector<uint8_t>> load_chunk(int x, int z);

 private:
   std::istream &stream;
};

}// namespace Region
