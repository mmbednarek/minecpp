#include "tracking.h"
#include "player.h"

namespace Game {

static Block::ChunkPos to_chunk_pos(Vec3 position) {
   return Block::ChunkPos{
       .x = position.x > 0.0 ? static_cast<int>(position.x / 16.0) : static_cast<int>(position.x / 16.0) - 1,
       .z = position.z > 0.0 ? static_cast<int>(position.z / 16.0) : static_cast<int>(position.z / 16.0) - 1,
   };
}

static inline int pow2(int a) { return a * a; }

static int dist_sq(Block::ChunkPos a, Block::ChunkPos b) { return pow2(a.x - b.x) + pow2(a.z - b.z); }

Tracking::Tracking(Vec3 position, int radius)
    : last_chunk_pos(to_chunk_pos(position)), radius_sq(radius * radius), move_dist_sq(radius * radius / 9),
      radius(radius) {}

void Tracking::on_movement(World &w, Player &p, Vec3 position) {
   auto next_chunk_pos = to_chunk_pos(position);
   if (next_chunk_pos == last_chunk_pos) {
      return; // no new chunks if didn't travel enough
   }

   std::vector<Block::ChunkPos> chunks_to_load; // TODO: pre alloc
   std::vector<Block::ChunkPos> chunks_to_free; // TODO: pre alloc

   for (int z = -radius; z < radius; ++z) {
      for (int x = -radius; x < radius; ++x) {
         auto offset = Block::ChunkPos{x, z};
         if (dist_sq(Block::ChunkPos{0, 0}, offset) > radius_sq) {
            continue;
         }

         auto next_chunk_pos_off = next_chunk_pos + offset;
         auto last_chunk_pos_off = last_chunk_pos + offset;

         auto next_off_to_last = dist_sq(next_chunk_pos_off, last_chunk_pos);
         auto last_off_to_next = dist_sq(last_chunk_pos_off, next_chunk_pos);

         if (next_off_to_last >= radius_sq) {
            // new chunks to load
            chunks_to_load.emplace_back(next_chunk_pos_off);
         }
         if (last_off_to_next >= radius_sq) {
            // chunks to free
            chunks_to_load.emplace_back(last_chunk_pos_off);
         }
      }
   }

   last_chunk_pos = next_chunk_pos;

   // sort so chunks closer to the player would load first
   std::sort(chunks_to_load.begin(), chunks_to_load.end(),
             [next_chunk_pos](const Block::ChunkPos &a, const Block::ChunkPos &b) {
                return dist_sq(next_chunk_pos, a) < dist_sq(next_chunk_pos, b);
             });

   w.free_refs(p.get_id(), chunks_to_free);
   w.add_refs(p.get_id(), chunks_to_load);
   w.notifier().load_terrain(p.get_id(), last_chunk_pos, chunks_to_load);
}

void Tracking::load_chunks(World &w, Player &p) {
   std::vector<Block::ChunkPos> chunks_to_load; // TODO: pre alloc

   for (int z = -radius; z < radius; ++z) {
      for (int x = -radius; x < radius; ++x) {
         auto offset = Block::ChunkPos{x, z};
         if (dist_sq(Block::ChunkPos{0, 0}, offset) <= radius_sq) {
            chunks_to_load.emplace_back(last_chunk_pos + offset);
         }
      }
   }

   // sort so chunks closer to the player would load first
   std::sort(chunks_to_load.begin(), chunks_to_load.end(),
             [chunk_pos = this->last_chunk_pos](const Block::ChunkPos &a, const Block::ChunkPos &b) {
                return dist_sq(chunk_pos, a) < dist_sq(chunk_pos, b);
             });

   w.add_refs(p.get_id(), chunks_to_load);
   w.notifier().load_terrain(p.get_id(), last_chunk_pos, chunks_to_load);
}

} // namespace Game
