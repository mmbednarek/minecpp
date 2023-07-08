#include <minecpp/game/ChunkPosition.h>
#include <minecpp/nbt/Parser.h>
#include <minecpp/repository/State.h>
#include <minecpp/util/Packed.h>
#include <minecpp/util/Time.h>
#include <minecpp/world/BlockState.h>
#include <minecpp/world/Chunk.h>
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

int Chunk::height_at(int x, int z)
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

std::array<short, 256> Chunk::get_height_map()
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

mb::result<std::unique_ptr<Chunk>> Chunk::from_nbt(nbt_chunk_v1::Chunk &chunk) noexcept
{
   auto out                      = std::make_unique<Chunk>();
   out->m_is_full                = chunk.level.status == "full";
   out->m_position               = {chunk.level.x_pos, chunk.level.z_pos};
   out->m_motion_blocking_height = HeightContainer::from_raw(chunk.level.heightmaps.motion_blocking.begin(),
                                                             chunk.level.heightmaps.motion_blocking.end());
   out->m_world_surface_height   = HeightContainer::from_raw(chunk.level.heightmaps.world_surface.begin(),
                                                             chunk.level.heightmaps.world_surface.end());
   std::fill_n(out->m_biomes.begin(), 1024, 1);
   std::transform(chunk.level.sections.begin(), chunk.level.sections.end(),
                  std::inserter(out->m_sections, out->m_sections.begin()),
                  [](const nbt_chunk_v1::Section &section) {
                     return std::make_pair(section.y, Section::from_nbt(section));
                  });
   return out;
}

nbt_chunk_v1::Chunk Chunk::to_nbt() noexcept
{
   nbt_chunk_v1::Chunk result;
   result.level.status      = m_is_full ? "full" : "features";
   result.level.x_pos       = m_position.x();
   result.level.z_pos       = m_position.z();
   result.level.last_update = static_cast<mb::i64>(minecpp::util::now());

   result.level.heightmaps.motion_blocking.resize(m_motion_blocking_height.raw().size());
   std::copy(m_motion_blocking_height.raw().begin(), m_motion_blocking_height.raw().end(),
             result.level.heightmaps.motion_blocking.begin());

   result.level.heightmaps.world_surface.resize(m_world_surface_height.raw().size());
   std::copy(m_world_surface_height.raw().begin(), m_world_surface_height.raw().end(),
             result.level.heightmaps.world_surface.begin());

   result.level.biomes.resize(m_biomes.size());
   std::copy(m_biomes.begin(), m_biomes.end(), result.level.biomes.begin());
   result.level.sections.reserve(m_sections.size());
   std::transform(m_sections.begin(), m_sections.end(), std::back_inserter(result.level.sections),
                  [](const std::pair<const mb::i8, Section> &pair) { return pair.second.to_nbt(); });
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

int Chunk::height_at(game::HeightType type, game::BlockPosition position) const
{
   return height_by_type(type).at(16 * position.offset_z() + position.offset_x());
}

void Chunk::set_height(game::HeightType type, game::BlockPosition position, int value)
{
   height_by_type(type).set(16 * position.offset_z() + position.offset_x(), value);
}

HeightContainer &Chunk::height_by_type(game::HeightType type)
{
   switch (type) {
   case game::HeightTypeValues::MotionBlocking: return m_motion_blocking_height;
   case game::HeightTypeValues::WorldSurface: return m_world_surface_height;
   case game::HeightTypeValues::LightBlocking: return m_light_blocking_height;
   }

   assert(false && "not reachable");
}

const HeightContainer &Chunk::height_by_type(game::HeightType type) const
{
   switch (type) {
   case game::HeightTypeValues::MotionBlocking: return m_motion_blocking_height;
   case game::HeightTypeValues::WorldSurface: return m_world_surface_height;
   case game::HeightTypeValues::LightBlocking: return m_light_blocking_height;
   }

   assert(false && "not reachable");
}

minecpp::proto::chunk::Chunk Chunk::to_proto() const
{
   minecpp::proto::chunk::Chunk chunk;
   *chunk.mutable_position() = position().to_proto();
   chunk.set_full(m_is_full);
   if (m_is_full) {
      *chunk.mutable_biomes() = {m_biomes.begin(), m_biomes.end()};
   }
   *chunk.mutable_hm_motion_blocking() = {m_motion_blocking_height.raw().begin(),
                                          m_motion_blocking_height.raw().end()};
   *chunk.mutable_hm_world_surface()   = {m_world_surface_height.raw().begin(),
                                          m_world_surface_height.raw().end()};

   for (auto const &sec : m_sections) {
      auto *out_sec = chunk.add_sections();
      *out_sec      = sec.second.to_proto();
      out_sec->set_y(sec.first);
   }

   return chunk;
}

std::unique_ptr<Chunk> Chunk::from_proto(const minecpp::proto::chunk::Chunk &proto_chunk)
{
   auto chunk = std::make_unique<Chunk>();
   chunk->read_from_proto(proto_chunk);
   return chunk;
}

void Chunk::read_from_proto(const proto::chunk::Chunk &proto_chunk)
{
   m_position = game::ChunkPosition::from_proto(proto_chunk.position());

   if (not proto_chunk.biomes().empty()) {
      m_is_full = true;
      std::copy(proto_chunk.biomes().begin(), proto_chunk.biomes().end(), m_biomes.begin());
   }

   m_motion_blocking_height = HeightContainer::from_raw(proto_chunk.hm_motion_blocking().begin(),
                                                        proto_chunk.hm_motion_blocking().end());
   m_world_surface_height   = HeightContainer::from_raw(proto_chunk.hm_world_surface().begin(),
                                                        proto_chunk.hm_world_surface().end());

   for (auto const &section : proto_chunk.sections()) {
      this->put_section(static_cast<mb::i8>(section.y()), Section::from_proto(section));
   }
}

std::size_t Chunk::section_count()
{
   return m_sections.size();
}

void Chunk::set_height_map(game::HeightType height_type, const std::array<short, 256> &height_map)
{
   auto &dest = height_by_type(height_type);
   mb::size index{};
   for (auto value : height_map) {
      dest.set(index, value);
      ++index;
   }
}

}// namespace minecpp::world
