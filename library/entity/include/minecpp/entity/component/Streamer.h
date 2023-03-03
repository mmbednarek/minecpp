#pragma once
#include <minecpp/game/Game.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class Streamer
{
 public:
   explicit Streamer(int view_distance);

   void on_attached(game::Entity &entity);

   mb::result<mb::empty> send_all_visible_chunks(game::IWorld &world, game::PlayerId player_id);
   void on_position_change(game::IWorld &world, game::Entity &entity, const math::Vector3 &old_position,
                           const math::Vector3 &new_position);
   void tick(game::IWorld &world, game::Entity &entity, double delta_time);

 private:
   std::mutex m_mutex{};
   game::ChunkPosition m_last_chunk_position{};
   int m_view_distance{};
   int m_view_distance_squared{};
   std::vector<game::ChunkPosition> m_chunks_to_load{};
   double m_tick_sum{};
};

}// namespace minecpp::entity::component