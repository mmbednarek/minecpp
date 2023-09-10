#include "ChunkSerializer.h"

#include "Chunk.h"
#include "Section.h"

#include "minecpp/math/Vector2.h"

namespace minecpp::world {

namespace {

struct RawLightData
{
   std::vector<std::uint64_t> &light_mask;
   std::vector<std::uint64_t> &reset_light_mask;
   std::vector<std::vector<std::uint8_t>> &data;
};

RawLightData raw_light_data_from_type(net::LightData &light_data, game::LightType light_type)
{
   if (light_type == game::LightType::Block) {
      return RawLightData{
              light_data.block_light_mask,
              light_data.empty_block_light_mask,
              light_data.block_light,
      };
   }

   return RawLightData{
           light_data.sky_light_mask,
           light_data.empty_sky_light_mask,
           light_data.sky_light,
   };
}

}// namespace

ChunkSerializer::ChunkSerializer(Chunk &chunk) :
    m_chunk{chunk}
{
}

void ChunkSerializer::write_chunk(net::Chunk &out_chunk) const
{
   out_chunk.position = m_chunk.position().position();

   network::message::Writer data_writer;
   net::ChunkData chunk_data_struct;
   this->write_chunk_data(chunk_data_struct);
   chunk_data_struct.serialize(data_writer);

   auto view = data_writer.view();
   out_chunk.data.resize(view.size());
   std::copy(view.data(), view.data() + view.size(), out_chunk.data.begin());

   auto &motion_blocking = m_chunk.heightmap_of(game::HeightType::MotionBlocking);
   out_chunk.heightmaps.motion_blocking.resize(motion_blocking.raw().size());
   std::copy(motion_blocking.raw().begin(), motion_blocking.raw().end(),
             out_chunk.heightmaps.motion_blocking.begin());

   auto &world_surface = m_chunk.heightmap_of(game::HeightType::WorldSurface);
   out_chunk.heightmaps.world_surface.resize(world_surface.raw().size());
   std::copy(world_surface.raw().begin(), world_surface.raw().end(),
             out_chunk.heightmaps.world_surface.begin());

   this->write_light_data(out_chunk.light_data, game::LightType::Block, 0, 16);
   this->write_light_data(out_chunk.light_data, game::LightType::Sky, 0, 16);
}

void ChunkSerializer::write_light_data(net::LightData &light_data, game::LightType light_type,
                                       int min_section, int max_section) const
{
   std::uint64_t reset_light_bits{};
   std::uint64_t update_light_bits{};

   // Update masks
   for (auto const &[y, section] : m_chunk) {
      if (y < min_section)
         continue;
      if (y > max_section)
         break;

      const auto place = y + 1;
      if (section.light_data(light_type) == nullptr) {
         reset_light_bits |= 1u << place;
      } else {
         update_light_bits |= 1u << place;
      }
   }

   auto raw_data = raw_light_data_from_type(light_data, light_type);

   raw_data.reset_light_mask.emplace_back(reset_light_bits);
   raw_data.light_mask.emplace_back(update_light_bits);

   for (auto const &[y, section] : m_chunk) {
      if (y < min_section)
         continue;
      if (y > max_section)
         break;

      auto result = section.light_data(light_type);
      if (result == nullptr)
         continue;

      std::vector<std::uint8_t> data;
      data.resize(result->raw().size());
      std::copy(result->raw().begin(), result->raw().end(), data.begin());

      assert(data.size() == 2048);
      raw_data.data.emplace_back(std::move(data));
   }
}

void ChunkSerializer::write_update_light(net::play::cb::UpdateLight &update_light, game::LightType light_type,
                                         int min_section, int max_section) const
{
   update_light.position = m_chunk.position().position();
   this->write_light_data(update_light.light_data, light_type, min_section, max_section);
}

void ChunkSerializer::write_chunk_data(net::ChunkData &out_chunk_data) const
{
   static constexpr auto section_count = 16;
   out_chunk_data.sections.resize(section_count);
   for (auto at = m_chunk.bottom_section(); at < section_count; ++at) {
      auto section = m_chunk.section(at);
      if (section.has_failed()) {
         this->write_empty_section(out_chunk_data.sections[static_cast<std::size_t>(at)]);
      } else {
         section->recalculate_reference_count();
         this->write_section(out_chunk_data.sections[static_cast<std::size_t>(at)], *section);
      }
   }
}

void ChunkSerializer::write_section(net::Section &out_section, const Section &in_section) const
{
   out_section.block_count = static_cast<std::uint16_t>(in_section.reference_count());
   this->write_paletted_data(out_section.block_states, in_section.data());

   out_section.biomes.bits_per_entry    = 0;
   out_section.biomes.single_value_data = net::SingleValueData{1};
}

void ChunkSerializer::write_empty_section(net::Section &out_section) const
{
   out_section.block_count = 0;
   this->write_empty_section(out_section.block_states);
   out_section.biomes.bits_per_entry    = 0;
   out_section.biomes.single_value_data = net::SingleValueData{0};
}

void ChunkSerializer::write_paletted_data(net::PalettedContainer &out_paletted_data,
                                          const BlockContainer &in_vector) const
{
   switch (in_vector.type()) {
   case container::PaletteType::Empty: {
      this->write_empty_section(out_paletted_data);
      break;
   }
   case container::PaletteType::SingleValue: {
      out_paletted_data.bits_per_entry = 0;
      out_paletted_data.single_value_data =
              net::SingleValueData{static_cast<std::int32_t>(in_vector.palette().at(0))};
      break;
   }
   case container::PaletteType::Indirect: {
      out_paletted_data.bits_per_entry = in_vector.indices().bits();

      net::PalettedData data;

      data.palette.resize(in_vector.palette().size());
      std::copy(in_vector.palette().begin(), in_vector.palette().end(), data.palette.begin());

      if (not in_vector.indices().raw().empty()) {
         data.data.resize(in_vector.indices().raw().size());
         std::copy(in_vector.indices().raw().begin(), in_vector.indices().raw().end(), data.data.begin());
      }
      out_paletted_data.indirect_data = std::move(data);
      break;
   }
   case container::PaletteType::Direct: {
      out_paletted_data.bits_per_entry = in_vector.indices().bits();

      net::DirectData data;

      if (not in_vector.indices().raw().empty()) {
         data.data.resize(in_vector.indices().raw().size());
         std::copy(in_vector.indices().raw().begin(), in_vector.indices().raw().end(), data.data.begin());
      }
      out_paletted_data.direct_data = std::move(data);
      break;
   }
   }
}

void ChunkSerializer::write_empty_section(net::PalettedContainer &out_paletted_data) const
{
   out_paletted_data.bits_per_entry    = 0;
   out_paletted_data.single_value_data = net::SingleValueData{0};
}


}// namespace minecpp::world
