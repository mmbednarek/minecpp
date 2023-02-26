#pragma once
#include "Game.h"
#include <entt/entt.hpp>
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::game {

class Entity;

template<typename T>
concept ProtoSerializable =
        requires(const T &t, proto::entity::v1::Entity *proto_entity) { t.serialize_to_proto(proto_entity); };

template<typename T>
concept PlayerProtoSerializable = requires(const T &t, proto::entity::v1::PlayerEntity *proto_entity) {
                                     t.serialize_player_to_proto(proto_entity);
                                  };

template<typename T>
concept IsAttachable = requires(T &t, Entity &entity) { t.on_attached(entity); };

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
}

}// namespace minecpp::game