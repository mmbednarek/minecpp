#include "NetworkGenerator.h"
#include "CppUtil.h"
#include "minecpp/util/Case.h"

#include <fmt/core.h>
#include <mb/codegen/class.h>
#include <mb/codegen/lambda.h>

using mb::codegen::assign;
using mb::codegen::call;
using mb::codegen::class_spec;
using mb::codegen::default_constructor;
using mb::codegen::deref;
using mb::codegen::for_statement;
using mb::codegen::function;
using mb::codegen::if_statement;
using mb::codegen::lambda;
using mb::codegen::method;
using mb::codegen::method_template;
using mb::codegen::ranged_for_statement;
using mb::codegen::raw;
using mb::codegen::return_statement;
using mb::codegen::statement;
using mb::codegen::static_method;
using mb::codegen::struct_constructor;
using mb::codegen::switch_statement;
using mb::codegen::template_arguments;

namespace minecpp::tool::schema_compiler::generator {

NetworkGenerator::NetworkGenerator(const Document &document, const SymbolTable &table,
                                   const PathInfo &path_info) :

    m_document{document},
    m_table{table},
    m_path_info{path_info},
    m_component{document.package_info().to_cpp_namespace()}
{
   m_component.source_include_local(this->corresponding_header(this->m_path_info.origin_document_path));
   m_component.source_include("algorithm");

   m_component.header_include("cstdint");
   m_component.header_include("string");
   m_component.header_include_local("minecpp/network/message/Writer.h");
   m_component.header_include_local("minecpp/network/message/Reader.h");

   auto headers = this->collect_headers();
   for (const auto &header : headers) {
      m_component.header_include_local(fmt::format("{}/{}", m_path_info.root_include_path, header));
   }

   int message_count{};

   for (const auto &record : m_document.records()) {
      class_spec record_class(record.name());

      bool is_message{false};
      if (record.annotations().has_key("MessageID")) {
         is_message = true;
         ++message_count;
      }

      for (const auto &attribute : record.attributes()) {
         CppAttribute cpp_attribute(m_document, m_table, attribute);
         record_class.add_public(cpp_attribute.type_name(), cpp_attribute.name());
      }

      record_class.add_public(
              method("void", "serialize",
                     {
                             {"::minecpp::network::message::Writer", "&writer"},
      },
                     true, [this, is_message, &record](statement::collector &col) {
                        if (is_message) {
                           col << raw("writer.write_byte(0x{})", record.annotations().value_at("MessageID"));
                        }

                        for (const auto &attribute : record.attributes()) {
                           CppAttribute cpp_attribute(m_document, m_table, attribute);
                           this->put_attribute_serializer(
                                   attribute.type(), fmt::format("this->{}", cpp_attribute.name()), 0, col);
                        }
                     }));
      record_class.add_public(static_method(
              record.name(), "deserialize",
              {
                      {"::minecpp::network::message::Reader", "&reader"},
      },
              [this, &record](statement::collector &col) {
                 col << raw("{} result", record.name());
                 for (const auto &attribute : record.attributes()) {
                    CppAttribute cpp_attribute(m_document, m_table, attribute);
                    this->put_attribute_deserializer(attribute.type(),
                                                     fmt::format("result.{}", cpp_attribute.name()), col);
                 }
                 col << return_statement(raw("result"));
              }));

      m_component << record_class;
   }

   if (message_count > 0) {

      m_component << template_arguments(
              {
                      {"typename", "TVisitor"}
      },
              function("void", "visit_message",
                       {{"TVisitor", "&visitor"}, {"::minecpp::network::message::Reader", "&reader"}},
                       [this](statement::collector &col) {
                          col << raw("auto message_id = reader.read_byte()");
                          switch_statement switch_stmt(raw("message_id"));
                          for (const auto &record : m_document.records()) {
                             if (not record.annotations().has_key("MessageID"))
                                continue;

                             switch_stmt.add(
                                     raw("0x{}", record.annotations().value_at("MessageID")),
                                     [&record](statement::collector &col) {
                                        std::string snake_case_name;
                                        util::convert_to_snake_case(record.name().begin(),
                                                                    record.name().end(),
                                                                    std::back_inserter(snake_case_name));
                                        col << raw("auto message = {}::deserialize(reader)", record.name());
                                        col << raw("visitor.on_{}(message)", snake_case_name);
                                        col << raw("break");
                                     });
                          }
                          switch_stmt.add_default_noscope([](statement::collector &col) {
                             col << raw("visitor.on_failure(message_id)");
                             col << raw("break");
                          });
                          col << switch_stmt;
                       }));
   }
}

std::string NetworkGenerator::target_header_path() const
{
   std::string_view document_path{m_path_info.origin_document_path};
   if (document_path.starts_with(m_path_info.root_origin_dir)) {
      document_path.remove_prefix(m_path_info.root_origin_dir.size());
   }

   return fmt::format("{}/{}.h", m_path_info.root_header_target_dir, document_path);
}

std::string NetworkGenerator::target_source_path() const
{
   std::string_view document_path{m_path_info.origin_document_path};
   if (document_path.starts_with(m_path_info.root_origin_dir)) {
      document_path.remove_prefix(m_path_info.root_origin_dir.size());
   }

   return fmt::format("{}/{}.cpp", m_path_info.root_source_target_dir, document_path);
}

void NetworkGenerator::generate_header(std::ostream &output)
{
   m_component.write_header(output);
}

void NetworkGenerator::generate_source(std::ostream &output)
{
   m_component.write_source(output);
}

void NetworkGenerator::put_attribute_serializer(const Type &type, const std::string_view attribute_name,
                                                int depth, statement::collector &col)
{
   CppType cpp_type{m_document, m_table, type};
   switch (cpp_type.symbol().type_class) {
   case TypeClass::Int8: col << raw("writer.write_byte({})", attribute_name); break;
   case TypeClass::Int16: col << raw("writer.write_short({})", attribute_name); break;
   case TypeClass::Int32: col << raw("writer.write_big_endian({})", attribute_name); break;
   case TypeClass::Int64: col << raw("writer.write_long({})", attribute_name); break;
   case TypeClass::String: col << raw("writer.write_string({})", attribute_name); break;
   case TypeClass::Float32: col << raw("writer.write_float({})", attribute_name); break;
   case TypeClass::Float64: col << raw("writer.write_double({})", attribute_name); break;
   case TypeClass::List: {
      const auto subtype = type.template_arg_at(0);
      generator_verify(subtype.has_value(), type.line(), type.column(),
                       "list type requires a template argument");

      col << raw("writer.write_varint(static_cast<std::uint32_t>({}.size()))", attribute_name);
      col << ranged_for_statement(
              "const auto", fmt::format("&value_{}", depth), raw(std::string{attribute_name}),
              [this, depth, &subtype](statement::collector &col) {
                 this->put_attribute_serializer(*subtype, fmt::format("value_{}", depth), depth + 1, col);
              });
      break;
   }
   case TypeClass::Map: {
      const auto key_type   = type.template_arg_at(0);
      const auto value_type = type.template_arg_at(1);
      generator_verify(key_type.has_value() && value_type.has_value(), type.line(), type.column(),
                       "map type requires two template argument");

      col << raw("writer.write_varint(static_cast<std::uint32_t>({}.size()))", attribute_name);
      col << ranged_for_statement(
              "const auto", fmt::format("&[key_{}, value_{}]", depth, depth), raw("{}", attribute_name),
              [this, depth, &key_type, &value_type](statement::collector &col) {
                 this->put_attribute_serializer(*key_type, fmt::format("key_{}", depth), depth + 1, col);
                 this->put_attribute_serializer(*value_type, fmt::format("value_{}", depth), depth + 1, col);
              });
      break;
   }
   case TypeClass::Record: {
      col << raw("{}.serialize(writer)", attribute_name);
      break;
   }
   case TypeClass::Optional: {
      const auto subtype = type.template_arg_at(0);
      generator_verify(subtype.has_value(), type.line(), type.column(),
                       "optional type requires a template argument");
      col << if_statement(
              raw("{}.has_value()", attribute_name),
              [this, depth, &subtype](statement::collector &col) {
                 col << raw("writer.write_byte(1)");
                 this->put_attribute_serializer(*subtype, "(*value)", depth, col);
              },
              [](statement::collector &col) { col << raw("writer.write_byte(0)"); });
      break;
   }
   case TypeClass::Varint: col << raw("writer.write_varint({})", attribute_name);
   case TypeClass::Varlong: col << raw("writer.write_varlong({})", attribute_name);
   default: break;
   }
}

void NetworkGenerator::put_attribute_deserializer(const Type &type, const std::string_view attribute_name,
                                                  statement::collector &col)
{
   CppType cpp_type{m_document, m_table, type};
   switch (cpp_type.symbol().type_class) {
   case TypeClass::Int8: col << raw("{} = reader.read_byte()", attribute_name); break;
   case TypeClass::Int16: col << raw("{} = reader.read_short()", attribute_name); break;
   case TypeClass::Int32: col << raw("{} = reader.read_big_endian<int>()", attribute_name); break;
   case TypeClass::Int64: col << raw("{} = reader.read_long()", attribute_name); break;
   case TypeClass::String: col << raw("{} = reader.read_string()", attribute_name); break;
   case TypeClass::Float32: col << raw("{} = reader.read_float()", attribute_name); break;
   case TypeClass::Float64: col << raw("{} = reader.read_double()", attribute_name); break;
   case TypeClass::List: {
      const auto subtype = type.template_arg_at(0);

      generator_verify(subtype.has_value(), type.line(), type.column(),
                       "list type requires a template argument");

      col << raw("auto size = reader.read_varint()");
      col << raw("{}.resize(static_cast<std::size_t>(size))", attribute_name);
      col << call("std::generate", raw("{}.begin()", attribute_name), raw("{}.end()", attribute_name),
                  lambda(
                          {},
                          [this, &subtype](statement::collector &col) {
                             CppType cpp_type(m_document, m_table, *subtype);
                             col << raw("{} result", cpp_type.type_name());
                             this->put_attribute_deserializer(*subtype, "result", col);
                             col << raw("return result");
                          },
                          raw("&reader")));
      break;
   }
   case TypeClass::Map: {
      const auto key_type   = type.template_arg_at(0);
      const auto value_type = type.template_arg_at(1);
      generator_verify(key_type.has_value() && value_type.has_value(), type.line(), type.column(),
                       "map type requires two template argument");

      col << raw("const auto map_size = reader.read_varint()", attribute_name);
      col << call("std::generate_n", raw("std::inserter({}, {}.begin())", attribute_name, attribute_name),
                  raw("static_cast<std::size_t>(map_size)"),
                  lambda(
                          {},
                          [this, &key_type, &value_type](statement::collector &col) {
                             CppType key_cpp_type(m_document, m_table, *key_type);
                             col << raw("{} key_result", key_cpp_type.type_name());

                             CppType value_cpp_type(m_document, m_table, *value_type);
                             col << raw("{} value_result", value_cpp_type.type_name());

                             this->put_attribute_deserializer(*key_type, "key_result", col);
                             this->put_attribute_deserializer(*value_type, "value_result", col);

                             col << raw("return std::make_pair(key_result, value_result)");
                          },
                          raw("&reader")));
      break;
   }
   case TypeClass::Record: {
      col << raw("{} = {}::deserialize(reader)", attribute_name, cpp_type.type_name());
      break;
   }
   case TypeClass::Optional: {
      const auto subtype = type.template_arg_at(0);
      generator_verify(subtype.has_value(), type.line(), type.column(),
                       "optional type requires a template argument");

      col << raw("const auto has_value = reader.read_byte()");

      col << if_statement(raw("has_value"), [this, &subtype, attribute_name](statement::collector &col) {
         this->put_attribute_deserializer(*subtype, attribute_name, col);
      });
      break;
   }
   case TypeClass::Varint: col << raw("{} = reader.read_varint()", attribute_name);
   case TypeClass::Varlong: col << raw("{} = reader.read_varlong()", attribute_name);
   default: break;
   }
}

std::set<std::string> NetworkGenerator::collect_headers() const
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

std::string NetworkGenerator::corresponding_header(std::string_view document_path) const
{
   if (document_path.starts_with(m_path_info.root_origin_dir)) {
      document_path.remove_prefix(m_path_info.root_origin_dir.size());
   }

   return fmt::format("{}.h", document_path);
}

std::unique_ptr<IGenerator> NetworkGeneratorFactory::create_generator(const Document &document,
                                                                      const SymbolTable &table,
                                                                      const PathInfo &path_info)
{
   return std::make_unique<NetworkGenerator>(document, table, path_info);
}

}// namespace minecpp::tool::schema_compiler::generator
