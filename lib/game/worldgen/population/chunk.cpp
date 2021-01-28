#include <minecpp/game/worldgen/population/chunk.h>
#include <minecpp/game/worldgen/population/object.h>
#include <minecpp/game/block/position.h>
#include <minecpp/random/java_random.h>

namespace Game::WorldGen::Population {

ChunkPlacements::ChunkPlacements(Game::Chunk &chunk, std::uint64_t seed) : m_seed(seed) {
   prepare_chunk(chunk);
}

Placement ChunkPlacements::get_placement(int x, int z) {
   auto p = m_placements.find(Block::Position(x, 0, z).as_long());
   if (p == m_placements.end()) {
      return Placement{
              .object_id = -1,
      };
   }
   return p->second;
}

void ChunkPlacements::prepare_chunk(Game::Chunk &chunk) {
   Rand::JavaRandom rand(m_seed);
   auto chunk_pos = chunk.pos();

   for (int _z = 0; _z < 16; ++_z) {
      for (int _x = 0; _x < 16; ++_x) {
         auto hash = chunk_pos.block_at(_x, 0, _z).as_long();
         if (m_placements.contains(hash)) {
            continue;
         }
         short height = chunk.height_at(_x, _z) + 1;
         if (height < 69 || height > 90)
            continue;

         std::uint32_t value = rand.next_int(10000);
         auto objid = find_object_id(value);
         if (objid >= 0) {
            put_object(chunk, objid, _x, height, _z);
         }
      }
   }
}

void ChunkPlacements::put_object(Game::Chunk &chunk, int id, int x, int y, int z) {
   if (id >= pop_objects.size()) {
      return;
   }
   const auto &obj = pop_objects[id];
   auto center = obj->center();

   std::uint16_t center_offset = z * 16 + x;
   if (center_offset > 255) {
      return;
   }

   for (int _z = -center.z; _z < obj->length() - center.z; ++_z) {
      for (int _x = -center.x; _x < obj->width() - center.x; ++_x) {
         auto hash = chunk.pos().block_at(x + _x, 0, z + _z).as_long();
         if (m_placements.contains(hash)) {
            return;
         }
      }
   }
   for (int _z = -center.z; _z < obj->length() - center.z; ++_z) {
      for (int _x = -center.x; _x < obj->width() - center.x; ++_x) {
         m_placements[chunk.pos().block_at(x + _x, 0, z + _z).as_long()] = Placement{.object_id = id, .x = static_cast<short>(_x + center.x), .z = static_cast<short>(_z + center.z), .chunk_x = static_cast<short>(x + _x), .chunk_z = static_cast<short>(z + _z), .height = y};
      }
   }
}

void ChunkPlacements::populate_chunk(Game::Chunk &chunk) {
   std::for_each(m_placements.begin(), m_placements.end(), [&chunk](auto &pair) {
      Placement &placement = pair.second;
     auto &obj = pop_objects[placement.object_id];
     if (placement.chunk_x < 0 || placement.chunk_x >= 16 || placement.chunk_z < 0 || placement.chunk_z >= 16)
        return;
     for (int y = 0; y < obj->height(); ++y) {
        auto state = obj->block_at(placement.x, y, placement.z);
        if (state != 0) {
           chunk.set_block(placement.chunk_x, placement.height + y, placement.chunk_z, state);
        }
     }
   });
}

void ChunkPlacements::populate_neighbour(Chunk &chunk, Block::ChunkPos pos) {
   std::for_each(m_placements.begin(), m_placements.end(), [&chunk, pos](auto &pair) {
     Placement &placement = pair.second;
     auto &obj = pop_objects[placement.object_id];

     auto x = placement.chunk_x + (pos.x - chunk.pos_x) * 16;
     auto z = placement.chunk_z + (pos.z - chunk.pos_z) * 16;

     if (x < 0 || x >= 16 || z < 0 || z >= 16)
        return;
     for (int y = 0; y < obj->height(); ++y) {
        auto state = obj->block_at(placement.x, y, placement.z);
        if (state != 0) {
           chunk.set_block(x, placement.height + y, z, state);
        }
     }
   });
}

}// namespace Game::WorldGen::Population