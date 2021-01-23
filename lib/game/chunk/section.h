#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <functional>
#include <squeeze/vector.h>
#include <squeeze/tiny.h>

namespace Game {

struct Section {
   int ref_count;
   std::vector<std::uint32_t> palette;
   Squeeze::Vector data;
   Squeeze::TinyVec<4> block_light;
   Squeeze::TinyVec<4> sky_light;
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