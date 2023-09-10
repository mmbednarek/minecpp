#pragma once

#include "Health.h"
#include "Location.h"

#include "minecpp/game/Entity.h"
#include "minecpp/game/EntityData.hpp"
#include "minecpp/game/IWorld.hpp"
#include "minecpp/game/Team.h"

#include <optional>

namespace minecpp::entity::component {

class Totem
{
 public:
   using Self = Totem;

   explicit Totem(game::Team team);

   void on_attached(game::Entity &entity);

   void serialize_to_net(game::NetworkEntity *net_entity) const;
   void on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity);
   void on_player_move(game::IWorld &world, game::Entity &entity, const math::Vector3 &old_position,
                       const math::Vector3 &new_position);
   void on_player_dead(game::IWorld &world, game::Entity &entity, const game::Damage &damage);

   void detach(game::IWorld &world, game::Entity &entity);

   [[nodiscard]] game::Team team() const;

 private:
   static std::optional<game::Team> base_from_position(const math::Vector3 &position);

   mb::u32 m_entity_type_id{78};
   game::EntityId m_entity_id{};
   Location::BeginIntersect::OptSink<Self> m_intersect_sink;
   Location::PositionChange::OptSink<Self> m_position_change_sink;
   Health::Dead::OptSink<Self> m_dead_sink;
   bool m_is_attached{false};
   bool m_is_moved{false};
   game::Team m_team;
};

}// namespace minecpp::entity::component
