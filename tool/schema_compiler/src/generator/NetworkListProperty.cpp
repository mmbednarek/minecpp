#include "NetworkListProperty.h"
#include "../IGenerator.h"
#include "NetworkSerializeContext.h"
#include "NetworkDeserializeContext.h"

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

void NetworkListProperty::write_serializer(NetworkSerializeContext &ctx)
{
   const auto subtype = ctx.type().template_arg_at(0);
   generator_verify(subtype.has_value(), ctx.type().line(), ctx.type().column(),
                    "list type requires a template argument");


   ctx << call("writer.write_varint",
               call("static_cast<std::int32_t>", method_call(ctx.source_property(), "size")));

   auto value_name = ctx.unique_name("_value");
   ctx << ranged_for_statement("const auto", fmt::format("&{}", value_name), ctx.source_property(),
                               [&subtype, &value_name, &ctx](statement::collector &col) {
                                  ctx.write_serializer(*subtype, raw(value_name), value_name, col);
                               });
}

void NetworkListProperty::write_deserializer(NetworkDeserializeContext &ctx)
{
   ctx.ensure_destination();

   const auto subtype = ctx.type().template_arg_at(0);

   generator_verify(subtype.has_value(), ctx.type().line(), ctx.type().column(),
                    "list type requires a template argument");

   auto size_name = ctx.unique_name("_size");

   ctx << raw("auto {} = reader.read_varint()", size_name);
   ctx << method_call(ctx.destination(), "resize", call("static_cast<std::size_t>", raw(size_name)));

   std::string lambda_captures;
   if (ctx.annotations().has_key("Capture")) {
      // Assume binding contains result
      lambda_captures = fmt::format("{}, &reader", ctx.annotations().value_at("Capture"));
   } else {
      lambda_captures = "&reader";
   }

   ctx << call("std::generate", method_call(ctx.destination(), "begin"),
               method_call(ctx.destination(), "end"),
               lambda(
                       {},
                       [&subtype, &ctx](statement::collector &col) {
                          auto result = ctx.write_deserializer(*subtype, col, ctx.unique_name("_result"));
                          col << return_statement(*result);
                       },
                       raw(lambda_captures)));
}

}// namespace minecpp::tool::schema_compiler::generator
