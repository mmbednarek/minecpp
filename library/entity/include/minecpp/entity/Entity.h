#pragma once

#include "Concepts.h"
#include <entt/entt.hpp>
#include <minecpp/game/Game.h>
#include <minecpp/math/Vector3.h>

namespace minecpp::entity {

class Entity
{
 public:
   Entity(entt::registry &registry, game::EntityId id);

   [[nodiscard]] math::Vector3 position() const;

   template<typename TComponent, typename... TArgs>
   void add_component(TArgs &&...args)
   {
      m_registry.emplace<TComponent>(m_entity, std::forward<TArgs>(args)...);
      if constexpr (HasOnAttached<TComponent>) {
         m_registry.get<TComponent>(m_entity).on_attached();
      }
   }

   template<typename TComponent>
   TComponent &component()
   {
      return m_registry.get<TComponent>(m_entity);
   }

   template<typename TCallback>
   void for_each_component(TCallback &&callback) const
   {
      for (auto &&curr : m_registry.storage()) {
         if (not curr.second.contains(m_entity))
            continue;

         auto meta_type = entt::resolve(curr.first);
         if (not meta_type)
            continue;

         auto meta_obj = meta_type.from_void(curr.second.get(m_entity));
         callback(meta_obj);
      }
   }

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;

   [[nodiscard]] game::EntityId id() const;

 private:
   entt::entity m_entity;
   entt::registry &m_registry;
};

}// namespace minecpp::entity