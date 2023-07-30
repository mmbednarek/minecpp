#include "NetworkExternProperty.h"
#include "../IGenerator.h"
#include "NetworkDeserializeContext.h"
#include "NetworkSerializeContext.h"

namespace minecpp::tool::schema_compiler::generator {

void NetworkExternProperty::write_serializer(NetworkSerializeContext &ctx)
{
   using mb::codegen::call;
   using mb::codegen::raw;

   auto symbol = ctx.symbol();
   generator_verify(symbol.annotations.has_key("Write"), ctx.type().line(), ctx.type().column(),
                    "extern type is missing Write field");

   ctx << call(symbol.annotations.value_at("Write"), raw("writer"), ctx.source_property());
}

void NetworkExternProperty::write_deserializer(NetworkDeserializeContext &ctx)
{
   using mb::codegen::call;
   using mb::codegen::raw;

   auto symbol = ctx.symbol();
   generator_verify(symbol.annotations.has_key("Read"), ctx.type().line(), ctx.type().column(),
                    "extern type is missing Read field");

   ctx.assign_expression(call(symbol.annotations.value_at("Read"), raw("reader")));
}

}// namespace minecpp::tool::schema_compiler::generator
