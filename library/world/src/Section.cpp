#include "Section.h"

#include "BlockState.h"
#include "Util.h"

#include "minecpp/util/Packed.h"

#include <spdlog/spdlog.h>
#include <utility>

namespace minecpp::world {

SectionBuilder::SectionBuilder() = default;

constexpr uint32_t coord_to_offset(int x, int y, int z)
{
   return (y & 15) * 16 * 16 + (z & 15) * 16 + (x & 15);
}

void SectionBuilder::fill(const std::function<int(short, short, short)> &callback)
{
   for (short y = 0; y < 16; ++y) {
      for (short z = 0; z < 16; ++z) {
         for (short x = 0; x < 16; ++x) {
            m_content[coord_to_offset(x, y, z)] = static_cast<game::BlockStateId>(callback(x, y, z));
         }
      }
   }
}

Section SectionBuilder::build()
{
   auto data = BlockContainer(m_content.begin(), m_content.end());

   Section section{0, std::move(data), {}};
   section.recalculate_reference_count();

   return section;
}

namespace {
std::array<game::BlockStateId, 4096> c_empty_section_data{};
}

Section::Section(int y) :
    m_reference_count{0},
    m_y{y},
    m_data{c_empty_section_data.begin(), c_empty_section_data.end()},
    m_block_light(std::make_unique<LightContainer>()),
    m_sky_light(std::make_unique<LightContainer>())
{
}

Section::Section(int ref_count, BlockContainer data, std::vector<game::LightSource> m_light_sources) :
    m_reference_count(ref_count),
    m_data(std::move(data)),
    m_light_sources(std::move(m_light_sources))
{
}

void Section::reset_light(game::LightType light_type)
{
   std::unique_lock lock{m_mutex};

   switch (light_type) {
   case game::LightType::Block: m_block_light.reset(); break;
   case game::LightType::Sky: m_sky_light.reset(); break;
   }
}

std::vector<game::LightSource> &Section::light_sources()
{
   //  TODO: MUTEX!!!
   return m_light_sources;
}

void Section::recalculate_reference_count()
{
   std::unique_lock lock{m_mutex};

   m_reference_count = 0;
   for (game::BlockStateId state : m_data) {
      BlockState block_state{state};

      auto res = repository::Block::the().get_by_id(block_state.block_id());
      if (!res.ok())
         return;

      //      auto &block = res.unwrap();
      //      if (block.stats().material != &game::block::Material::Air) {
      if (block_state.block_id() != 0) {
         ++m_reference_count;
      }
   }
}

Section::Section(const Section &section) :
    m_reference_count(section.reference_count()),
    m_data(section.data()),
    m_block_light(section.m_block_light == nullptr
                          ? nullptr
                          : std::make_unique<LightContainer>(*section.m_block_light)),
    m_sky_light(section.m_sky_light == nullptr ? nullptr
                                               : std::make_unique<LightContainer>(*section.m_sky_light)),
    m_light_sources(section.m_light_sources)
{
}

Section &Section::operator=(const Section &section)
{
   std::unique_lock lock{m_mutex};

   m_reference_count = section.reference_count();
   m_data            = section.data();
   if (section.m_block_light != nullptr)
      m_block_light = std::make_unique<LightContainer>(*section.m_block_light);
   if (section.m_sky_light != nullptr)
      m_sky_light = std::make_unique<LightContainer>(*section.m_sky_light);
   m_light_sources = section.m_light_sources;
   return *this;
}

void Section::set_block(game::BlockPosition position, game::BlockStateId id)
{
   std::unique_lock lock{m_mutex};

   auto source_block = get_block_internal(position);
   if (source_block == id)
      return;

   if (source_block == 0)
      ++m_reference_count;

   m_data.set(position.section_offset(), id);
}

const BlockContainer &Section::data() const
{
   return m_data;
}

BlockContainer &Section::data()
{
   return m_data;
}

int Section::reference_count() const
{
   std::shared_lock lock{m_mutex};
   return m_reference_count;
}

game::LightValue Section::get_light(game::LightType type, game::BlockPosition position) const
{
   std::shared_lock lock{m_mutex};
   const auto *light = light_data_internal(type);
   if (light == nullptr)
      return 0;
   return light->at(position.section_offset());
}

void Section::set_light(game::LightType type, game::BlockPosition position, game::LightValue value)
{
   std::unique_lock lock{m_mutex};
   auto *light = light_data_internal(type);
   if (light == nullptr) {
      fill_light_internal(type);
      light = light_data_internal(type);
   }
   light->set(position.section_offset(), value);
}

game::BlockStateId Section::get_block_internal(game::BlockPosition position) const
{
   return m_data.at(position.section_offset());
}

game::BlockStateId Section::get_block(game::BlockPosition position) const
{
   std::shared_lock lock{m_mutex};
   return get_block_internal(position);
}

void Section::fill_light(game::LightType type)
{
   std::shared_lock lock{m_mutex};
   fill_light_internal(type);
}

void Section::fill_light_internal(game::LightType type)
{
   switch (type) {
   case game::LightType::Block: m_block_light = std::make_unique<LightContainer>(); break;
   case game::LightType::Sky: m_sky_light = std::make_unique<LightContainer>(); break;
   }
}

LightContainer *Section::light_data(game::LightType type) const
{
   std::shared_lock lock{m_mutex};
   return light_data_internal(type);
}

LightContainer *Section::light_data_internal(game::LightType type) const
{
   switch (type) {
   case game::LightType::Block: return m_block_light.get();
   case game::LightType::Sky: return m_sky_light.get();
   }
   return nullptr;
}

Section Section::from_net(const net::Section &section, int y)
{
   auto data = BlockContainer::from_net(section.block_states, 4096);

   Section result(section.block_count, std::move(data), {});
   result.m_y = y;

   return result;
}

}// namespace minecpp::world
