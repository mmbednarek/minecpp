#pragma once

#include "INetworkProperty.hpp"

namespace minecpp::tool::schema_compiler::generator {

class NetworkMapProperty : public INetworkProperty
{
 public:
   void write_serializer(NetworkSerializeContext &ctx) override;
   void write_deserializer(NetworkDeserializeContext &ctx) override;
};

}// namespace minecpp::tool::schema_compiler::generator
