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

   for (int z = 0; z < 16; ++z) {
      for (int x = 0; x < 16; ++x) {
         auto hash = chunk_pos.block_at(x, 0, z).as_long();
         if (m_placements.contains(hash)) {
            continue;
         }
         auto height = chunk.height_at(x, z) + 1;
         if (height < 65 || height > 86)
            continue;

         auto value     = rand.next_int(10000);
         auto object_id = ObjectRepository::the().find_object_id(value);
         put_object(chunk, static_cast<int>(object_id), {x, height, z});
      }
   }
}

void ChunkPlacements::put_object(Chunk &chunk, int id, game::BlockPosition position)
{
   if (id < 0)
      return;
   unsigned object_seed = rand();// TODO: Replace with good random

   auto obj    = ObjectRepository::the().get_object(static_cast<std::size_t>(id), object_seed);
   auto center = obj->center();

   auto center_offset = position.z * 16 + position.x;
   if (center_offset > 255) {
      return;
   }

   for (int z = -center.z; z < obj->length() - center.z; ++z) {
      for (int x = -center.x; x < obj->width() - center.x; ++x) {
         auto hash = chunk.pos().block_at(position.x + x, 0, position.z + z).as_long();
         if (m_placements.contains(hash)) {
            return;
         }
      }
   }

   for (int z = -center.z; z < obj->length() - center.z; ++z) {
      for (int x = -center.x; x < obj->width() - center.x; ++x) {
         m_placements[chunk.pos().block_at(position.x + x, 0, position.z + z).as_long()] =
                 Placement{.object_id   = id,
                           .object_seed = object_seed,
                           .x           = static_cast<short>(x + center.x),
                           .z           = static_cast<short>(z + center.z),
                           .chunk_x     = static_cast<short>(position.x + x),
                           .chunk_z     = static_cast<short>(position.z + z),
                           .height      = static_cast<short>(position.y)};
      }
   }
}

void ChunkPlacements::populate_chunk(Chunk &chunk)
{
   for (auto &[_, placement] : m_placements) {
      auto obj = ObjectRepository::the().get_object(static_cast<mb::size>(placement.object_id),
                                                    placement.object_seed);

      if (placement.chunk_x < 0 || placement.chunk_x >= 16 || placement.chunk_z < 0 ||
          placement.chunk_z >= 16)
         continue;

      for (int y = 0; y < obj->height(); ++y) {
         auto state = obj->block_at(placement.x, y, placement.z);
         if (state != 0) {
            chunk.set_block(game::BlockPosition{placement.chunk_x, placement.height + y, placement.chunk_z},
                            static_cast<game::BlockStateId>(state));
         }
      }
   }
}

void ChunkPlacements::populate_neighbour(Chunk &chunk, game::ChunkPosition pos)
{
   for (auto &[_, placement] : m_placements) {
      auto obj = ObjectRepository::the().get_object(static_cast<mb::size>(placement.object_id),
                                                    placement.object_seed);

      game::BlockPosition position{};

      position.x = placement.chunk_x + (pos.x - chunk.pos().x) * 16;
      position.z = placement.chunk_z + (pos.z - chunk.pos().z) * 16;

      if (position.x < 0 || position.x >= 16 || position.z < 0 || position.z >= 16)
         continue;

      for (int y = 0; y < obj->height(); ++y) {
         position.y = placement.height + y;
         auto state = obj->block_at(placement.x, y, placement.z);
         if (state != 0) {
            chunk.set_block(position, static_cast<game::BlockStateId>(state));
         }
      }
   }
}

}// namespace minecpp::world::population