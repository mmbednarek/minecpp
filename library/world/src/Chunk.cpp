#include "minecpp/repository/Block.h"
#include "minecpp/repository/State.h"
#include <minecpp/nbt/Parser.h>
#include <minecpp/util/Packed.h>
#include <minecpp/util/Time.h>
#include <minecpp/world/BlockState.h>
#include <minecpp/world/Chunk.h>
#include <minecpp/world/Util.h>
#include <stdexcept>
#include <vector>

namespace minecpp::world {

namespace nbt_chunk_v1 = minecpp::nbt::chunk::v1;

inline int expected_data_version = 2230;

Chunk::Chunk() = default;

Chunk::Chunk(int x, int z, std::array<short, 256> &height_map) :
    m_pos_x(x),
    m_pos_z(z),
    m_full(false)
{
   int i    = 0;
   auto arr = minecpp::util::generate_packed(9, 256, [&height_map, &i]() { return height_map[i++]; });

   std::copy(arr.begin(), arr.end(), m_hm_motion_blocking.begin());
   std::copy(arr.begin(), arr.end(), m_hm_world_surface.begin());

   std::fill(m_biomes.begin(), m_biomes.end(), 1);
}

void Chunk::as_proto(minecpp::proto::chunk::v1::Chunk *chunk)
{
   chunk->set_pos_x(m_pos_x);
   chunk->set_pos_z(m_pos_z);
   chunk->set_full(m_full);
   if (m_full) {
      *chunk->mutable_biomes() = {m_biomes.begin(), m_biomes.end()};
   }
   *chunk->mutable_hm_motion_blocking() = {m_hm_motion_blocking.begin(), m_hm_motion_blocking.end()};

   *chunk->mutable_hm_world_surface() = {m_hm_world_surface.begin(), m_hm_world_surface.end()};

   for (auto const &sec : m_sections) {
      auto *out_sec = chunk->add_sections();
      *out_sec      = sec.second.to_proto();
      out_sec->set_y(sec.first);
      //         out_sec->set_bits(sec.second.m_data.indices().bits());
      //         out_sec->set_ref_count(sec.second.m_reference_count);
      //         *out_sec->mutable_palette()     = {sec.second.m_data.palette().begin(), sec.second.m_data.palette().end()};
      //         *out_sec->mutable_data()        = {sec.second.m_data.indices().raw().begin(), sec.second.m_data.indices().raw().end()};
      //         *out_sec->mutable_block_light() = {sec.second.block_light.raw().begin(),
      //                                            sec.second.block_light.raw().end()};
      //         *out_sec->mutable_sky_light() = {sec.second.sky_light.raw().begin(), sec.second.sky_light.raw().end()};
   }
}

constexpr uint32_t coord_to_offset(int x, int y, int z)
{
   return (y & 15) * 16 * 16 + (z & 15) * 16 + (x & 15);
}

void Chunk::create_empty_section(int8_t sec)
{
   m_sections[sec] = Section{};
}

void Chunk::set_block(int x, int y, int z, game::BlockStateId state)
{
   auto sec  = static_cast<std::int8_t>(y / 16);
   auto iter = m_sections.find(sec);
   if (iter == m_sections.end()) {
      create_empty_section(sec);
      iter = m_sections.find(sec);
   }

   auto &section = iter->second;
   section.m_data.set(coord_to_offset(x, y, z), state);
   //   auto index    = std::find(section.palette.begin(), section.palette.end(), state);
   //   std::size_t value{};
   //   if (index == section.palette.end()) {
   //      value = section.palette.size();
   //      section.palette.emplace_back(state);
   //   } else {
   //      value = std::distance(section.palette.begin(), index);
   //   }
   //
   //   section.data.set(coord_to_offset(x, y, z), value);

   set_block_light(game::BlockPosition{x, y, z}, 0);
   set_sky_light(game::BlockPosition{x, y, z}, 0);
}

game::BlockStateId Chunk::get_block(int x, int y, int z)
{
   auto section_id = static_cast<int8_t>(y / 16);

   auto it_section = m_sections.find(section_id);
   if (it_section == m_sections.end())
      return 0;

   return it_section->second.m_data[coord_to_offset(x, y, z)];
   //   auto palette_index = static_cast<std::size_t>(it_section->second.data.at(coord_to_offset(x, y, z)));
   //   if (palette_index < 0 || palette_index >= it_section->second.palette.size())
   //      return 0;
   //
   //   return it_section->second.palette[palette_index];
}

mb::result<game::LightLevel> Chunk::get_block_light(game::BlockPosition position)
{
   auto section = section_from_y_level(position.y);
   if (section.has_failed()) {
      return std::move(section.err());
   }

   if (section->block_light.empty()) {
      return mb::error("this section has empty block light");
   }

   return static_cast<game::LightLevel>(section->block_light.at(position.offset_within_section()));
}

mb::result<game::LightLevel> Chunk::get_sky_light(game::BlockPosition position)
{
   auto section = section_from_y_level(position.y);
   if (section.has_failed()) {
      return std::move(section.err());
   }

   if (section->sky_light.empty()) {
      return mb::error("this section has empty sky light");
   }

   return static_cast<game::LightLevel>(section->sky_light.at(position.offset_within_section()));
}

mb::emptyres Chunk::set_block_light(game::BlockPosition position, game::LightLevel value)
{
   auto section = section_from_y_level(position.y);
   if (section.has_failed()) {
      return std::move(section.err());
   }

   if (section->block_light.empty()) {
      section->block_light = minecpp::squeezed::TinyVec<4>(4096);
   }

   section->block_light.set(static_cast<mb::size>(position.offset_within_section()),
                            static_cast<mb::i8>(value));
   return mb::ok;
}

mb::emptyres Chunk::set_sky_light(game::BlockPosition position, game::LightLevel value)
{
   auto section = section_from_y_level(position.y);
   if (section.has_failed()) {
      return std::move(section.err());
   }

   if (section->sky_light.empty()) {
      section->sky_light = minecpp::squeezed::TinyVec<4>(4096);
   }

   section->sky_light.set(static_cast<mb::size>(position.offset_within_section()),
                          static_cast<mb::i8>(value));
   return mb::ok;
}

bool Chunk::add_ref(uuid engine_id, game::PlayerId player_id)
{
   m_references.insert(player_id);

   if (!m_engine_lock.is_nil()) {
      if (m_engine_lock != engine_id) {
         return false;
      }
   }
   m_engine_lock = engine_id;
   return true;
}

void Chunk::free_ref(game::PlayerId player_id)
{
   if (m_references.find(player_id) == m_references.end()) {
      return;
   }
   m_references.erase(player_id);
   if (m_references.empty()) {
      m_engine_lock = {};
   }
}

uuid Chunk::get_lock() const
{
   return m_engine_lock;
}

int Chunk::height_at(int x, int z)
{
   return minecpp::util::get_packed(m_hm_world_surface, 9, 16 * (z & 15) + (x & 15));
}

void Chunk::put_section(int8_t level, Section sec)
{
   m_sections[level] = std::move(sec);
}

std::array<short, 256> Chunk::get_height_map()
{
   std::array<short, 256> result{};
   for (int z = 0; z < 16; ++z) {
      for (int x = 0; x < 16; ++x) {
         result[z * 16 + x] = height_at(x, z);
      }
   }
   return result;
}

game::ChunkPosition Chunk::pos() const
{
   return {m_pos_x, m_pos_z};
}

mb::result<std::unique_ptr<Chunk>> Chunk::from_nbt(nbt_chunk_v1::Chunk &chunk) noexcept
{
   auto out     = std::make_unique<Chunk>();
   out->m_full  = chunk.level.status == "full";
   out->m_pos_x = chunk.level.x_pos;
   out->m_pos_z = chunk.level.z_pos;
   std::copy(chunk.level.heightmaps.world_surface.begin(), chunk.level.heightmaps.world_surface.end(),
             out->m_hm_world_surface.begin());
   std::copy(chunk.level.heightmaps.motion_blocking.begin(), chunk.level.heightmaps.motion_blocking.end(),
             out->m_hm_motion_blocking.begin());
   //   std::copy(chunk.level.biomes.begin(), chunk.level.biomes.end(), out->biomes.begin());
   std::fill_n(out->m_biomes.begin(), 1024, 1);
   std::transform(
           chunk.level.sections.begin(), chunk.level.sections.end(),
           std::inserter(out->m_sections, out->m_sections.begin()), [](const nbt_chunk_v1::Section &sec) {
              Section out_sec;
              out_sec.sky_light   = minecpp::squeezed::TinyVec<4>(sec.sky_light);
              out_sec.block_light = minecpp::squeezed::TinyVec<4>(sec.block_light);

              std::vector<game::BlockStateId> palette;
              palette.resize(sec.palette.size());
              std::transform(sec.palette.begin(), sec.palette.end(), palette.begin(),
                             [](const nbt::chunk::v1::PaletteItem &item) -> game::BlockStateId {
                                auto block_id = repository::Block::the().find_id_by_tag(item.name);
                                if (block_id.has_failed())
                                   return BLOCK_ID(Air);

                                BlockState state{*block_id, 0};
                                for (const auto &property : item.properties) {
                                   state.set_from_string(property.first, property.second.as<std::string>());
                                }

                                return state.block_state_id();
                             });

              out_sec.m_data = container::PalettedVector<game::BlockStateId>::from_raw(
                      4096, sec.block_states.begin(), sec.block_states.end(), palette.begin(), palette.end());

              out_sec.m_reference_count = calculate_ref_count(sec.block_states, out_sec.m_data.palette());
              //              if (!sec.block_states.empty()) {
              //                 out_sec.m_data.
              //              }
              return std::make_pair(sec.y, out_sec);
           });
   return out;
}

nbt_chunk_v1::Chunk Chunk::to_nbt() noexcept
{
   nbt_chunk_v1::Chunk result;
   result.level.status      = m_full ? "full" : "features";
   result.level.x_pos       = m_pos_x;
   result.level.z_pos       = m_pos_z;
   result.level.last_update = static_cast<mb::i64>(minecpp::util::now());
   result.level.heightmaps.world_surface.resize(m_hm_world_surface.size());
   std::copy(m_hm_world_surface.begin(), m_hm_world_surface.end(),
             result.level.heightmaps.world_surface.begin());
   result.level.heightmaps.motion_blocking.resize(m_hm_motion_blocking.size());
   std::copy(m_hm_motion_blocking.begin(), m_hm_motion_blocking.end(),
             result.level.heightmaps.motion_blocking.begin());
   result.level.biomes.resize(m_biomes.size());
   std::copy(m_biomes.begin(), m_biomes.end(), result.level.biomes.begin());
   result.level.sections.reserve(m_sections.size());
   std::transform(m_sections.begin(), m_sections.end(), std::back_inserter(result.level.sections),
                  [](const std::pair<const mb::i8, Section> &pair) {
                     nbt_chunk_v1::Section sec;
                     sec.y           = pair.first;
                     sec.sky_light   = pair.second.sky_light.raw();
                     sec.block_light = pair.second.block_light.raw();
                     sec.palette.resize(pair.second.m_data.palette().size());
                     std::transform(pair.second.m_data.palette().begin(), pair.second.m_data.palette().end(),
                                    sec.palette.begin(), [](const game::BlockStateId state) {
                                       nbt_chunk_v1::PaletteItem item;
                                       auto [block_id, state_value] =
                                               repository::StateManager::the().parse_block_id(state);
                                       auto res = repository::Block::the().get_by_id(block_id);
                                       if (!res.ok()) {
                                          return item;
                                       }
                                       auto &block = res.unwrap();
                                       item.name   = block.tag();
                                       return item;
                                    });
                     sec.block_states.resize(pair.second.m_data.indices().raw().size());
                     std::copy(pair.second.m_data.indices().raw().begin(),
                               pair.second.m_data.indices().raw().end(), sec.block_states.begin());
                     return sec;
                  });
   return result;
}

mb::result<Section &> Chunk::section_from_y_level(int y)
{
   auto sec  = static_cast<mb::i8>(y / 16);
   auto iter = m_sections.find(sec);
   if (iter == m_sections.end()) {
      return mb::error("no such section");
   }
   return iter->second;
}

}// namespace minecpp::world
