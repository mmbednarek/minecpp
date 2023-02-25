#pragma once
#include <minecpp/game/Game.h>
#include <minecpp/game/IWorld.h>

namespace minecpp::entity::component {

class StreamingComponent
{
 public:
   explicit StreamingComponent(int view_distance);

   void on_attached(game::Entity &entity);

   mb::result<mb::empty> send_all_visible_chunks(game::IWorld &world, game::PlayerId player_id);
   void on_position_change(game::IWorld &world, game::Entity &entity, const math::Vector3 &old_position,
                           const math::Vector3 &new_position);

 private:
   std::mutex m_mutex{};
   game::ChunkPosition m_last_chunk_position{};
   int m_view_distance{};
   int m_view_distance_squared{};
};

}// namespace minecpp::entity::component