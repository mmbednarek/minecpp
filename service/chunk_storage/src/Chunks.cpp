#include "Chunks.h"
#include <minecpp/game/Game.h>
#include <minecpp/nbt/Parser.h>
#include <minecpp/region/File.h>
#include <minecpp/util/Compression.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::chunk_storage {

using mb::result;

ChunkManager::ChunkManager(Regions regions) :
    m_regions(std::move(regions)),
    gen(*this, 43254124543534345)
{
}

constexpr int64_t max_z = 1875060;

static constexpr int64_t hash_chunk_pos(int x, int z)
{
   return static_cast<int64_t>(z) + max_z * static_cast<int64_t>(x);
}

world::Chunk &ChunkManager::get_incomplete_chunk(int x, int z)
{
   auto hash = hash_chunk_pos(x, z);
   auto iter = m_chunks.find(hash);
   if (iter != m_chunks.end()) {
      return *iter->second;
   }

   gen.generate_terrain({x, z});
   iter = m_chunks.find(hash);
   return *iter->second;
}

result<world::Chunk &> ChunkManager::get_chunk(int x, int z)
{
   auto iter = m_chunks.find(hash_chunk_pos(x, z));
   if (iter != m_chunks.end() && iter->second->full()) {
      return *iter->second;
   }
   return load_chunk(x, z);
}

result<world::Chunk &> ChunkManager::get_chunk(const game::ChunkPosition &pos)
{
   return get_chunk(pos.x, pos.z);
}

result<world::Chunk &> ChunkManager::load_chunk(int x, int z)
{
   //   auto data = MB_TRY(m_regions.read_chunk(x, z));
   //   auto chunk_data = std::any_cast<std::vector<uint8_t>>(data);
   //   std::istringstream compressed_stream(std::string((char *) chunk_data.data(), chunk_data.size()));
   //   minecpp::util::ZlibInputStream chunk_stream(compressed_stream);

   //   auto nbt_chunk = minecpp::nbt::chunk::v1::Chunk::deserialize(chunk_stream);
   //   m_Chunks.hash_chunk_pos(x, z)] = MB_TRY(minecpp::game::Chunk::from_nbt(nbt_chunk));

   gen.generate_chunk({x, z});
   auto &chunk = *m_chunks.at(hash_chunk_pos(x, z));
   return chunk;
}

result<mb::empty> ChunkManager::save_chunk(int x, int z)
{
   auto chunk_it = m_chunks.find(hash_chunk_pos(x, z));
   if (chunk_it == m_chunks.end()) {
      return mb::error("chunk not found");
   }

   auto nbt_chunk = chunk_it->second->to_nbt();
   std::stringstream ss;
   nbt_chunk.serialize(ss, "");
   std::vector<char> buff;
   minecpp::util::compress_zlib(buff, ss);
   MB_TRY(m_regions.write_chunk(x, z, buff));
   return mb::ok;
}

result<mb::empty> ChunkManager::set_block(int x, int y, int z, uint32_t state)
{
   minecpp::game::BlockPosition pos(x, y, z);
   auto chunk_pos  = pos.chunk_position();
   auto hashed_pos = hash_chunk_pos(chunk_pos.x, chunk_pos.z);

   if (auto iter = m_chunks.find(hashed_pos); iter == m_chunks.end()) {
      if (auto res = load_chunk(chunk_pos.x, chunk_pos.z); !res.ok()) {
         return std::move(res.err());
      }
   }

   m_chunks[hashed_pos]->set_block(pos, state);

   if (auto res = save_chunk(chunk_pos.x, chunk_pos.z); !res.ok()) {
      spdlog::error("could not save chunk: {}", res.err()->msg());
      return res;
   }
   spdlog::info("successfully saved chunk!");
   return mb::ok;
}

result<uuid> ChunkManager::add_refs(uuid engine_id, game::PlayerId player_id,
                                    std::vector<minecpp::game::ChunkPosition> coords)
{
   uuid target_engine{};
   for (const auto &coord : coords) {
      auto chunk = MB_TRY(get_chunk(coord.x, coord.z));
      if (!chunk.add_ref(engine_id, player_id)) {
         target_engine = chunk.get_lock();
      }
   }
   return target_engine;
}

result<mb::empty> ChunkManager::free_refs(game::PlayerId player_id,
                                          std::vector<minecpp::game::ChunkPosition> coords)
{
   for (const auto &coord : coords) {
      auto chunk = MB_TRY(get_chunk(coord.x, coord.z));
      chunk.free_ref(player_id);
   }
   return mb::ok;
}

result<int> ChunkManager::height_at(int x, int z)
{
   auto res = get_chunk(minecpp::game::BlockPosition(x, 0, z).chunk_position());
   if (!res.ok()) {
      return std::move(res.err());
   }
   return res.get().height_at(x, z);
}

mb::result<mb::empty> ChunkManager::put_chunk(game::ChunkPosition position, std::unique_ptr<world::Chunk> chunk)
{
   m_chunks[hash_chunk_pos(position.x, position.z)] = std::move(chunk);
   return mb::ok;
}

result<world::ChunkState> ChunkManager::get_chunk_state(game::ChunkPosition position)
{
   auto iter = m_chunks.find(hash_chunk_pos(position.x, position.z));
   if (iter == m_chunks.end()) {
      return world::ChunkState::ABSENT;
   }

   if (iter->second->full()) {
      return world::ChunkState::COMPLETE;
   }

   return world::ChunkState::TERRAIN;
}

result<world::SectionSlice> ChunkManager::get_slice(game::SectionRange range)
{
   world::SectionSlice result{range, {}};
   for (auto section_position : range) {
      auto chunk = get_chunk(section_position.chunk_position);
      MB_VERIFY(chunk);

      auto section = chunk->section(static_cast<mb::i8>(section_position.y));
      if (section.has_failed())
         continue;
      result[section_position] = *section;
   }

   return result;
}

mb::emptyres ChunkManager::apply_slice(world::SectionSlice &slice)
{
   for (auto section_position : slice.range()) {
      auto chunk = get_chunk(section_position.chunk_position);
      MB_VERIFY(chunk);

      auto section = dynamic_cast<world::Section *>(&slice[section_position]);
      if (section == nullptr)
         continue;

      chunk->put_section(static_cast<mb::i8>(section_position.y), *section);
   }

   return mb::ok;
}

}// namespace minecpp::service::chunk_storage
