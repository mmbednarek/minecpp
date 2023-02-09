#pragma once
#include <map>
#include <mb/result.h>
#include <minecpp/game/entity/Entity.h>
#include <minecpp/game/EntityManager.hpp>

namespace minecpp::service::engine {

using minecpp::game::entity::Entity;

class EntityManager : public game::EntityManager
{
 public:
   using Storage  = std::map<game::EntityId, Entity>;
   using Iterator = Storage::iterator;

   game::EntityId spawn(Entity e) override;
   mb::result<Entity &> get_entity(game::EntityId id) override;
   mb::emptyres remove_entity(game::EntityId id) override;
   mb::size total_count();

   [[nodiscard]] Iterator begin();
   [[nodiscard]] Iterator end();

 private:
   Storage m_entities;
   game::EntityId m_top_entity_id;
};

}// namespace minecpp::service::engine
