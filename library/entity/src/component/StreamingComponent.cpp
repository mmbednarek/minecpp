#include <algorithm>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/StreamingComponent.h>
#include <minecpp/game/Game.h>
#include <minecpp/math/Vector2.h>

namespace {

int pow2(int value)
{
   return value * value;
}

int distance_squared(const minecpp::math::Vector2i &lhs, const minecpp::math::Vector2i &rhs)
{
   return (lhs - rhs).transform(pow2).sum();
}

}// namespace

namespace minecpp::entity::component {

StreamingComponent::StreamingComponent(int view_distance) :
    m_view_distance(view_distance),
    m_view_distance_squared(view_distance * view_distance)
{
}

void StreamingComponent::on_attached(game::Entity &entity)
{
   if (entity.has_component<Location>()) {
      auto &location        = entity.component<Location>();
      m_last_chunk_position = game::ChunkPosition::from_position(location.position());

      entt::sink on_pos_sink{location.on_position_change};
      on_pos_sink.connect<&StreamingComponent::on_position_change>(this);
   }
}

mb::result<mb::empty> StreamingComponent::send_all_visible_chunks(game::IWorld &world,
                                                                  game::PlayerId player_id)
{
   std::vector<game::ChunkPosition> chunks_to_load;

   for (auto z{-m_view_distance}; z < m_view_distance; ++z) {
      for (auto x{-m_view_distance}; x < m_view_distance; ++x) {
         math::Vector2i offset{x, z};

         if (offset.transform(pow2).sum() > m_view_distance_squared)
            continue;

         chunks_to_load.emplace_back(m_last_chunk_position.position + offset);
      }
   }

   // sort so chunks closer to the player would load first
   std::sort(chunks_to_load.begin(), chunks_to_load.end(),
             [this](const game::ChunkPosition &lhs, const game::ChunkPosition &rhs) {
                return distance_squared(m_last_chunk_position.position, lhs.position) <
                       distance_squared(m_last_chunk_position.position, rhs.position);
             });

   if (auto res = world.add_refs(player_id, chunks_to_load); !res.ok()) {
      return std::move(res.err());
   }

   world.dispatcher().update_chunk_position(player_id, m_last_chunk_position);

   for (const auto &chunk_pos : chunks_to_load) {
      world.send_chunk_to_player(player_id, chunk_pos);
   }

   return mb::ok;
}

void StreamingComponent::on_position_change(game::IWorld &world, game::Entity &entity,
                                            const math::Vector3 &old_position,
                                            const math::Vector3 &new_position)
{
   std::lock_guard<std::mutex> lock(m_mutex);

   if (not entity.has_component<Player>())
      return;

   auto next_chunk_pos = game::ChunkPosition::from_position(new_position);
   if (next_chunk_pos.position == m_last_chunk_position.position)
      return;

   std::vector<game::ChunkPosition> chunks_to_load;// TODO: pre alloc
   std::vector<game::ChunkPosition> chunks_to_free;// TODO: pre alloc

   for (int z = -m_view_distance - 1; z < m_view_distance + 1; ++z) {
      for (int x = -m_view_distance - 1; x < m_view_distance + 1; ++x) {
         math::Vector2i offset{x, z};
         if (offset.transform(pow2).sum() > m_view_distance_squared)
            continue;

         auto next_chunk_pos_off = next_chunk_pos.position + offset;
         auto last_chunk_pos_off = m_last_chunk_position.position + offset;

         auto next_off_to_last = distance_squared(next_chunk_pos_off, m_last_chunk_position.position);
         auto last_off_to_next = distance_squared(last_chunk_pos_off, next_chunk_pos.position);

         if (next_off_to_last >= m_view_distance_squared) {
            // new chunks to load
            chunks_to_load.emplace_back(next_chunk_pos_off);
         }
         if (last_off_to_next >= m_view_distance_squared) {
            // chunks to free
            chunks_to_free.emplace_back(last_chunk_pos_off);
         }
      }
   }

   m_last_chunk_position = next_chunk_pos;

   auto player_id = entity.component<Player>().id;
   world.dispatcher().update_chunk_position(player_id, m_last_chunk_position);

   if (!chunks_to_free.empty()) {
      if (auto res = world.free_refs(player_id, chunks_to_free); !res.ok()) {
         return;
      }
      for (const auto &pos : chunks_to_free) {
         world.dispatcher().unload_chunk(player_id, pos);
      }
   }

   if (!chunks_to_load.empty()) {
      // sort so chunks closer to the player would load first
      std::sort(chunks_to_load.begin(), chunks_to_load.end(),
                [next_chunk_pos](const game::ChunkPosition &lhs, const game::ChunkPosition &rhs) {
                   return distance_squared(next_chunk_pos.position, lhs.position) <
                          distance_squared(next_chunk_pos.position, rhs.position);
                });
      if (auto res = world.add_refs(player_id, chunks_to_load); !res.ok()) {
         return;
      }

      for (const auto &chunk_pos : chunks_to_load) {
         // TODO: Add chunk
         world.send_chunk_to_player(player_id, chunk_pos);
      }
   }

   auto new_visible_entities = world.entity_system().list_entities_in_view_distance(new_position);
   std::sort(new_visible_entities.begin(), new_visible_entities.end());

   auto new_it = new_visible_entities.begin();
   auto old_it = m_visible_entities.begin();

   while (new_it != new_visible_entities.end() or old_it != m_visible_entities.end()) {
      if (new_it == new_visible_entities.end() or (old_it != m_visible_entities.end() and *old_it < *new_it))
      {
        world.dispatcher().remove_entity_for_player(player_id, *old_it);
        auto other_entity = world.entity_system().entity(*old_it);
        if (other_entity.has_component<Player>()) {
           world.dispatcher().remove_entity_for_player(other_entity.component<Player>().id, entity.id());
        }

        ++old_it;
         continue;
      }

      if (old_it == m_visible_entities.end() or *new_it < *old_it)
      {
         auto other_entity = world.entity_system().entity(*new_it);
         if (other_entity.has_component<Player>()) {
           if (other_entity.component<Player>().id == player_id) {
              ++new_it;
              continue;
           }

            world.dispatcher().spawn_player_for_player(player_id, other_entity.component<Player>().id, other_entity.id());
            world.dispatcher().spawn_player_for_player(other_entity.component<Player>().id, player_id, entity.id());
         } else {
            world.dispatcher().spawn_entity_for_player(player_id, other_entity.id());
         }

         ++new_it;
         continue;
      }

      if (old_it != m_visible_entities.end())
         ++old_it;
      if (new_it != new_visible_entities.end())
         ++new_it;
   }

   m_visible_entities = new_visible_entities;
}

}// namespace minecpp::entity::component
