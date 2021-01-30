#include <minecpp/game/chunk/section.h>
#include <minecpp/game/chunk/utils.h>
#include <minecpp/util/packed.h>
#include <numeric>

namespace minecpp::game {

SectionBuilder::SectionBuilder() = default;

constexpr uint32_t coord_to_offset(int x, int y, int z) { return (y & 15) * 16 * 16 + (z & 15) * 16 + (x & 15); }

void SectionBuilder::fill(std::function<int(short, short, short)> callback) {
   for (short y = 0; y < 16; ++y) {
      for (short z = 0; z < 16; ++z) {
         for (short x = 0; x < 16; ++x) {
            auto state = callback(x, y, z);

            auto iter = palette.find(state);
            if (iter != palette.end()) {
               content[coord_to_offset(x, y, z)] = iter->second;
               continue;
            }

            palette[state] = top_item;
            content[coord_to_offset(x, y, z)] = top_item;
            ++top_item;
         }
      }
   }
}

int pow2(int v) {
   int result = 1;
   for (int i = 0; i < v; i++) {
      result += 2;
   }
   return result;
}


Section SectionBuilder::build() {
   auto bits = 4;
   while (pow2(bits) < top_item)
      ++bits;

   int i = 0;
   auto data = minecpp::util::generate_packed(bits, 4096, [this, &i]() {
      return content[i++];
   });

   auto light = std::vector<uint8_t>(2048);
   std::fill(light.begin(), light.end(), 255);

   std::vector<std::uint32_t> out_palette(top_item);
   std::for_each(palette.begin(), palette.end(), [&out_palette](auto &item) {
      out_palette[item.second] = item.first;
   });

   int ref_count = game::calculate_ref_count(data, out_palette);

   return Section{
           .ref_count = ref_count,
           .palette = std::move(out_palette),
           .data{static_cast<uint8_t>(bits), 4096, data},
           .block_light{minecpp::squeezed::TinyVec<4>(light)},
           .sky_light{minecpp::squeezed::TinyVec<4>(std::move(light))},
   };
}

}// namespace minecpp::game
