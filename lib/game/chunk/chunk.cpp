#include "chunk.h"
#include <game/blocks/registry.h>
#include <game/chunk/utils.h>
#include <game/items/registry.h>
#include <mineutils/packed.h>
#include <nbt/parser.h>
#include <stdexcept>
#include <vector>

namespace Game {

inline int expected_data_version = 2230;

Chunk::Chunk() = default;

Chunk::Chunk(int x, int z, std::array<short, 256> &height_map) : pos_x(x), pos_z(z), full(false) {
   int i = 0;
   auto arr = Utils::generate_packed(9, 256, [&height_map, &i]() {
      return height_map[i++];
   });

   std::copy(arr.begin(), arr.end(), hm_motion_blocking.begin());
   std::copy(arr.begin(), arr.end(), hm_world_surface.begin());

   std::fill(biomes.begin(), biomes.end(), 34);
}

result<std::unique_ptr<Chunk>> Chunk::from_nbt(NBT::Reader &r) {
   auto chunk = std::make_unique<Chunk>();
   try {
      tryget(r.try_read_compound([&chunk](NBT::Reader &r, NBT::TagId tagid, const std::string &name) -> result<empty> {
         return chunk->load(r, tagid, name);
      }));
      return result<std::unique_ptr<Chunk>>(std::move(chunk));
   } catch (std::exception &e) {
      return errorf("exception while reading nbt tag: ", e.what());
   }
}

result<empty> Chunk::load(NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
   switch (tagid) {
   case NBT::TagId::String:
      if (name == "Status") {
         if (auto status = r.read_str(); status == "full") {
            full = true;
         }
         return result_ok;
      }

      r.skip_payload(NBT::TagId::String);
      return result_ok;
   case NBT::TagId::Int:
      if (name == "xPos") {
         pos_x = r.read_int();
         return result_ok;
      }
      if (name == "zPos") {
         pos_z = r.read_int();
         return result_ok;
      }
      r.skip_payload(NBT::TagId::Int);
      return result_ok;
   case NBT::TagId::Compound:
      if (name == "Heightmaps") {
         tryget(r.try_read_compound([this](NBT::Reader &r, NBT::TagId tagid, const std::string &name) -> result<empty> {
            if (tagid != NBT::TagId::LongArray) {
               return error(errclass::Internal, "height map expected to be a long array");
            }

            if (name == "MOTION_BLOCKING") {
               hm_motion_blocking = r.read_long_array<37>();
               return result_ok;
            }
            if (name == "WORLD_SURFACE") {
               hm_world_surface = r.read_long_array<37>();
               return result_ok;
            }

            r.skip_payload(tagid);
            return result_ok;
         }));
         return result_ok;
      }
      r.skip_payload(tagid);
      return result_ok;
   case NBT::TagId::IntArray:
      if (name == "Biomes") {
         biomes = r.read_int_array<1024>();
         return result_ok;
      }
      r.skip_payload(NBT::TagId::IntArray);
      return result_ok;
   case NBT::TagId::List:
      if (name == "Sections") {
         r.read_list([this](NBT::Reader &r) {
            int8_t y = 0;
            std::vector<int64_t> data;
            std::vector<uint8_t> block_light;
            std::vector<uint8_t> sky_light;
            std::vector<std::uint32_t> palette;
            r.read_compound([&y, &data, &palette, &block_light, &sky_light](NBT::Reader &r, NBT::TagId tag_id,
                                                                            const std::string &name) {
               if (tag_id == NBT::TagId::Byte && name == "Y") {
                  y = r.read_byte();
                  return;
               }
               if (tag_id == NBT::TagId::ByteArray) {
                  if (name == "BlockLight") {
                     block_light = r.read_byte_vector();
                     return;
                  }
                  if (name == "SkyLight") {
                     sky_light = r.read_byte_vector();
                     return;
                  }
               }
               if (tag_id == NBT::TagId::LongArray && name == "BlockStates") {
                  data = r.read_long_vec();
                  return;
               }
               if (tag_id == NBT::TagId::List && name == "Palette") {
                  r.read_list([&palette](NBT::Reader &r) { palette.emplace_back(PaletteItem(r).to_state_id()); });
                  return;
               }
               r.skip_payload(tag_id);
            });

            uint8_t bits = data.size() * 64 / 4096;
            int ref_count = Game::calculate_ref_count(data, palette);

            sections[y] = Section{
                    .ref_count = ref_count,
                    .palette = std::move(palette),
                    .data = Squeeze::Vector(bits, 4096, data),
                    .block_light = Squeeze::TinyVec<4>(std::move(block_light)),
                    .sky_light = Squeeze::TinyVec<4>(std::move(sky_light)),
            };
         });
         return result_ok;
      }
      r.skip_payload(NBT::TagId::List);
      return result_ok;
   case NBT::TagId::Long:
      r.skip_payload(NBT::TagId::Long);
      return result_ok;
   case NBT::TagId::Byte:
      r.skip_payload(NBT::TagId::Byte);
      return result_ok;
   default:
      return error(errclass::Internal, "invalid nbt tag");
   }
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
   sections[sec] = Game::Section{
           .ref_count = 4096,
           .palette{0},
           .data{4, 4096, []() {return 0;}},
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
      iter->second.block_light = Squeeze::TinyVec<4>(4096);
   }

   iter->second.block_light.set(coord_to_offset(x, y, z), value);
}

void Chunk::set_sky_light(int x, int y, int z, uint8_t value) {
   int8_t sec = y / 16;
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      return;
   }

   if (iter->second.block_light.empty()) {
      iter->second.block_light = Squeeze::TinyVec<4>(4096);
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

int Chunk::height_at(int x, int z) { return Utils::get_packed(hm_world_surface, 9, 16 * (z & 15) + (x & 15)); }

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

Block::ChunkPos Chunk::pos() const {
   return Block::ChunkPos(pos_x, pos_z);
}

PaletteItem::PaletteItem(NBT::Reader &r) {
   r.read_compound([this](NBT::Reader &r, NBT::TagId type, std::string key) {
      if (key == "Name" && type == NBT::TagId::String) {
         tag_name = r.read_str();
         return;
      }
      if (key == "Properties" && type == NBT::TagId::Compound) {
         NBT::Parser p(r.raw_stream());
         properties = p.read_compound();
         return;
      }
      r.skip_payload(type);// ignore properties for now
   });
}

uint32_t PaletteItem::to_state_id() { return Block::encode_state(tag_name, properties); }

}// namespace Game
