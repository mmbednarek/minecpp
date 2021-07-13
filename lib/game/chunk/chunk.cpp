#include <fmt/core.h>
#include <minecpp/game/block/registry.h>
#include <minecpp/game/chunk/chunk.h>
#include <minecpp/game/chunk/utils.h>
#include <minecpp/game/item/registry.h>
#include <minecpp/nbt/parser.h>
#include <minecpp/util/packed.h>
#include <minecpp/util/time.h>
#include <stdexcept>
#include <vector>

namespace minecpp::game {

inline int expected_data_version = 2230;

Chunk::Chunk() = default;

Chunk::Chunk(int x, int z, std::array<short, 256> &height_map) : m_pos_x(x), m_pos_z(z), m_full(false) {
   int i = 0;
   auto arr = minecpp::util::generate_packed(9, 256, [&height_map, &i]() {
      return height_map[i++];
   });

   std::copy(arr.begin(), arr.end(), m_hm_motion_blocking.begin());
   std::copy(arr.begin(), arr.end(), m_hm_world_surface.begin());

   std::fill(m_biomes.begin(), m_biomes.end(), 1);
}

void Chunk::as_proto(minecpp::chunk::NetChunk *chunk) {
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
      out_sec->set_y(sec.first);
      out_sec->set_bits(sec.second.data.bits());
      out_sec->set_ref_count(sec.second.ref_count);
      *out_sec->mutable_palette() = {sec.second.palette.begin(), sec.second.palette.end()};
      *out_sec->mutable_data() = {sec.second.data.raw().begin(), sec.second.data.raw().end()};
      *out_sec->mutable_block_light() = {sec.second.block_light.raw().begin(), sec.second.block_light.raw().end()};
      *out_sec->mutable_sky_light() = {sec.second.sky_light.raw().begin(), sec.second.sky_light.raw().end()};
   }
}

constexpr uint32_t coord_to_offset(int x, int y, int z) { return (y & 15) * 16 * 16 + (z & 15) * 16 + (x & 15); }

void Chunk::create_empty_section(int8_t sec) {
   m_sections[sec] = game::Section{
           .ref_count = 4096,
           .palette{0},
           .data{4, 4096, []() { return 0; }},
   };
}

void Chunk::set_block(int x, int y, int z, uint32_t state) {
   int8_t sec = y / 16;
   auto iter = m_sections.find(sec);
   if (iter == m_sections.end()) {
      create_empty_section(sec);
      iter = m_sections.find(sec);
   }

   auto &section = iter->second;
   auto index = std::find(section.palette.begin(), section.palette.end(), state);
   int value;
   if (index == section.palette.end()) {
      value = section.palette.size();
      section.palette.emplace_back(state);
   } else {
      value = std::distance(section.palette.begin(), index);
   }

   section.data.set(coord_to_offset(x, y, z), value);

   set_block_light(x, y, z, 15);
   set_sky_light(x, y, z, 15);
}

uint8_t Chunk::get_block_light(int x, int y, int z) {
   int8_t sec = y / 16;
   auto iter = m_sections.find(sec);
   if (iter == m_sections.end()) {
      return 0;
   }

   if (iter->second.block_light.empty()) {
      return 0;
   }

   return iter->second.block_light.at(coord_to_offset(x, y, z));
}

void Chunk::set_block_light(int x, int y, int z, uint8_t value) {
   int8_t sec = y / 16;
   auto iter = m_sections.find(sec);
   if (iter == m_sections.end()) {
      return;
   }

   if (iter->second.block_light.empty()) {
      iter->second.block_light = minecpp::squeezed::TinyVec<4>(4096);
   }

   iter->second.block_light.set(coord_to_offset(x, y, z), value);
}

void Chunk::set_sky_light(int x, int y, int z, uint8_t value) {
   int8_t sec = y / 16;
   auto iter = m_sections.find(sec);
   if (iter == m_sections.end()) {
      return;
   }

   if (iter->second.sky_light.empty()) {
      iter->second.sky_light = minecpp::squeezed::TinyVec<4>(4096);
   }

   iter->second.sky_light.set(coord_to_offset(x, y, z), value);
}

bool Chunk::add_ref(uuid engine_id, uuid player_id) {
   m_references.insert(player_id);

   if (!m_engine_lock.is_nil()) {
      if (m_engine_lock != engine_id) {
         return false;
      }
   }
   m_engine_lock = engine_id;
   return true;
}

void Chunk::free_ref(uuid player_id) {
   if (m_references.find(player_id) == m_references.end()) {
      return;
   }
   m_references.erase(player_id);
   if (m_references.empty()) {
      m_engine_lock = {};
   }
}

uuid Chunk::get_lock() const { return m_engine_lock; }

int Chunk::height_at(int x, int z) { return minecpp::util::get_packed(m_hm_world_surface, 9, 16 * (z & 15) + (x & 15)); }

void Chunk::put_section(int8_t level, Section sec) {
   m_sections[level] = std::move(sec);
}

std::array<short, 256> Chunk::get_height_map() {
   std::array<short, 256> result{};
   for (int z = 0; z < 16; ++z) {
      for (int x = 0; x < 16; ++x) {
         result[z * 16 + x] = height_at(x, z);
      }
   }
   return result;
}

block::ChunkPos Chunk::pos() const {
   return block::ChunkPos(m_pos_x, m_pos_z);
}

mb::result<std::unique_ptr<Chunk>> Chunk::from_nbt(minecpp::message::nbt::Chunk &chunk) noexcept {
   auto out = std::make_unique<Chunk>();
   out->m_full = chunk.level.status == "full";
   out->m_pos_x = chunk.level.x_pos;
   out->m_pos_z = chunk.level.z_pos;
   std::copy(chunk.level.heightmaps.world_surface.begin(), chunk.level.heightmaps.world_surface.end(), out->m_hm_world_surface.begin());
   std::copy(chunk.level.heightmaps.motion_blocking.begin(), chunk.level.heightmaps.motion_blocking.end(), out->m_hm_motion_blocking.begin());
   //   std::copy(chunk.level.biomes.begin(), chunk.level.biomes.end(), out->biomes.begin());
   std::fill_n(out->m_biomes.begin(), 1024, 1);
   std::transform(chunk.level.sections.begin(), chunk.level.sections.end(), std::inserter(out->m_sections, out->m_sections.begin()), [](const minecpp::message::nbt::Section &sec) {
      Section out_sec;
      out_sec.sky_light = minecpp::squeezed::TinyVec<4>(sec.sky_light);
      out_sec.block_light = minecpp::squeezed::TinyVec<4>(sec.block_light);
      out_sec.palette.resize(sec.palette.size());
      std::transform(sec.palette.begin(), sec.palette.end(), out_sec.palette.begin(), [](const minecpp::message::nbt::PaletteItem &item) {
         return block::encode_state(item.name, item.properties);
      });
      out_sec.ref_count = game::calculate_ref_count(sec.block_states, out_sec.palette);
      if (!sec.block_states.empty()) {
         out_sec.data = minecpp::squeezed::Vector(sec.block_states.size() * 64 / 4096, 4096, sec.block_states);
      }
      return std::make_pair(sec.y, out_sec);
   });
   return out;
}

minecpp::message::nbt::Chunk Chunk::to_nbt() noexcept {
   minecpp::message::nbt::Chunk result;
   result.level.status = m_full ? "full" : "features";
   result.level.x_pos = m_pos_x;
   result.level.z_pos = m_pos_z;
   result.level.last_update = minecpp::util::now();
   result.level.heightmaps.world_surface.resize(m_hm_world_surface.size());
   std::copy(m_hm_world_surface.begin(), m_hm_world_surface.end(), result.level.heightmaps.world_surface.begin());
   result.level.heightmaps.motion_blocking.resize(m_hm_motion_blocking.size());
   std::copy(m_hm_motion_blocking.begin(), m_hm_motion_blocking.end(), result.level.heightmaps.motion_blocking.begin());
   result.level.biomes.resize(m_biomes.size());
   std::copy(m_biomes.begin(), m_biomes.end(), result.level.biomes.begin());
   result.level.sections.reserve(m_sections.size());
   std::transform(m_sections.begin(), m_sections.end(), std::back_inserter(result.level.sections), [](const std::pair<const mb::i8, Section> &pair) {
      minecpp::message::nbt::Section sec;
      sec.y = pair.first;
      sec.sky_light = pair.second.sky_light.raw();
      sec.block_light = pair.second.block_light.raw();
      sec.palette.resize(pair.second.palette.size());
      std::transform(pair.second.palette.begin(), pair.second.palette.end(), sec.palette.begin(), [](const mb::u32 state) {
         minecpp::message::nbt::PaletteItem item;
         item.name = fmt::format("minecraft:{}", block::tag_from_state_id(state));
         return item;
      });
      sec.block_states.resize(pair.second.data.raw().size());
      std::copy(pair.second.data.raw().begin(), pair.second.data.raw().end(), sec.block_states.begin());
      return sec;
   });
   return result;
}

}// namespace minecpp::game
