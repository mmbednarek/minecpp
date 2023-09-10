#pragma once

#include "EntityData.hpp"
#include "Entt.hpp"

#include "minecpp/math/Vector3.h"
#include "minecpp/proto/entity/Entity.pb.h"

namespace minecpp::game {

class Entity;
class IWorld;

template<typename T>
concept ProtoSerializable =
        requires(const T &t, proto::entity::Entity *proto_entity) { t.serialize_to_proto(proto_entity); };

template<typename T>
concept PlayerProtoSerializable = requires(const T &t, proto::entity::PlayerEntity *proto_entity) {
   t.serialize_player_to_proto(proto_entity);
};

template<typename T>
concept NetSerializable = requires(const T &t, NetworkEntity *net_entity) { t.serialize_to_net(net_entity); };

template<typename T>
concept NetPlayerSerializable =
        requires(const T &t, NetworkPlayer *net_player) { t.serialize_to_net_player(net_player); };

template<typename T>
concept IsAttachable = requires(T &t, Entity &entity) { t.on_attached(entity); };

template<typename T>
concept HasOnKilled = requires(T &t, IWorld *world, Entity *entity) { t.on_killed(world, entity); };

template<typename T>
concept HasOnAttachedToWorld =
        requires(T &t, IWorld *world, Entity *entity, math::Vector3 position, math::Vector3 extent) {
           t.on_attached_to_world(world, entity, position, extent);
        };

template<typename TComponent>
void register_component()
{
   using namespace entt::literals;

   auto meta_type = entt::meta<TComponent>();
   if constexpr (ProtoSerializable<TComponent>) {
      meta_type.template func<&TComponent::serialize_to_proto>("serialize_to_proto"_hs);
   }
   if constexpr (PlayerProtoSerializable<TComponent>) {
      meta_type.template func<&TComponent::serialize_player_to_proto>("serialize_player_to_proto"_hs);
   }
   if constexpr (NetSerializable<TComponent>) {
      meta_type.template func<&TComponent::serialize_to_net>("serialize_to_net"_hs);
   }
   if constexpr (NetPlayerSerializable<TComponent>) {
      meta_type.template func<&TComponent::serialize_to_net_player>("serialize_to_net_player"_hs);
   }
   if constexpr (game::HasOnKilled<TComponent>) {
      meta_type.template func<&TComponent::on_killed>("on_killed"_hs);
   }
   if constexpr (game::HasOnAttachedToWorld<TComponent>) {
      meta_type.template func<&TComponent::on_attached_to_world>("on_attached_to_world"_hs);
   }
}

}// namespace minecpp::game