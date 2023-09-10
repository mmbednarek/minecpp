#include <minecpp/game/ChunkPosition.h>
#include <minecpp/nbt/Parser.h>
#include <minecpp/repository/State.h>
#include <minecpp/util/Packed.h>
#include <minecpp/util/Time.h>
#include <minecpp/world/BlockState.h>
#include <minecpp/world/Chunk.h>

#include <mutex>
#include <stdexcept>
#include <vector>

namespace minecpp::world {

namespace nbt_chunk_v1 = minecpp::nbt::chunk;

Chunk::Chunk()
{
   std::fill(m_biomes.begin(), m_biomes.end(), 1);
}

Chunk::Chunk(int x, int z, const std::array<short, 256> &height_map) :
    m_position{x, z},
    m_is_full(false)
{
   m_motion_blocking_height = {height_map.begin(), height_map.end()};
   m_world_surface_height   = {height_map.begin(), height_map.end()};
   m_light_blocking_height  = {height_map.begin(), height_map.end()};
   std::fill(m_biomes.begin(), m_biomes.end(), 1);
}

constexpr uint32_t coord_to_offset(int x, int y, int z)
{
   return (y & 15) * 16 * 16 + (z & 15) * 16 + (x & 15);
}

void Chunk::create_empty_section(int8_t sec)
{
   m_sections.emplace(sec, Section{sec});
}

mb::emptyres Chunk::set_block_at(const game::BlockPosition &position, game::BlockStateId state)
{
   auto sec  = static_cast<std::int8_t>(position.y() / 16);
   auto iter = m_sections.find(sec);
   if (iter == m_sections.end()) {
      create_empty_section(sec);
      iter = m_sections.find(sec);
   }

   auto &section = iter->second;
   section.set_block(position, state);

   BlockState block_state{state};
   auto block = repository::Block::the().get_by_id(block_state.block_id());
   MB_VERIFY(block)

   if (block_state.solid_faces() & game::FaceMask::Top ||
       block_state.solid_faces() & game::FaceMask::Bottom || block_state.opacity() > 0) {
      if (height_at(game::HeightType::LightBlocking, position) < position.y()) {
         set_height(game::HeightType::LightBlocking, position, position.y());
      }
   }

   return mb::ok;
}

mb::result<game::BlockStateId> Chunk::block_at(const game::BlockPosition &position)
{
   auto section_id = static_cast<int8_t>(position.y() / 16);

   auto it_section = m_sections.find(section_id);
   if (it_section == m_sections.end())
      return DEFAULT_BLOCK_STATE(Air);

   return it_section->second.get_block(position);
}

mb::result<game::LightValue> Chunk::light_value_at(game::LightType type, const game::BlockPosition &position)
{
   auto section = section_from_y_level(position.y());
   if (section.has_failed()) {
      return std::move(section.err());
   }

   return section->get_light(type, position);
}

mb::emptyres Chunk::set_light_value_at(game::LightType type, const game::BlockPosition &position,
                                       game::LightValue value)
{
   auto section = section_from_y_level(position.y());
   if (section.has_failed()) {
      return std::move(section.err());
   }

   section->set_light(type, position, value);
   return mb::ok;
}

bool Chunk::add_player_reference(game::PlayerId player_id)
{
   std::unique_lock lk{m_player_references_mutex};
   m_player_references.insert(player_id);
   return true;
}

void Chunk::remove_player_reference(game::PlayerId player_id)
{
   std::unique_lock lk{m_player_references_mutex};

   if (m_player_references.find(player_id) == m_player_references.end())
      return;

   m_player_references.erase(player_id);
}

int Chunk::height_at(int x, int z) const
{
   return m_world_surface_height.at(16 * (z & 15) + (x & 15));
}

void Chunk::put_section(int8_t level, Section sec)
{
   if (m_sections.contains(level)) {
      m_sections.at(level) = sec;
      return;
   }
   m_sections.emplace(level, std::move(sec));
}

std::array<short, 256> Chunk::get_height_map() const
{
   std::array<short, 256> result{};
   for (std::size_t z{}; z < 16ul; ++z) {
      for (std::size_t x{}; x < 16ul; ++x) {
         result[z * 16 + x] = static_cast<short>(height_at(static_cast<int>(x), static_cast<int>(z)));
      }
   }
   return result;
}

game::ChunkPosition Chunk::position() const
{
   return m_position;
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

int Chunk::height_at(game::HeightType type, game::BlockPosition position) const
{
   return heightmap_of(type).at(16 * position.offset_z() + position.offset_x());
}

void Chunk::set_height(game::HeightType type, game::BlockPosition position, int value)
{
   heightmap_of(type).set(16 * position.offset_z() + position.offset_x(), value);
}

HeightContainer &Chunk::heightmap_of(game::HeightType type)
{
   switch (type) {
   case game::HeightTypeValues::MotionBlocking: return m_motion_blocking_height;
   case game::HeightTypeValues::WorldSurface: return m_world_surface_height;
   case game::HeightTypeValues::LightBlocking: return m_light_blocking_height;
   }

   assert(false && "not reachable");
}

const HeightContainer &Chunk::heightmap_of(game::HeightType type) const
{
   switch (type) {
   case game::HeightTypeValues::MotionBlocking: return m_motion_blocking_height;
   case game::HeightTypeValues::WorldSurface: return m_world_surface_height;
   case game::HeightTypeValues::LightBlocking: return m_light_blocking_height;
   }

   assert(false && "not reachable");
}

std::size_t Chunk::section_count() const
{
   return m_sections.size();
}

void Chunk::set_height_map(game::HeightType height_type, const std::array<short, 256> &height_map)
{
   auto &dest = heightmap_of(height_type);
   mb::size index{};
   for (auto value : height_map) {
      dest.set(index, value);
      ++index;
   }
}

std::map<int8_t, Section>::iterator Chunk::begin()
{
   return m_sections.begin();
}

std::map<int8_t, Section>::iterator Chunk::end()
{
   return m_sections.end();
}

std::map<int8_t, Section>::const_iterator Chunk::begin() const
{
   return m_sections.begin();
}

std::map<int8_t, Section>::const_iterator Chunk::end() const
{
   return m_sections.end();
}

std::int8_t Chunk::top_section() const
{
   return (--m_sections.end())->first;
}

std::int8_t Chunk::bottom_section() const
{
   return 0;
}

void Chunk::read_net_chunk(const net::Chunk &chunk)
{
   m_position               = game::ChunkPosition(chunk.position);
   m_motion_blocking_height = HeightContainer::from_raw(chunk.heightmaps.motion_blocking.begin(),
                                                        chunk.heightmaps.motion_blocking.end());
   m_world_surface_height   = HeightContainer::from_raw(chunk.heightmaps.world_surface.begin(),
                                                        chunk.heightmaps.world_surface.end());

   container::BufferView buffer(const_cast<unsigned char *>(chunk.data.data()), chunk.data.size());
   auto stream = buffer.make_stream();
   network::message::Reader reader(stream);

   auto data = minecpp::net::ChunkData::deserialize(reader, 16);

   std::int8_t section_y = 0;
   for (const auto &section : data.sections) {
      this->put_section(section_y, world::Section::from_net(section, section_y));
      ++section_y;
   }

   if (not chunk.light_data.sky_light_mask.empty()) {
      auto sky_mask = chunk.light_data.sky_light_mask.front();
      std::int8_t index{-1};
      auto at = chunk.light_data.sky_light.begin();
      while (sky_mask != 0) {
         if ((sky_mask & 0x1) == 0x1) {
            auto section = this->section(index);
            if (section.has_failed()) {
               this->create_empty_section(index);
               section = this->section(index);
            }
            assert(at != chunk.light_data.sky_light.end());

            section->fill_light(game::LightType::Sky);
            *section->light_data(game::LightType::Sky) = LightContainer::from_raw(at->begin(), at->end());
            ++at;
         }

         sky_mask >>= 1u;
         ++index;
      }

      assert(at == chunk.light_data.sky_light.end());
   }
}

int Chunk::calculate_top_block() const
{
   int max_value   = 0;
   const auto size = m_world_surface_height.size();
   for (std::size_t i{}; i < size; ++i) {
      auto value = m_world_surface_height.at(i);
      if (value > max_value) {
         max_value = value;
      }
   }
   return max_value;
}

}// namespace minecpp::world
