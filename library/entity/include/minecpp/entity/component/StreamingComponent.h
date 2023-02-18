#pragma once
#include <minecpp/game/World.h>
#include <minecpp/game/Game.h>

namespace minecpp::entity::component {

class StreamingComponent
{
   std::mutex m_mutex{};
   game::ChunkPosition m_last_chunk_position{};
   int m_view_distance{};
   int m_view_distance_squared{};

 public:
   explicit StreamingComponent(int view_distance);

   void on_attached(game::Entity &entity);

   mb::result<mb::empty> send_all_visible_chunks(game::World &world, game::PlayerId player_id);
   void on_position_change(game::World &world, game::Entity entity, const math::Vector3 &old_position,
                           const math::Vector3 &new_position);
};

}