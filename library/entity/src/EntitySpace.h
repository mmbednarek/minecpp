#pragma once
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <minecpp/game/Game.h>
#include <minecpp/math/Vector3.h>
#include <shared_mutex>

BOOST_GEOMETRY_REGISTER_POINT_3D(::minecpp::math::Vector3, double, boost::geometry::cs::cartesian,
                                 m_storage[0], m_storage[1], m_storage[2])

namespace minecpp::entity {

using Box = boost::geometry::model::box<math::Vector3>;

class EntitySpace
{
 public:
   using IndexedPoint = std::pair<Box, game::EntityId>;
   using Storage      = boost::geometry::index::rtree<IndexedPoint, boost::geometry::index::rstar<16, 4>>;

   void remove_entity(game::EntityId entity_id, const math::Vector3 &position, const math::Vector3 &extent);
   void register_entity(game::EntityId entity_id, math::Vector3 position, math::Vector3 extent);
   void update_position(game::EntityId entity_id, math::Vector3 old_position, math::Vector3 new_position,
                        math::Vector3 extent);
   std::vector<game::EntityId> list_entities_in(math::Vector3 min, math::Vector3 max);
   std::vector<game::EntityId> list_entities_intersecting_with(math::Vector3 min, math::Vector3 max);
   [[nodiscard]] std::optional<game::EntityId> find_nearest(math::Vector3 position);

 private:
   Storage m_storage;
   std::shared_mutex m_mutex;
};

}// namespace minecpp::entity
