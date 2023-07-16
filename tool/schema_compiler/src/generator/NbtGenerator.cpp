#include "NbtGenerator.h"
#include "CppUtil.h"

#include <array>
#include <fmt/core.h>
#include <mb/codegen/class.h>
#include <mb/codegen/lambda.h>
#include <memory>
#include <sstream>
#include <string_view>

using mb::codegen::assign;
using mb::codegen::call;
using mb::codegen::class_spec;
using mb::codegen::default_constructor;
using mb::codegen::deref;
using mb::codegen::for_statement;
using mb::codegen::if_statement;
using mb::codegen::if_switch_statement;
using mb::codegen::items;
using mb::codegen::lambda;
using mb::codegen::method;
using mb::codegen::method_call;
using mb::codegen::method_template;
using mb::codegen::ranged_for_statement;
using mb::codegen::raw;
using mb::codegen::return_statement;
using mb::codegen::statement;
using mb::codegen::static_method;
using mb::codegen::struct_constructor;

namespace minecpp::tool::schema_compiler::generator {

std::unique_ptr<IGenerator> NbtGeneratorFactory::create_generator(const Document &document,
                                                                  const SymbolTable &table,
                                                                  const PathInfo &path_info)
{
   return std::make_unique<NbtGenerator>(document, table, path_info);
}

NbtGenerator::NbtGenerator(const Document &document, const SymbolTable &table, const PathInfo &path_info) :
    m_document(document),
    m_table(table),
    m_path_info(path_info),
    m_component(document.package_info().to_cpp_namespace())
{
   m_component.source_include_local(this->corresponding_header(this->m_path_info.origin_document_path));

   m_component.header_include("iostream");
   m_component.header_include("optional");
   m_component.header_include("map");
   m_component.header_include("mb/result.h");
   m_component.header_include("mb/int.h");
   m_component.header_include("minecpp/nbt/Writer.h");
   m_component.header_include("minecpp/nbt/Reader.h");
   m_component.header_include("string");
   m_component.header_include("vector");

   m_component.source_include("minecpp/nbt/Exception.h");

   auto headers = this->collect_headers();
   for (const auto &header : headers) {
      m_component.header_include_local(fmt::format("{}/{}", m_path_info.root_include_path, header));
   }

   for (const auto &record : m_document.records()) {
      class_spec record_class(record.name());

      std::map<std::string, std::vector<Attribute>> type_names{};
      for (const auto &attribute : record.attributes()) {
         const auto &cpp_type = this->cpp_type_of(attribute.type());
         record_class.add_public(cpp_type, this->cpp_name(attribute));

         auto symbol =
                 m_table.find_symbol(m_document.package_info().full_name(), attribute.type().full_name());
         generator_verify(symbol.has_value(), attribute.line(), attribute.column(),
                          "could not find symbol {} in package {}", attribute.type().full_name(),
                          m_document.package_info().full_name());

         if (symbol->type_class == TypeClass::Optional) {
            auto non_opt_type = attribute.type().template_arg_at(0);
            generator_verify(non_opt_type.has_value(), attribute.line(), attribute.column(),
                             "optional type for field {}", attribute.name());
            type_names[this->cpp_type_of(*non_opt_type)].push_back(attribute);
         } else {
            type_names[cpp_type].push_back(attribute);
         }
      }

      // public:

      record_class.add_public(default_constructor());

      // void serialize_no_header()
      record_class.add_public(method(
              "void", "serialize_no_header",
              {
                      {"minecpp::nbt::Writer", "&w"}
      },
              true, [this, &record](statement::collector &col) {
                 for (const auto &attribute : record.attributes()) {
                    auto value = raw(this->cpp_name(attribute));

                    auto symbol = m_table.find_symbol(m_document.package_info().full_name(),
                                                      attribute.type().full_name());
                    generator_verify(symbol.has_value(), attribute.line(), attribute.column(),
                                     "could not find symbol {} in package {}", attribute.type().full_name(),
                                     m_document.package_info().full_name());

                    if (symbol->type_class == TypeClass::Optional) {
                       col << if_statement(method_call(value, "has_value"),
                                           [this, &attribute, &value](statement::collector &col) {
                                              auto core_type = attribute.type().template_arg_at(0);
                                              generator_verify(
                                                      core_type.has_value(), attribute.line(),
                                                      attribute.column(),
                                                      "optional type is missing a template argument");

                                              col << call("w.write_header", raw(this->nbt_tag_id(*core_type)),
                                                          raw("\"{}\"", this->nbt_name(attribute)));

                                              put_serialize_logic(col, *core_type, deref{value}, 0);
                                           });

                    } else if (symbol->type_class == TypeClass::Variant) {
                       if_switch_statement if_switch;
                       for (std::size_t arg_index{0}; arg_index < attribute.type().template_args_count();
                            ++arg_index) {
                          auto subtype = attribute.type().template_arg_at(arg_index);
                          generator_verify(subtype.has_value(), attribute.line(), attribute.column(),
                                           "internal error");

                          if_switch.add_case(
                                  call(fmt::format("std::holds_alternative<{}>", this->cpp_type_of(*subtype)),
                                       value),
                                  [this, &subtype, &attribute, &value](statement::collector &col) {
                                     col << call("w.write_header", raw(this->nbt_tag_id(*subtype)),
                                                 raw("\"{}\"", this->nbt_name(attribute)));
                                     this->put_serialize_logic(
                                             col, *subtype,
                                             call(fmt::format("std::get<{}>", this->cpp_type_of(*subtype)),
                                                  value),
                                             0);
                                  });
                       }
                       col << if_switch;
                    } else {
                       col << call("w.write_header", raw(this->nbt_tag_id(attribute.type())),
                                   raw("\"{}\"", this->nbt_name(attribute)));
                       put_serialize_logic(col, attribute.type(), value, 0);
                    }
                 }


                 col << call("w.end_compound");
              }));

      // void serialize()
      record_class.add_public(method("void", "serialize",
                                     {
                                             {    "std::ostream",      "&out_stream"},
                                             {"std::string_view", "in_compound_name"}
      },
                                     true, [](statement::collector &col) {
                                        col << call("minecpp::nbt::Writer w", raw("out_stream"));
                                        col << call("w.begin_compound", raw("in_compound_name"));
                                        col << call("this->serialize_no_header", raw("w"));
                                     }));

      // static Msg deserialize_no_header
      record_class.add_public(static_method(record.name(), "deserialize_no_header",
                                            {
                                                    {"minecpp::nbt::Reader", "&r"}
      },
                                            [this, &record](statement::collector &col) {
                                               col << raw("{} result", record.name());
                                               col << ranged_for_statement(
                                                       "const auto", "&[tagid, in_field_name]",
                                                       call("r.iterate_compound"),
                                                       [this, &record](statement::collector &col) {
                                                          this->put_deserialize_logic(record, col);
                                                       });
                                               col << raw("return result");
                                            }));

      // static Msg deserialize
      record_class.add_public(static_method(
              record.name(), "deserialize",
              {
                      {"std::istream", "&in"}
      },
              [&record](statement::collector &col) {
                 col << call("minecpp::nbt::Reader r", raw("in"));
                 col << assign("auto peek", call("r.peek_tag"));
                 col << if_statement(raw("peek.id != minecpp::nbt::TagId::Compound"),
                                     [](statement::collector &col) { col << raw("return {}"); });
                 col << raw("return {}::deserialize_no_header(r)", record.name());
              }));

      // public:

      m_component << record_class;
   }
}

void NbtGenerator::generate_header(std::ostream &output)
{
   m_component.write_header(output);
}

void NbtGenerator::generate_source(std::ostream &output)
{
   m_component.write_source(output);
}

std::string NbtGenerator::target_header_path() const
{
   return fmt::format("{}/{}", m_path_info.root_header_target_dir,
                      this->corresponding_header(m_path_info.origin_document_path));
}

std::string NbtGenerator::target_source_path() const
{
   std::string_view document_path{m_path_info.origin_document_path};
   if (document_path.starts_with(m_path_info.root_origin_dir)) {
      document_path.remove_prefix(m_path_info.root_origin_dir.size());
   }

   return fmt::format("{}/{}.cpp", m_path_info.root_source_target_dir, document_path);
}

std::string NbtGenerator::corresponding_header(std::string_view document_path) const
{
   if (document_path.starts_with(m_path_info.root_origin_dir)) {
      document_path.remove_prefix(m_path_info.root_origin_dir.size());
   }

   return fmt::format("{}.h", document_path);
}

std::string NbtGenerator::header_base_name() const
{
   auto slash_at = m_path_info.origin_document_path.find_last_of('/');
   if (slash_at == std::string::npos) {
      return fmt::format("{}.h", m_path_info.origin_document_path);
   }
   return fmt::format("{}.h", m_path_info.origin_document_path.substr(slash_at + 1));
}

std::set<std::string> NbtGenerator::collect_headers() const
{
   std::set<std::string> output;
   for (const auto &record : m_document.records()) {
      for (const auto &attribute : record.attributes()) {
         auto symbol =
                 m_table.find_symbol(m_document.package_info().full_name(), attribute.type().full_name());
         generator_verify(symbol.has_value(), attribute.line(), attribute.column(),
                          "could not find symbol {} in package {}", attribute.type().full_name(),
                          m_document.package_info().full_name());

         if (symbol->source_file == this->m_path_info.origin_document_path)
            continue;

         if (symbol->source_file.empty())
            continue;

         output.emplace(this->corresponding_header(symbol->source_file));
      }
   }
   return output;
}

std::string NbtGenerator::cpp_type_of(const Type &type) const
{
   CppType cpp_type(m_document, m_table, type);
   return cpp_type.type_name();
}

// clang-format off
constexpr std::array<const char *, 24> g_core_nbt_types{
   "minecpp::nbt::TagId::Byte",
   "minecpp::nbt::TagId::Short",
   "minecpp::nbt::TagId::Int",
   "minecpp::nbt::TagId::Long",
   "minecpp::nbt::TagId::Byte",
   "minecpp::nbt::TagId::Short",
   "minecpp::nbt::TagId::Int",
   "minecpp::nbt::TagId::Long",
   "minecpp::nbt::TagId::String",
   "minecpp::nbt::TagId::Float",
   "minecpp::nbt::TagId::Double",
   "minecpp::nbt::TagId::List",
   "minecpp::nbt::TagId::Compound",
   "minecpp::nbt::TagId::Compound",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "minecpp::nbt::TagId::Compound",
   ""
};

// clang-format on

std::string NbtGenerator::nbt_tag_id(const Type &type) const
{
   auto symbol = m_table.find_symbol(m_document.package_info().full_name(), type.full_name());
   generator_verify(symbol.has_value(), type.line(), type.column(), "could not find symbol {} in package {}",
                    type.full_name(), m_document.package_info().full_name());

   generator_verify(symbol->type_class != TypeClass::Variant, type.line(), type.column(),
                    "invalid use of variant type");

   if (symbol->type_class == TypeClass::List) {
      auto sub_type = type.template_arg_at(0);
      generator_verify(sub_type.has_value(), type.line(), type.column(),
                       "list type is missing a template argument");

      auto sub_symbol = m_table.find_symbol(m_document.package_info().full_name(), sub_type->full_name());
      generator_verify(symbol.has_value(), sub_type->line(), sub_type->column(),
                       "could not find symbol {} in package {}", sub_type->full_name(),
                       m_document.package_info().full_name());

      switch (sub_symbol->type_class) {
      case TypeClass::UInt8: return "minecpp::nbt::TagId::ByteArray";
      case TypeClass::Int32: return "minecpp::nbt::TagId::IntArray";
      case TypeClass::Int64: return "minecpp::nbt::TagId::LongArray";
      default: return "minecpp::nbt::TagId::List";
      }
   }
   if (symbol->type_class == TypeClass::Optional) {
      auto sub_type = type.template_arg_at(0);
      generator_verify(sub_type.has_value(), type.line(), type.column(),
                       "optional type is missing a template argument");

      return this->nbt_tag_id(*sub_type);
   }
   return g_core_nbt_types[static_cast<std::size_t>(symbol->type_class)];
}

std::string NbtGenerator::cpp_name(const Attribute &attribute) const
{
   CppAttribute cpp_attribute(m_document, m_table, attribute);
   return cpp_attribute.name();
}

std::string NbtGenerator::nbt_name(const Attribute &attribute) const
{
   if (attribute.annotations().has_key("Namespace") && attribute.annotations().has_key("Path")) {
      return fmt::format("{}:{}", attribute.annotations().value_at("Namespace"),
                         attribute.annotations().value_at("Path"));
   }
   return attribute.name();
}

raw NbtGenerator::put_deserialize_procedure(const Type &type, statement::collector &col, bool should_move)
{
   auto symbol = m_table.find_symbol(m_document.package_info().full_name(), type.full_name());
   generator_verify(symbol.has_value(), type.line(), type.column(), "could not find symbol {} in package {}",
                    type.full_name(), m_document.package_info().full_name());

   if (symbol->type_class == TypeClass::Optional) {
      auto subtype = type.template_arg_at(0);
      generator_verify(subtype.has_value(), type.line(), type.column(),
                       "optional type is missing a template argument");

      return this->put_deserialize_procedure(*subtype, col, false);
   }

   if (auto static_deserializer = this->static_deserializer_of(type); static_deserializer.has_value()) {
      return raw(*static_deserializer);
   }

   if (symbol->type_class == TypeClass::Record) {
      generator_verify(symbol->generator == g_nbt_generator_name, type.line(), type.column(),
                       "NBT records can only contain other NBT records");
      return raw("{}::deserialize_no_header(r)", this->cpp_type_of(type));
   }

   if (symbol->type_class == TypeClass::Variant) {
      col << raw("{} result_variant", this->cpp_type_of(type));
      if_switch_statement if_switch;
      for (std::size_t arg_index{0}; arg_index < type.template_args_count(); ++arg_index) {
         auto subtype = type.template_arg_at(arg_index);
         generator_verify(subtype.has_value(), type.line(), type.column(), "internal error");
         if_switch.add_case(
                 raw("tagid == {}", this->nbt_tag_id(*subtype)), [this, &subtype](statement::collector &col) {
                    col << assign("result_variant", this->put_deserialize_procedure(*subtype, col, true));
                 });
      }
      col << if_switch;
      if (should_move) {
         return raw("std::move(result_variant)");
      } else {
         return raw("result_variant");
      }
   }

   if (symbol->type_class == TypeClass::Map) {
      auto key_type = type.template_arg_at(0);
      generator_verify(key_type.has_value(), type.line(), type.column(),
                       "map type is missing first template argument");

      generator_verify(key_type->full_name() == "string", type.line(), type.column(),
                       "map key type needs to be a string");

      auto value_type = type.template_arg_at(1);
      generator_verify(value_type.has_value(), type.line(), type.column(),
                       "map type is missing second template argument");

      col << raw("std::map<std::string, {}> map_result", this->cpp_type_of(*value_type));

      col << ranged_for_statement("const auto", "&[tag_id, key]", call("r.iterate_compound"),
                                  [this, &value_type](statement::collector &col) {
                                     col << assign("map_result[key]",
                                                   this->put_deserialize_procedure(*value_type, col, true));
                                  });

      if (should_move) {
         return raw("std::move(map_result)");
      } else {
         return raw("map_result");
      }
   }

   if (symbol->type_class == TypeClass::List) {
      col << raw("auto list_info = r.peek_list()");

      // TODO: Throw if the list_info type is incorrect!

      auto subtype = type.template_arg_at(0);
      generator_verify(subtype.has_value(), type.line(), type.column(),
                       "list type is missing template argument");
      col << raw("std::vector<{}> list(list_info.size)", this->cpp_type_of(*subtype), 0);

      col << call("std::generate", call("list.begin"), call("list.end"),
                  lambda(
                          {},
                          [this, &subtype](statement::collector &col) {
                             col << mb::codegen::return_statement(
                                     this->put_deserialize_procedure(*subtype, col, false));
                          },
                          raw("&r")));

      if (should_move) {
         return raw("std::move(list)");
      } else {
         return raw("list");
      }
   }

   if (symbol->type_class == TypeClass::NbtCompoundContent) {
      return raw("r.read_compound_content()");
   }

   generator_verify(false, type.line(), type.column(), "unsupported type for NBT generation");
   return raw{""};
}

void NbtGenerator::put_deserialize_logic(const Record &record, mb::codegen::statement::collector &col)
{
   using namespace mb::codegen;

   for (const auto &attribute : record.attributes()) {
      col << if_statement(raw("in_field_name == \"{}\"", this->nbt_name(attribute)),
                          [this, &record, &attribute](mb::codegen::statement::collector &col) {
                             if (attribute.type().full_name() != "variant") {
                                col << raw(R"(::minecpp::nbt::verify_tag("{}", in_field_name, {}, tagid))",
                                           record.name(), this->nbt_tag_id(attribute.type()));
                             }
                             std::string attribute_name = fmt::format("result.{}", this->cpp_name(attribute));
                             col << assign(attribute_name,
                                           this->put_deserialize_procedure(attribute.type(), col, true));
                             col << raw("continue");
                          });
   }
   col << call("r.skip_payload", raw("tagid"));
}

std::optional<std::string> NbtGenerator::static_deserializer_of(const Type &type) const
{
   auto symbol = m_table.find_symbol(m_document.package_info().full_name(), type.full_name());
   generator_verify(symbol.has_value(), type.line(), type.column(), "could not find symbol {} in package {}",
                    type.full_name(), m_document.package_info().full_name());

   switch (symbol->type_class) {
   case TypeClass::Int8: return "r.read_byte()";
   case TypeClass::Int16: return "r.read_short()";
   case TypeClass::Int32: return "r.read_int()";
   case TypeClass::Int64: return "r.read_long()";
   case TypeClass::String: return "r.read_str()";
   case TypeClass::Float32: return "r.read_float32()";
   case TypeClass::Float64: return "r.read_float64()";
   case TypeClass::List: {
      auto subtype = type.template_arg_at(0);
      if (not subtype.has_value())
         return std::nullopt;

      auto sub_symbol = m_table.find_symbol(m_document.package_info().full_name(), subtype->full_name());
      generator_verify(sub_symbol.has_value(), subtype->line(), subtype->column(),
                       "could not find symbol {} in package {}", subtype->full_name(),
                       m_document.package_info().full_name());

      switch (sub_symbol->type_class) {
      case TypeClass::UInt8: return "r.read_byte_vector()";
      case TypeClass::Int32: return "r.read_int_vec()";
      case TypeClass::Int64: return "r.read_long_vec()";
      default: return std::nullopt;
      }
   }
   default: return std::nullopt;
   }
}

void NbtGenerator::put_serialize_logic(mb::codegen::statement::collector &col, const Type &type,
                                       const mb::codegen::expression &value, int depth)
{
   auto symbol = m_table.find_symbol(m_document.package_info().full_name(), type.full_name());
   generator_verify(symbol.has_value(), type.line(), type.column(), "could not find symbol {} in package {}",
                    type.full_name(), m_document.package_info().full_name());

   switch (symbol->type_class) {
   case TypeClass::Int8: col << call("w.write_byte_content", call("static_cast<std::uint8_t>", value)); break;
   case TypeClass::Int16: col << call("w.write_short_content", value); break;
   case TypeClass::Int32: col << call("w.write_int_content", value); break;
   case TypeClass::Int64: col << call("w.write_long_content", value); break;
   case TypeClass::String: col << call("w.write_string_content", value); break;
   case TypeClass::Float32: col << call("w.write_float_content", value); break;
   case TypeClass::Float64: col << call("w.write_double_content", value); break;
   case TypeClass::List: {
      auto subtype = type.template_arg_at(0);
      generator_verify(subtype.has_value(), type.line(), type.column(),
                       "list type is missing a template argument");

      auto sub_symbol = m_table.find_symbol(m_document.package_info().full_name(), subtype->full_name());
      generator_verify(sub_symbol.has_value(), subtype->line(), subtype->column(),
                       "could not find symbol {} in package {}", subtype->full_name(),
                       m_document.package_info().full_name());

      switch (sub_symbol->type_class) {
      case TypeClass::UInt8: col << call("w.write_bytes_content", value); break;
      case TypeClass::Int32: col << call("w.write_ints_content", value); break;
      case TypeClass::Int64: col << call("w.write_longs_content", value); break;
      default: {
         col << call("w.begin_list_no_header", raw(this->nbt_tag_id(*subtype)), method_call(value, "size"));

         std::string list_item_name = fmt::format("&list_item_{}", depth);
         col << ranged_for_statement(
                 "const auto", list_item_name, value, [this, depth, &subtype](statement::collector &col) {
                    this->put_serialize_logic(col, *subtype, raw("list_item_{}", depth), depth + 1);
                 });
      }
      }

      break;
   }
   case TypeClass::Map: {
      auto key_type = type.template_arg_at(0);
      generator_verify(key_type.has_value(), type.line(), type.column(),
                       "map type is missing first template argument");
      generator_verify(key_type->full_name() == "string", type.line(), type.column(),
                       "map key type needs to be a string");

      auto value_type = type.template_arg_at(1);
      generator_verify(value_type.has_value(), type.line(), type.column(),
                       "map type is missing second template argument");

      std::string key_value_name = fmt::format("&[key_{}, value_{}]", depth, depth);
      col << ranged_for_statement(
              "const auto", key_value_name, value, [this, depth, &value_type](statement::collector &col) {
                 col << call("w.write_header", raw(this->nbt_tag_id(*value_type)), raw("key_{}", depth));
                 this->put_serialize_logic(col, *value_type, raw("value_{}", depth), depth + 1);
              });
      col << call("w.end_compound");

      break;
   }
   case TypeClass::Record: {
      generator_verify(symbol->generator == g_nbt_generator_name, type.line(), type.column(),
                       "NBT records can only contain other NBT records");
      col << method_call(value, "serialize_no_header", raw("w"));
      break;
   }
   case TypeClass::Variant: {
      for (std::size_t arg_index{0}; arg_index < type.template_args_count(); ++arg_index) {
         auto subtype = type.template_arg_at(arg_index);
         generator_verify(subtype.has_value(), type.line(), type.column(), "internal error");

         col << if_statement(
                 call(fmt::format("std::holds_alternative<{}>", this->cpp_type_of(*subtype)), value),
                 [this, &subtype, &value](statement::collector &col) {
                    this->put_serialize_logic(
                            col, *subtype,
                            call(fmt::format("std::get<{}>", this->cpp_type_of(*subtype)), value), 0);
                 });
      }
   }
   case TypeClass::NbtCompoundContent:
      col << call("minecpp::nbt::serialize_compound_content", raw("w"), value);
      break;
   default:
      generator_verify(false, type.line(), type.column(), "type {} is unsupported for NBT generation",
                       type.full_name());
   }
}
}// namespace minecpp::tool::schema_compiler::generator
