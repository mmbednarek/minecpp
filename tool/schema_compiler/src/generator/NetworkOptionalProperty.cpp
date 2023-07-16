#include "NetworkOptionalProperty.h"
#include "../IGenerator.h"
#include "NetworkDeserializeContext.h"
#include "NetworkSerializeContext.h"

using mb::codegen::assign;
using mb::codegen::binary_operator;
using mb::codegen::call;
using mb::codegen::deref;
using mb::codegen::for_statement;
using mb::codegen::if_statement;
using mb::codegen::method_call;
using mb::codegen::ranged_for_statement;
using mb::codegen::raw;
using mb::codegen::return_statement;
using mb::codegen::statement;
using mb::codegen::switch_statement;

namespace minecpp::tool::schema_compiler::generator {

void NetworkOptionalProperty::write_serializer(NetworkSerializeContext &ctx)
{
   const auto subtype = ctx.type().template_arg_at(0);
   generator_verify(subtype.has_value(), ctx.type().line(), ctx.type().column(),
                    "optional type requires a template argument");

   bool has_condition = ctx.annotations().has_key("Condition");

   ctx << if_statement(
           method_call(ctx.source_property(), "has_value"),
           // if (field.has_value(..))
           [&subtype, &ctx, has_condition](statement::collector &col) {
              if (not has_condition) {
                 col << raw("writer.write_byte(1)");
              }
              ctx.write_serializer(*subtype, deref(ctx.source_property()), ctx.unique_name("_opt_value"),
                                   col);
           },
           // else
           [has_condition](statement::collector &col) {
              if (not has_condition) {
                 col << raw("writer.write_byte(0)");
              }
           });
}

void NetworkOptionalProperty::write_deserializer(NetworkDeserializeContext &ctx)
{
   ctx.ensure_destination();

   const auto subtype = ctx.type().template_arg_at(0);
   generator_verify(subtype.has_value(), ctx.type().line(), ctx.type().column(),
                    "optional type requires a template argument");

   auto has_value_name = ctx.unique_name("_has_value");
   if (ctx.annotations().has_key("Condition")) {
      ctx << raw("const auto {} = {}", has_value_name, ctx.annotations().value_at("Condition"));
   } else {
      ctx << raw("const auto {} = reader.read_byte()", has_value_name);
   }

   ctx << if_statement(raw(has_value_name), [&subtype, &ctx](statement::collector &col) {
      ctx.write_deserializer(*subtype, col, ctx.unique_name("_opt_value"), ctx.destination());
   });
}

}// namespace minecpp::tool::schema_compiler::generator
