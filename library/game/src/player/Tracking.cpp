#include <algorithm>
#include <minecpp/game/player/Player.h>
#include <minecpp/game/player/Tracking.h>
#include <minecpp/game/World.h>
#include <minecpp/util/Vec.h>
#include <spdlog/spdlog.h>

namespace minecpp::game::player {

Tracking::Tracking(const util::Vec3 &position, int radius) :
    m_chunk_pos(game::ChunkPosition::from_position(position)),
    m_radius_sq(radius * radius),
    m_radius(radius)
{
}

template<typename T>
static constexpr auto pow2(T value)
{
   return value * value;
}

static int dist_sq(game::ChunkPosition a, game::ChunkPosition b)
{
   return pow2(a.x - b.x) + pow2(a.z - b.z);
}

mb::result<mb::empty> Tracking::load_chunks(game::World &w, Player &p)
{
   std::vector<game::ChunkPosition> chunks_to_load;// TODO: pre alloc

   for (int z = -m_radius; z < m_radius; ++z) {
      for (int x = -m_radius; x < m_radius; ++x) {
         auto offset = game::ChunkPosition(x, z);
         if (dist_sq(game::ChunkPosition{0, 0}, offset) <= m_radius_sq) {
            chunks_to_load.emplace_back(m_chunk_pos + offset);
         }
      }
   }

   // sort so chunks closer to the player would load first
   std::sort(chunks_to_load.begin(), chunks_to_load.end(),
             [this](const game::ChunkPosition &a, const game::ChunkPosition &b) {
                return dist_sq(m_chunk_pos, a) < dist_sq(m_chunk_pos, b);
             });

   if (auto res = w.add_refs(p.id(), chunks_to_load); !res.ok()) {
      return std::move(res.err());
   }
   w.notifier().load_terrain(p.id(), m_chunk_pos, chunks_to_load);
   return mb::ok;
}

void Tracking::on_movement(game::World &w, Player &p, util::Vec3 position)
{
   std::lock_guard<std::mutex> lock(m_mutex);
   auto next_chunk_pos = game::ChunkPosition::from_position(position);
   if (next_chunk_pos.x == m_chunk_pos.x && next_chunk_pos.z == m_chunk_pos.z) {
      return;
   }

   std::vector<game::ChunkPosition> chunks_to_load;// TODO: pre alloc
   std::vector<game::ChunkPosition> chunks_to_free;// TODO: pre alloc

   for (int z = -m_radius - 1; z < m_radius + 1; ++z) {
      for (int x = -m_radius - 1; x < m_radius + 1; ++x) {
         if ((pow2(x) + pow2(z)) > m_radius_sq) {
            continue;
         }

         auto offset = game::ChunkPosition(x, z);

         auto next_chunk_pos_off = (next_chunk_pos + offset);
         auto last_chunk_pos_off = (m_chunk_pos + offset);

         auto next_off_to_last = dist_sq(next_chunk_pos_off, m_chunk_pos);
         auto last_off_to_next = dist_sq(last_chunk_pos_off, next_chunk_pos);

         if (next_off_to_last >= m_radius_sq) {
            // new chunks to load
            chunks_to_load.emplace_back(next_chunk_pos_off);
         }
         if (last_off_to_next >= m_radius_sq) {
            // chunks to free
            chunks_to_free.emplace_back(last_chunk_pos_off);
         }
      }
   }

   spdlog::info("settings player chunk position to {} {}", next_chunk_pos.x, next_chunk_pos.z);
   m_chunk_pos = next_chunk_pos;

   if (!chunks_to_free.empty()) {
      if (auto res = w.free_refs(p.id(), chunks_to_free); !res.ok()) {
         return;
      }
      for (const auto &pos : chunks_to_free) {
         w.notifier().unload_chunk(p.id(), pos);
      }
   }

   if (!chunks_to_load.empty()) {
      // sort so chunks closer to the player would load first
      std::sort(chunks_to_load.begin(), chunks_to_load.end(),
                [next_chunk_pos](const game::ChunkPosition &a, const game::ChunkPosition &b) {
                   return dist_sq(next_chunk_pos, a) < dist_sq(next_chunk_pos, b);
                });
      if (auto res = w.add_refs(p.id(), chunks_to_load); !res.ok()) {
         return;
      }
      w.notifier().load_terrain(p.id(), next_chunk_pos, chunks_to_load);
   }
}

}// namespace minecpp::game::player