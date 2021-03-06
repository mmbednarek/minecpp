#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <minecpp/squeezed/tiny.h>
#include <minecpp/squeezed/vector.h>
#include <vector>

namespace minecpp::game {

struct Section {
   int ref_count;
   std::vector<std::uint32_t> palette;
   minecpp::squeezed::Vector data;
   minecpp::squeezed::TinyVec<4> block_light;
   minecpp::squeezed::TinyVec<4> sky_light;
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