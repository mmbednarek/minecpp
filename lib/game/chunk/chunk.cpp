#include <minecpp/game/block/registry.h>
#include <minecpp/game/chunk/chunk.h>
#include <minecpp/game/chunk/utils.h>
#include <minecpp/game/item/registry.h>
#include <minecpp/nbt/parser.h>
#include <minecpp/util/packed.h>
#include <stdexcept>
#include <vector>

namespace minecpp::game {

inline int expected_data_version = 2230;

Chunk::Chunk() = default;

Chunk::Chunk(int x, int z, std::array<short, 256> &height_map) : pos_x(x), pos_z(z), full(false) {
   int i = 0;
   auto arr = minecpp::util::generate_packed(9, 256, [&height_map, &i]() {
      return height_map[i++];
   });

   std::copy(arr.begin(), arr.end(), hm_motion_blocking.begin());
   std::copy(arr.begin(), arr.end(), hm_world_surface.begin());

   std::fill(biomes.begin(), biomes.end(), 1);
}

void Chunk::as_proto(minecpp::chunk::NetChunk *chunk) {
   chunk->set_pos_x(pos_x);
   chunk->set_pos_z(pos_z);
   chunk->set_full(full);
   if (full) {
      *chunk->mutable_biomes() = {biomes.begin(), biomes.end()};
   }
   *chunk->mutable_hm_motion_blocking() = {hm_motion_blocking.begin(), hm_motion_blocking.end()};

   *chunk->mutable_hm_world_surface() = {hm_world_surface.begin(), hm_world_surface.end()};

   for (auto const &sec : sections) {
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
   sections[sec] = game::Section{
           .ref_count = 4096,
           .palette{0},
           .data{4, 4096, []() { return 0; }},
   };
}

void Chunk::set_block(int x, int y, int z, uint32_t state) {
   int8_t sec = y / 16;
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      create_empty_section(sec);
      iter = sections.find(sec);
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
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      return 0;
   }

   if (iter->second.block_light.empty()) {
      return 0;
   }

   return iter->second.block_light.at(coord_to_offset(x, y, z));
}

void Chunk::set_block_light(int x, int y, int z, uint8_t value) {
   int8_t sec = y / 16;
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      return;
   }

   if (iter->second.block_light.empty()) {
      iter->second.block_light = minecpp::squeezed::TinyVec<4>(4096);
   }

   iter->second.block_light.set(coord_to_offset(x, y, z), value);
}

void Chunk::set_sky_light(int x, int y, int z, uint8_t value) {
   int8_t sec = y / 16;
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      return;
   }

   if (iter->second.sky_light.empty()) {
      iter->second.sky_light = minecpp::squeezed::TinyVec<4>(4096);
   }

   iter->second.sky_light.set(coord_to_offset(x, y, z), value);
}

bool Chunk::add_ref(uuid engine_id, uuid player_id) {
   refs.insert(player_id);

   if (!engine_lock.is_nil()) {
      if (engine_lock != engine_id) {
         return false;
      }
   }
   engine_lock = engine_id;
   return true;
}

void Chunk::free_ref(uuid player_id) {
   if (refs.find(player_id) == refs.end()) {
      return;
   }
   refs.erase(player_id);
   if (refs.empty()) {
      engine_lock = {};
   }
}

uuid Chunk::get_lock() const { return engine_lock; }

int Chunk::height_at(int x, int z) { return minecpp::util::get_packed(hm_world_surface, 9, 16 * (z & 15) + (x & 15)); }

void Chunk::put_section(int8_t level, Section sec) {
   sections[level] = std::move(sec);
}

std::array<short, 256> Chunk::get_height_map() {
   std::array<short, 256> result;
   for (int z = 0; z < 16; ++z) {
      for (int x = 0; x < 16; ++x) {
         result[z * 16 + x] = height_at(x, z);
      }
   }
   return result;
}

block::ChunkPos Chunk::pos() const {
   return block::ChunkPos(pos_x, pos_z);
}

mb::result<std::unique_ptr<Chunk>> Chunk::from_nbt(minecpp::message::nbt::Chunk &chunk) {
   auto out = std::make_unique<Chunk>();
   out->full = chunk.level.status == "full";
   out->pos_x = chunk.level.x_pos;
   out->pos_z = chunk.level.z_pos;
   std::copy(chunk.level.heightmaps.world_surface.begin(), chunk.level.heightmaps.world_surface.end(), out->hm_world_surface.begin());
   std::copy(chunk.level.heightmaps.motion_blocking.begin(), chunk.level.heightmaps.motion_blocking.end(), out->hm_motion_blocking.begin());
//   std::copy(chunk.level.biomes.begin(), chunk.level.biomes.end(), out->biomes.begin());
   std::fill_n(out->biomes.begin(), 1024, 1);
   std::for_each(chunk.level.sections.begin(), chunk.level.sections.end(), [&out](const minecpp::message::nbt::Section &sec) {
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
      out->sections[sec.y] = out_sec;
   });
   return out;
}

}// namespace minecpp::game
