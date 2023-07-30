#include "NetworkBasicProperty.h"
#include "NetworkDeserializeContext.h"
#include "NetworkSerializeContext.h"

#include <mb/codegen/expression.h>

using mb::codegen::call;

namespace minecpp::tool::schema_compiler::generator {

NetworkBasicProperty::NetworkBasicProperty(std::string_view serialize_call,
                                           std::string_view deserialize_call) :
    m_serialize_call(std::string{serialize_call}),
    m_deserialize_call(std::string{deserialize_call})
{
}

void NetworkBasicProperty::write_serializer(NetworkSerializeContext &ctx)
{
   ctx << call(m_serialize_call, ctx.source_property());
}

void NetworkBasicProperty::write_deserializer(NetworkDeserializeContext &ctx)
{
   ctx.assign_expression(call(m_deserialize_call));
}

}// namespace minecpp::tool::schema_compiler::generator
