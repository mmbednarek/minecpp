#pragma once

#include <string>
#include <vector>
#include <chrono>

#include "minecpp/game/EntityData.hpp"
#include "minecpp/game/IDispatcher.hpp"
#include "minecpp/game/IEntitySystem.hpp"

namespace minecpp::entity::component {

class Player
{
 public:
   Player(const game::PlayerId &id, std::string name);

   void on_attached(game::Entity &entity);

   void serialize_to_net_player(game::NetworkPlayer *net_player) const;

   [[nodiscard]] game::PlayerId id() const;
   [[nodiscard]] const std::string &name() const;
   void refresh_visible_entities(game::IDispatcher &dispatcher, game::IEntitySystem &entity_system,
                                 const math::Vector3 &position);
   void init_visible_entities(game::IDispatcher &dispatcher, game::IEntitySystem &entity_system,
                              const math::Vector3 &position);
   void on_killed(game::IWorld *world, game::Entity *entity);
   void on_attached_to_world(game::IWorld *world, game::Entity *entity, const math::Vector3 &position,
                             const math::Vector3 &extent);

   [[nodiscard]] const std::vector<game::EntityId> &visible_entities() const;
   void add_visible_player_entity(game::IDispatcher &dispatcher, game::EntityId entity_id);
   void remove_visible_entity(game::IDispatcher &dispatcher, game::EntityId entity_id);

   void begin_use_item();
   std::chrono::steady_clock::duration end_use_item();

 private:
   game::PlayerId m_id;
   game::EntityId m_entity_id{};
   std::string m_name;
   std::vector<game::EntityId> m_visible_entities;
   std::mutex m_visible_entities_mutex;
   std::optional<std::chrono::steady_clock::time_point> m_started_using_item;
};

}// namespace minecpp::entity::component
