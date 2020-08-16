#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <functional>

namespace Game {

struct Section {
   uint8_t bits;
   int ref_count;
   std::vector<int> palette;
   std::vector<int64_t> data;
   std::vector<uint8_t> block_light;
   std::vector<uint8_t> sky_light;
};

class SectionBuilder {
   std::map<int, int> palette;
   std::array<int, 4096> content;
   int top_item = 0;
 public:
   SectionBuilder();

   void fill(std::function<int(short, short, short)> callback);
   Section build();
};

}