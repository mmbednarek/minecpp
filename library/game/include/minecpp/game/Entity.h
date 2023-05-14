#pragma once

#include "Concepts.hpp"
#include "Entt.hpp"
#include "Types.hpp"
#include <minecpp/math/Vector3.h>

namespace minecpp::game {

class Entity
{
 public:
   Entity(entt::registry &registry, game::EntityId id);

   template<typename TComponent, typename... TArgs>
   void add_component(TArgs &&...args)
   {
      m_registry.emplace<TComponent>(m_entity, std::forward<TArgs>(args)...);

      if constexpr (IsAttachable<TComponent>) {
         m_registry.get<TComponent>(m_entity).on_attached(*this);
      }
   }

   template<typename TComponent>
   [[nodiscard]] bool has_component() const
   {
      return m_registry.all_of<TComponent>(m_entity);
   }

   template<typename TComponent>
   TComponent &component() const
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
   void serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const;
   void on_killed(IWorld &world);
   void on_attached_to_world(IWorld &world, const math::Vector3 &position, const math::Vector3 &extent);

   [[nodiscard]] game::EntityId id() const;
   [[nodiscard]] bool is_valid() const;

 private:
   entt::entity m_entity;
   entt::registry &m_registry;
};

struct Movement
{
   math::Vector3s movement;

   [[nodiscard]] static Movement from_vector3(const math::Vector3 &position);
   [[nodiscard]] math::Vector3 to_vector3() const;
};

}// namespace minecpp::game