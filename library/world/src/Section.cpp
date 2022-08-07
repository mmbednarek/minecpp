#include "minecpp/world/BlockState.h"
#include <minecpp/util/Packed.h>
#include <minecpp/world/Section.h>
#include <minecpp/world/Util.h>
#include <numeric>
#include <spdlog/spdlog.h>
#include <utility>

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
            content[coord_to_offset(x, y, z)] = static_cast<game::BlockStateId>(callback(x, y, z));
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

   int i = 0;

   auto data = container::PalettedVector<game::BlockStateId>(content.begin(), content.end());

   Section section{0, std::move(data), {}};
   section.recalculate_reference_count();

   return section;
}

Section::Section(int refCount, container::PalettedVector<game::BlockStateId> data,
                 std::vector<game::LightSource> mLightSources) :
    m_reference_count(refCount),
    m_data(std::move(data)),
    m_light_sources(std::move(mLightSources))
{
}

void Section::reset_light(game::LightType light_type)
{
   switch (light_type) {
   case game::LightType::Block: m_block_light.reset(); break;
   case game::LightType::Sky: m_sky_light.reset(); break;
   }
}

std::vector<game::LightSource> &Section::light_sources()
{
   return m_light_sources;
}

Section Section::from_proto(const proto::chunk::v1::Section &section)
{
   auto palette = container::PalettedVector<game::BlockStateId>::from_raw(
           static_cast<container::TightVector::bits_type>(section.bits()), 4096, section.data().begin(),
           section.data().end(), section.palette().begin(), section.palette().end());

   std::vector<game::LightSource> light_sources{};
   light_sources.resize(static_cast<mb::u64>(section.light_sources_size()));
   std::transform(section.light_sources().begin(), section.light_sources().end(), light_sources.begin(),
                  game::LightSource::from_proto);

   Section result{section.ref_count(), std::move(palette), std::move(light_sources)};

   result.m_block_light = std::make_unique<LightContainer>(
           LightContainer::from_raw(section.block_light().begin(), section.block_light().end()));
   result.m_sky_light = std::make_unique<LightContainer>(
           LightContainer::from_raw(section.sky_light().begin(), section.sky_light().end()));

   return result;
}

proto::chunk::v1::Section Section::to_proto() const
{
   proto::chunk::v1::Section result{};

   result.set_ref_count(m_reference_count);

   result.mutable_palette()->Resize(static_cast<int>(m_data.palette().size()), 0);
   std::copy(m_data.palette().begin(), m_data.palette().end(), result.mutable_palette()->begin());

   result.set_bits(m_data.indices().bits());
   if (not m_data.indices().raw().empty()) {
      result.mutable_data()->Resize(static_cast<int>(m_data.indices().raw().size()), 0);
      std::copy(m_data.indices().raw().begin(), m_data.indices().raw().end(), result.mutable_data()->begin());
   }

   result.mutable_block_light()->resize(LightContainer::raw_size);
   if (m_block_light != nullptr) {
      std::copy(m_block_light->raw().begin(), m_block_light->raw().end(), result.mutable_block_light()->begin());
   }

   result.mutable_sky_light()->resize(LightContainer::raw_size);
   if (m_sky_light != nullptr) {
      std::copy(m_sky_light->raw().begin(), m_sky_light->raw().end(), result.mutable_sky_light()->begin());
   }

   result.mutable_light_sources()->Reserve(static_cast<int>(m_light_sources.size()));
   std::transform(m_light_sources.begin(), m_light_sources.end(),
                  google::protobuf::RepeatedFieldBackInserter(result.mutable_light_sources()),
                  [](const game::LightSource &light) { return light.to_proto(); });

   return result;
}

void Section::recalculate_reference_count()
{
   m_reference_count = 0;
   for (game::BlockStateId state : m_data) {
      BlockState block_state{state};

      auto res = repository::Block::the().get_by_id(block_state.block_id());
      if (!res.ok())
         return;

      auto &block = res.unwrap();
      if (block.stats().material != &game::block::Material::Air) {
         ++m_reference_count;
      }
   }
}

Section::Section(const Section &section) :
    m_reference_count(section.reference_count()),
    m_data(section.data()),
    m_block_light(section.m_block_light == nullptr ? nullptr : std::make_unique<LightContainer>(*section.m_block_light)),
    m_sky_light(section.m_sky_light == nullptr ? nullptr : std::make_unique<LightContainer>(*section.m_sky_light)),
    m_light_sources(section.m_light_sources)
{
}

Section &Section::operator=(const Section &section)
{
   m_reference_count = section.reference_count();
   m_data            = section.data();
   if (section.m_block_light != nullptr)
      m_block_light     = std::make_unique<LightContainer>(*section.m_block_light);
   if (section.m_sky_light != nullptr)
      m_sky_light       = std::make_unique<LightContainer>(*section.m_sky_light);
   m_light_sources   = section.m_light_sources;
   return *this;
}

}// namespace minecpp::world
