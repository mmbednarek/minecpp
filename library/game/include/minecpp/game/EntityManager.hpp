#ifndef MINECPP_ENTITYMANAGER_HPP
#define MINECPP_ENTITYMANAGER_HPP
#include "entity/Entity.h"
#include "Game.h"

namespace minecpp::game {

class EntityManager
{
 public:
   virtual ~EntityManager() noexcept = default;

   virtual EntityId spawn(entity::Entity entity)                              = 0;
   [[nodiscard]] virtual mb::result<entity::Entity &> get_entity(EntityId id) = 0;
   [[nodiscard]] virtual mb::emptyres remove_entity(game::EntityId id) = 0;
};

}// namespace minecpp::game

#endif//MINECPP_ENTITYMANAGER_HPP
