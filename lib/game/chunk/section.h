#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <functional>
#include <squeeze/vector.h>

namespace Game {

struct Section {
   int ref_count;
   std::vector<std::uint32_t> palette;
   Squeeze::Vector data;
   std::vector<std::uint8_t> block_light;
   std::vector<std::uint8_t> sky_light;
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