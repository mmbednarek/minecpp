#include "tracking.h"
#include "player.h"

namespace Game {

static inline int pow2(int a) { return a * a; }

static int dist_sq(Block::ChunkPos a, Block::ChunkPos b) { return pow2(a.x - b.x) + pow2(a.z - b.z); }

Tracking::Tracking(Vec3 position, int radius)
    : last_chunk_pos(position.flat() / 16.0), radius_sq(radius * radius), move_dist_sq(radius * radius / 9),
      radius(radius) {}

void Tracking::on_movement(World &w, Player &p, Vec3 position) {
   auto next_chunk_pos = (position.flat() / 16.0).truncate();
   if (distance(next_chunk_pos, last_chunk_pos) < 1.0) {
      return; // no new chunks if didn't travel enough
   }

   std::vector<Block::ChunkPos> chunks_to_load; // TODO: pre alloc
   std::vector<Block::ChunkPos> chunks_to_free; // TODO: pre alloc

   for (int z = -radius; z < radius; ++z) {
      for (int x = -radius; x < radius; ++x) {
         auto offset = Vec2(x, z);
         if (distance(Vec2(), offset) > radius) {
            continue;
         }

         auto next_chunk_pos_off = (next_chunk_pos + offset);
         auto last_chunk_pos_off = (last_chunk_pos + offset);

         auto next_off_to_last = distance(next_chunk_pos_off, last_chunk_pos);
         auto last_off_to_next = distance(last_chunk_pos_off, next_chunk_pos);

         if (next_off_to_last >= radius) {
            // new chunks to load
            chunks_to_load.emplace_back(next_chunk_pos_off);
         }
         if (last_off_to_next >= radius) {
            // chunks to free
            chunks_to_free.emplace_back(last_chunk_pos_off);
         }
      }
   }

   last_chunk_pos = next_chunk_pos;
   Block::ChunkPos chunk_pos(next_chunk_pos);

   if (!chunks_to_free.empty()) {
      auto res = w.free_refs(p.get_id(), chunks_to_free);
      if (!res.ok()) {
         return;
      }
   }

   if (!chunks_to_load.empty()) {
      // sort so chunks closer to the player would load first
      std::sort(chunks_to_load.begin(), chunks_to_load.end(),
                [chunk_pos](const Block::ChunkPos &a, const Block::ChunkPos &b) {
                   return dist_sq(chunk_pos, a) < dist_sq(chunk_pos, b);
                });
      w.add_refs(p.get_id(), chunks_to_load).unwrap();
      w.notifier().load_terrain(p.get_id(), chunk_pos, chunks_to_load);
   }
}

void Tracking::load_chunks(World &w, Player &p) {
   std::vector<Block::ChunkPos> chunks_to_load; // TODO: pre alloc
   Block::ChunkPos chunk_pos(last_chunk_pos);

   for (int z = -radius; z < radius; ++z) {
      for (int x = -radius; x < radius; ++x) {
         auto offset = Block::ChunkPos{x, z};
         if (dist_sq(Block::ChunkPos{0, 0}, offset) <= radius_sq) {
            chunks_to_load.emplace_back(chunk_pos + offset);
         }
      }
   }

   // sort so chunks closer to the player would load first
   std::sort(chunks_to_load.begin(), chunks_to_load.end(),
             [chunk_pos](const Block::ChunkPos &a, const Block::ChunkPos &b) {
                return dist_sq(chunk_pos, a) < dist_sq(chunk_pos, b);
             });

   w.add_refs(p.get_id(), chunks_to_load).unwrap();
   w.notifier().load_terrain(p.get_id(), chunk_pos, chunks_to_load);
}

} // namespace Game
