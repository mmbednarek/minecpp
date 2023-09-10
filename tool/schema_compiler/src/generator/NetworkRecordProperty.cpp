#include "NetworkRecordProperty.h"
#include "../IGenerator.h"
#include "NetworkDeserializeContext.h"
#include "NetworkSerializeContext.h"

using mb::codegen::assign;
using mb::codegen::binary_operator;
using mb::codegen::call;
using mb::codegen::for_statement;
using mb::codegen::if_statement;
using mb::codegen::method_call;
using mb::codegen::ranged_for_statement;
using mb::codegen::raw;
using mb::codegen::return_statement;
using mb::codegen::statement;
using mb::codegen::switch_statement;

namespace minecpp::tool::schema_compiler::generator {

void NetworkRecordProperty::write_serializer(NetworkSerializeContext &ctx)
{
   auto generator = ctx.type_generator();
   if (generator == g_network_generator_name) {
      ctx << method_call(ctx.source_property(), "serialize", raw("writer"));
      return;
   }
   if (generator == g_nbt_generator_name) {
      ctx << method_call(ctx.source_property(), "serialize", raw("writer.raw_stream()"), raw("\"\""));
      return;
   }

   generator_verify(false, ctx.type().line(), ctx.type().column(), "unknown generator: {}", generator);
}

void NetworkRecordProperty::write_deserializer(NetworkDeserializeContext &ctx)
{
   auto generator = ctx.type_generator();
   if (generator == g_network_generator_name) {
      if (ctx.annotations().has_key("Bind")) {
         ctx.assign_expression(
                 raw("{}::deserialize(reader, {})", ctx.type_name(), ctx.annotations().value_at("Bind")));
      } else {
         ctx.assign_expression(raw("{}::deserialize(reader)", ctx.type_name()));
      }
      return;
   }
   if (generator == g_nbt_generator_name) {
      ctx.assign_expression(raw("{}::deserialize(reader.raw_stream())", ctx.type_name()));
      return;
   }

   generator_verify(false, ctx.type().line(), ctx.type().column(), "unknown generator: {}", generator);
}

}// namespace minecpp::tool::schema_compiler::generator
