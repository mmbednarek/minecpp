#include <minecpp/util/Packed.h>
#include <minecpp/world/Section.h>
#include <minecpp/world/Util.h>
#include <numeric>
#include <utility>
#include <spdlog/spdlog.h>

namespace minecpp::world {

SectionBuilder::SectionBuilder() = default;

constexpr uint32_t coord_to_offset(int x, int y, int z)
{
   return (y & 15) * 16 * 16 + (z & 15) * 16 + (x & 15);
}

void SectionBuilder::fill(std::function<int(short, short, short)> callback)
{
   for (short y = 0; y < 16; ++y) {
      for (short z = 0; z < 16; ++z) {
         for (short x = 0; x < 16; ++x) {
            auto state = callback(x, y, z);

            auto iter = palette.find(state);
            if (iter != palette.end()) {
               content[coord_to_offset(x, y, z)] = iter->second;
               continue;
            }

            palette[state]                    = top_item;
            content[coord_to_offset(x, y, z)] = top_item;
            ++top_item;
         }
      }
   }
}

int pow2(int v)
{
   int result = 1;
   for (int i = 0; i < v; i++) {
      result += 2;
   }
   return result;
}

Section SectionBuilder::build()
{
   auto bits = 4;
   while (pow2(bits) < top_item) ++bits;

   int i     = 0;
   auto data = minecpp::util::generate_packed(bits, 4096, [this, &i]() { return content[i++]; });

   std::vector<std::uint32_t> out_palette(static_cast<mb::size>(top_item));
   std::for_each(palette.begin(), palette.end(),
                 [&out_palette](auto &item) { out_palette[item.second] = item.first; });

   int ref_count = calculate_ref_count(data, out_palette);

   minecpp::squeezed::TinyVec<4> sky_light(4096);
   for (mb::size n = 0; n < 4096; ++n) {
      sky_light.set(n, 0x0);
   }

   minecpp::squeezed::TinyVec<4> block_light(4096);
   for (mb::size n = 0; n < 4096; ++n) {
      block_light.set(n, 0x0);
   }

   return Section{
           ref_count,
           out_palette,
           {static_cast<uint8_t>(bits), 4096, data},
           {std::move(block_light)},
           {std::move(sky_light)},
           {}
   };
}

void Section::reset_light(game::LightType light_type)
{
   switch (light_type) {
   case game::LightType::Block: block_light.reset(); break;
   case game::LightType::Sky: sky_light.reset(); break;
   }
}

std::vector<game::LightSource> &Section::light_sources()
{
   return m_light_sources;
}

Section::Section(int refCount, std::vector<std::uint32_t> palette, const squeezed::Vector &data,
                 squeezed::TinyVec<4> blockLight, squeezed::TinyVec<4> skyLight,
                 std::vector<game::LightSource> mLightSources) :
    ref_count(refCount),
    palette(std::move(palette)),
    data(data),
    block_light(std::move(blockLight)),
    sky_light(std::move(skyLight)),
    m_light_sources(std::move(mLightSources))
{
}

Section Section::from_proto(const proto::chunk::v1::Section &section)
{
   std::vector<mb::u32> palette{};
   palette.resize(static_cast<mb::u64>(section.palette_size()));
   std::copy(section.palette().begin(), section.palette().end(), palette.begin());

   std::vector<mb::u64> data_longs{};
   data_longs.resize(static_cast<mb::u64>(section.data_size()));
   std::copy(section.data().begin(), section.data().end(), data_longs.begin());
   squeezed::Vector data{static_cast<mb::u8>(section.data_size() * 64 / 4096), 4096, std::move(data_longs)};

   std::vector<mb::u8> block_light_data{};
   block_light_data.resize(static_cast<mb::u64>(section.block_light().size()));
   std::copy(section.block_light().begin(), section.block_light().end(), block_light_data.begin());
   squeezed::TinyVec<4> block_light{std::move(block_light_data)};

   std::vector<mb::u8> sky_light_data{};
   sky_light_data.resize(static_cast<mb::u64>(section.sky_light().size()));
   std::copy(section.sky_light().begin(), section.sky_light().end(), sky_light_data.begin());
   squeezed::TinyVec<4> sky_light{std::move(sky_light_data)};

   std::vector<game::LightSource> light_sources{};
   light_sources.resize(static_cast<mb::u64>(section.light_sources_size()));
   std::transform(section.light_sources().begin(), section.light_sources().end(), light_sources.begin(), game::LightSource::from_proto);

   return {section.ref_count(), std::move(palette), data, std::move(block_light), std::move(sky_light), std::move(light_sources)};
}

proto::chunk::v1::Section Section::to_proto()
{
   proto::chunk::v1::Section result{};

   result.mutable_palette()->Resize(static_cast<int>(palette.size()), 0);
   std::copy(palette.begin(), palette.end(), result.mutable_palette()->begin());

   result.mutable_data()->Resize(static_cast<int>(data.size()), 0);
   std::copy(data.begin(), data.end(), result.mutable_data()->begin());

   result.mutable_block_light()->resize(block_light.raw().size());
   std::copy(block_light.raw().begin(), block_light.raw().end(), result.mutable_block_light()->begin());

   result.mutable_sky_light()->resize(sky_light.raw().size());
   std::copy(sky_light.raw().begin(), sky_light.raw().end(), result.mutable_sky_light()->begin());

   result.mutable_light_sources()->Reserve(static_cast<int>(data.size()));
   std::transform(m_light_sources.begin(), m_light_sources.end(), google::protobuf::RepeatedFieldBackInserter(result.mutable_light_sources()), [](const game::LightSource &light) {
      return light.to_proto();
   });

   return result;
}

}// namespace minecpp::world
