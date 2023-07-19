#include "NetworkMapProperty.h"
#include "../IGenerator.h"
#include "NetworkDeserializeContext.h"
#include "NetworkSerializeContext.h"

#include <mb/codegen/lambda.h>

using mb::codegen::assign;
using mb::codegen::binary_operator;
using mb::codegen::call;
using mb::codegen::for_statement;
using mb::codegen::if_statement;
using mb::codegen::lambda;
using mb::codegen::method_call;
using mb::codegen::ranged_for_statement;
using mb::codegen::raw;
using mb::codegen::return_statement;
using mb::codegen::statement;
using mb::codegen::switch_statement;

namespace minecpp::tool::schema_compiler::generator {

void NetworkMapProperty::write_serializer(NetworkSerializeContext &ctx)
{
   const auto key_type   = ctx.type().template_arg_at(0);
   const auto value_type = ctx.type().template_arg_at(1);
   generator_verify(key_type.has_value() && value_type.has_value(), ctx.type().line(), ctx.type().column(),
                    "map type requires two template argument");

   bool has_terminate_on = ctx.annotations().has_key("TerminateOn");

   if (not has_terminate_on) {
      ctx << call("writer.write_varint",
                  call("static_cast<std::int32_t>", method_call(ctx.source_property(), "size")));
   }

   auto key_name   = ctx.unique_name("_key");
   auto value_name = ctx.unique_name("_value");

   ctx << ranged_for_statement(
           "const auto", fmt::format("&[{}, {}]", key_name, value_name), ctx.source_property(),
           [&ctx, &key_type, &value_type, &key_name, &value_name](statement::collector &col) {
              ctx.write_serializer(*key_type, raw(key_name), key_name, col);
              ctx.write_serializer(*value_type, raw(value_name), value_name, col);
           });

   if (has_terminate_on) {
      ctx.write_serializer(*key_type, raw(ctx.annotations().value_at("TerminateOn")), key_name,
                           ctx.collector());
   }
}

void NetworkMapProperty::write_deserializer(NetworkDeserializeContext &ctx)
{
   ctx.ensure_destination();

   const auto key_type   = ctx.type().template_arg_at(0);
   const auto value_type = ctx.type().template_arg_at(1);
   generator_verify(key_type.has_value() && value_type.has_value(), ctx.type().line(), ctx.type().column(),
                    "map type requires two template argument");

   const auto has_terminate_on = ctx.annotations().has_key("TerminateOn");

   if (has_terminate_on) {
      ctx << for_statement(
              raw(""), raw(""), raw(""), [&key_type, &value_type, &ctx](statement::collector &col) {
                 auto key_expr = ctx.write_deserializer_to_var(*key_type, col, ctx.unique_name("_key"));
                 col << if_statement(
                         binary_operator(*key_expr, "==", raw(ctx.annotations().value_at("TerminateOn"))),
                         [](statement::collector &col) { col << raw("break"); });

                 auto value_expr = ctx.write_deserializer(*value_type, col, ctx.unique_name("_value"));
                 col << method_call(ctx.destination(), "emplace", *key_expr, *value_expr);
              });
   } else {
      auto map_size_name = ctx.unique_name("_map_size");
      ctx << raw("const auto {} = reader.read_varint()", map_size_name);
      ctx << call("std::generate_n",
                  call("std::inserter", ctx.destination(), method_call(ctx.destination(), "begin")),
                  raw("static_cast<std::size_t>({})", map_size_name),
                  lambda(
                          {},
                          [&key_type, &value_type, &ctx](statement::collector &col) {
                             auto key_expr = ctx.write_deserializer_to_var(*key_type, col, ctx.unique_name("_key"));
                             auto value_expr =
                                     ctx.write_deserializer(*value_type, col, ctx.unique_name("_value"));

                             col << return_statement(call("std::make_pair", *key_expr, *value_expr));
                          },
                          raw("&reader")));
   }
}

}// namespace minecpp::tool::schema_compiler::generator
