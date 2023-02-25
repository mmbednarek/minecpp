#include "EntitySpace.h"

namespace minecpp::entity {

namespace geo = boost::geometry::index;

namespace {
Box make_entity_hitbox(math::Vector3 position, math::Vector3 extent)
{
   auto min = position - math::Vector3{extent.x(), 0, extent.z()} / 2.0;
   auto max = min + extent;
   return {min, max};
}
}// namespace

void EntitySpace::register_entity(game::EntityId entity_id, math::Vector3 position, math::Vector3 extent)
{
   std::unique_lock lk{m_mutex};
   m_storage.insert({make_entity_hitbox(position, extent), entity_id});
}

void EntitySpace::update_position(game::EntityId entity_id, math::Vector3 old_position,
                                  math::Vector3 new_position, math::Vector3 extent)
{
   std::unique_lock lk{m_mutex};
   m_storage.remove({make_entity_hitbox(old_position, extent), entity_id});
   m_storage.insert({make_entity_hitbox(new_position, extent), entity_id});
}

std::optional<game::EntityId> EntitySpace::find_nearest(math::Vector3 position)
{
   std::shared_lock lk{m_mutex};
   auto result = m_storage.qbegin(geo::nearest(position, 1));
   if (result == m_storage.qend())
      return std::nullopt;
   return result->second;
}

std::vector<game::EntityId> EntitySpace::list_entities_in(math::Vector3 min, math::Vector3 max)
{
   std::shared_lock lk{m_mutex};
   std::vector<game::EntityId> result{};
   for (auto it = m_storage.qbegin(geo::within(Box{min, max})); it != m_storage.qend(); ++it)  {
      result.push_back(it->second);
   }
   return result;
}

std::vector<game::EntityId> EntitySpace::list_entities_intersecting_with(math::Vector3 min, math::Vector3 max)
{
   std::shared_lock lk{m_mutex};
   std::vector<game::EntityId> result{};
   for (auto it = m_storage.qbegin(geo::intersects(Box{min, max})); it != m_storage.qend(); ++it)  {
      result.push_back(it->second);
   }
   return result;
}

void EntitySpace::remove_entity(game::EntityId entity_id, const math::Vector3 &position,
                                const math::Vector3 &extent)
{
   std::unique_lock lk{m_mutex};
   m_storage.remove({make_entity_hitbox(position, extent), entity_id});
}

}// namespace minecpp::entity
