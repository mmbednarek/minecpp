#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <minecpp/game/Game.h>
#include <minecpp/game/World.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <minecpp/squeezed/Tiny.h>
#include <minecpp/squeezed/Vector.h>
#include <vector>

namespace minecpp::world {

struct Section final : public game::ISection
{
   int ref_count{};
   std::vector<std::uint32_t> palette;
   squeezed::Vector data;
   squeezed::TinyVec<4> block_light;
   squeezed::TinyVec<4> sky_light;
   std::vector<game::LightSource> m_light_sources;

   Section() = default;

   Section(int refCount, std::vector<std::uint32_t> palette, squeezed::Vector data,
           squeezed::TinyVec<4> blockLight, squeezed::TinyVec<4> skyLight,
           std::vector<game::LightSource> mLightSources);

   std::vector<game::LightSource> &light_sources() override;
   void reset_light(game::LightType light_type) override;

   static Section from_proto(const proto::chunk::v1::Section& section);
   proto::chunk::v1::Section to_proto();
};

class SectionBuilder
{
   std::map<int, int> palette;
   std::array<int, 4096> content{};
   int top_item = 0;

 public:
   SectionBuilder();

   void fill(std::function<int(short, short, short)> callback);
   Section build();
};

}// namespace minecpp::world