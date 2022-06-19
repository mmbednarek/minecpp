#include <minecpp/random/JavaRandom.h>
#include <minecpp/world/population/Chunk.h>
#include <minecpp/world/population/Object.h>

namespace minecpp::world::population {

ChunkPlacements::ChunkPlacements(Chunk &chunk, std::uint64_t seed) :
    m_seed(seed)
{
   prepare_chunk(chunk);
}

Placement ChunkPlacements::get_placement(int x, int z)
{
   auto p = m_placements.find(game::BlockPosition{x, 0, z}.as_long());
   if (p == m_placements.end()) {
      return Placement{
              .object_id = -1,
      };
   }
   return p->second;
}

void ChunkPlacements::prepare_chunk(Chunk &chunk)
{
   random::JavaRandom rand(m_seed);
   auto chunk_pos = chunk.pos();

   for (int _z = 0; _z < 16; ++_z) {
      for (int _x = 0; _x < 16; ++_x) {
         auto hash = chunk_pos.block_at(_x, 0, _z).as_long();
         if (m_placements.contains(hash)) {
            continue;
         }
         short height = chunk.height_at(_x, _z) + 1;
         if (height < 65 || height > 86)
            continue;

         std::uint32_t value = rand.next_int(10000);
         auto objid          = ObjectRepository::the().find_object_id(value);
         if (objid >= 0) {
            put_object(chunk, objid, _x, height, _z);
         }
      }
   }
}

void ChunkPlacements::put_object(Chunk &chunk, int id, int x, int y, int z)
{
   if (id < 0)
      return;
   unsigned object_seed = rand();// TODO: Replace with good random

   const auto &obj = ObjectRepository::the().get_object(id, object_seed);
   auto center     = obj.center();

   std::uint16_t center_offset = z * 16 + x;
   if (center_offset > 255) {
      return;
   }

   for (int _z = -center.z; _z < obj.length() - center.z; ++_z) {
      for (int _x = -center.x; _x < obj.width() - center.x; ++_x) {
         auto hash = chunk.pos().block_at(x + _x, 0, z + _z).as_long();
         if (m_placements.contains(hash)) {
            return;
         }
      }
   }
   for (int _z = -center.z; _z < obj.length() - center.z; ++_z) {
      for (int _x = -center.x; _x < obj.width() - center.x; ++_x) {
         m_placements[chunk.pos().block_at(x + _x, 0, z + _z).as_long()] =
                 Placement{.object_id   = id,
                           .object_seed = object_seed,
                           .x           = static_cast<short>(_x + center.x),
                           .z           = static_cast<short>(_z + center.z),
                           .chunk_x     = static_cast<short>(x + _x),
                           .chunk_z     = static_cast<short>(z + _z),
                           .height      = static_cast<short>(y)};
      }
   }
}

void ChunkPlacements::populate_chunk(Chunk &chunk)
{
   std::for_each(m_placements.begin(), m_placements.end(), [&chunk](auto &pair) {
      Placement &placement = pair.second;
      auto &obj            = ObjectRepository::the().get_object(placement.object_id, placement.object_seed);
      if (placement.chunk_x < 0 || placement.chunk_x >= 16 || placement.chunk_z < 0 ||
          placement.chunk_z >= 16)
         return;
      for (int y = 0; y < obj.height(); ++y) {
         auto state = obj.block_at(placement.x, y, placement.z);
         if (state != 0) {
            chunk.set_block(placement.chunk_x, placement.height + y, placement.chunk_z, state);
         }
      }
   });
}

void ChunkPlacements::populate_neighbour(Chunk &chunk, game::ChunkPosition pos)
{
   std::for_each(m_placements.begin(), m_placements.end(), [&chunk, pos](auto &pair) {
      Placement &placement = pair.second;
      auto &obj            = ObjectRepository::the().get_object(placement.object_id, placement.object_seed);

      auto x = placement.chunk_x + (pos.x - chunk.m_pos_x) * 16;
      auto z = placement.chunk_z + (pos.z - chunk.m_pos_z) * 16;

      if (x < 0 || x >= 16 || z < 0 || z >= 16)
         return;
      for (int y = 0; y < obj.height(); ++y) {
         auto state = obj.block_at(placement.x, y, placement.z);
         if (state != 0) {
            chunk.set_block(x, placement.height + y, z, state);
         }
      }
   });
}

}// namespace minecpp::world::population