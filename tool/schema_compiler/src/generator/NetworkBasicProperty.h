#pragma once

#include "INetworkProperty.hpp"

#include <string>
#include <string_view>

namespace minecpp::tool::schema_compiler::generator {

class NetworkBasicProperty : public INetworkProperty
{
 public:
   NetworkBasicProperty(std::string_view serialize_call, std::string_view deserialize_call);

   void write_serializer(NetworkSerializeContext &ctx) override;
   void write_deserializer(NetworkDeserializeContext &ctx) override;

 private:
   std::string m_serialize_call;
   std::string m_deserialize_call;
};

}// namespace minecpp::tool::schema_compiler::generator
