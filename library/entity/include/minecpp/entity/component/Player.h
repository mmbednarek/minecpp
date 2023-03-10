#pragma once
#include <minecpp/game/Game.h>
#include <minecpp/game/IDispatcher.hpp>
#include <minecpp/game/IEntitySystem.hpp>
#include <string>
#include <vector>

namespace minecpp::entity::component {

class Player
{
 public:
   Player(const game::PlayerId &id, std::string name);

   void on_attached(game::Entity &entity);

   void serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const;

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
   void add_visible_player_entity(game::IDispatcher &dispatcher, game::PlayerId player_id,
                                  game::EntityId entity_id);
   void remove_visible_entity(game::IDispatcher &dispatcher, game::EntityId entity_id);

 private:
   game::PlayerId m_id;
   game::EntityId m_entity_id{};
   std::string m_name;
   std::vector<game::EntityId> m_visible_entities;
   std::mutex m_visible_entities_mutex;
};

}// namespace minecpp::entity::component
