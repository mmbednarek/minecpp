#pragma once

namespace minecpp::tool::schema_compiler::generator {

class NetworkSerializeContext;
class NetworkDeserializeContext;

class INetworkProperty
{
 public:
   virtual ~INetworkProperty() = default;

   virtual void write_serializer(NetworkSerializeContext &ctx)     = 0;
   virtual void write_deserializer(NetworkDeserializeContext &ctx) = 0;
};

}// namespace minecpp::tool::schema_compiler::generator
