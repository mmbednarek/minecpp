#pragma once
#include <entt/entt.hpp>
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::entity {

template<typename T>
concept ProtoSerializable = requires(const T &t, proto::entity::v1::Entity *proto_entity) { t.serialize_to_proto(proto_entity); };

template<typename T>
concept HasOnAttached = requires(const T &t) { t.on_attached(); };

template<typename TComponent>
void register_component()
{
   using namespace entt::literals;

   auto meta_type = entt::meta<TComponent>();
   if constexpr (ProtoSerializable<TComponent>) {
      meta_type.template func<&TComponent::serialize_to_proto>("serialize_to_proto"_hs);
   }
}

}// namespace minecpp::entity