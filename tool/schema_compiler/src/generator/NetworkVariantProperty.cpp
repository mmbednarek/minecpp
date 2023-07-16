#include "NetworkVariantProperty.h"
#include "../IGenerator.h"
#include "NetworkDeserializeContext.h"
#include "NetworkSerializeContext.h"

using mb::codegen::call;
using mb::codegen::method_call;
using mb::codegen::raw;
using mb::codegen::statement;
using mb::codegen::switch_statement;

namespace minecpp::tool::schema_compiler::generator {

void NetworkVariantProperty::write_serializer(NetworkSerializeContext &ctx)
{
   ctx << call("writer.write_varint",
               call("static_cast<std::int32_t>", method_call(ctx.source_property(), "index")));

   switch_statement cases(method_call(ctx.source_property(), "index"));
   for (std::size_t i{0}; i < ctx.type().template_args_count(); ++i) {
      auto variant_type = ctx.type().template_arg_at(i);

      generator_verify(variant_type.has_value(), ctx.type().line(), ctx.type().column(), "internal error");

      cases.add(raw("{}", i), [&ctx, &variant_type, i](statement::collector &col) {
         ctx.write_serializer(*variant_type, call(fmt::format("std::get<{}>", i), ctx.source_property()),
                              ctx.unique_name(fmt::format("_item_", i)), col);
         col << raw("break");
      });
   }

   cases.add_default_noscope(
           [](statement::collector &col) { col << raw("throw std::runtime_error(\"invalid variant\")"); });

   ctx << cases;
}

void NetworkVariantProperty::write_deserializer(NetworkDeserializeContext &ctx)
{
   ctx.ensure_destination();

   auto index_name = ctx.unique_name("_index");
   ctx << raw("auto {} = reader.read_varint()", index_name);
   switch_statement cases(raw("{}", index_name));
   for (std::size_t i{0}; i < ctx.type().template_args_count(); ++i) {
      auto variant_type = ctx.type().template_arg_at(i);
      generator_verify(variant_type.has_value(), ctx.type().line(), ctx.type().column(), "internal error");

      cases.add(raw("{}", i), [&variant_type, &ctx](statement::collector &col) {
         ctx.write_deserializer(*variant_type, col, ctx.unique_name("_item"), ctx.destination());
         col << raw("break");
      });
   }
   cases.add_default_noscope(
           [](statement::collector &col) { col << raw("throw std::runtime_error(\"invalid variant\")"); });
   ctx << cases;
}

}// namespace minecpp::tool::schema_compiler::generator
