#include "NetworkGenerator.h"
#include "CppUtil.h"
#include "minecpp/util/Case.h"

#include "NetworkBasicProperty.h"
#include "NetworkDeserializeContext.h"
#include "NetworkListProperty.h"
#include "NetworkMapProperty.h"
#include "NetworkOptionalProperty.h"
#include "NetworkRecordProperty.h"
#include "NetworkSerializeContext.h"
#include "NetworkVariantProperty.h"

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
   m_component.header_include("optional");
   m_component.header_include_local("minecpp/network/message/Writer.h");
   m_component.header_include_local("minecpp/network/message/Reader.h");

   auto headers = this->collect_headers();
   for (const auto &header : headers) {
      m_component.header_include_local(fmt::format("{}/{}", m_path_info.root_include_path, header));
   }

   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Int8, "writer.write_sbyte",
                                                              "reader.read_sbyte");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::UInt8, "writer.write_byte",
                                                              "reader.read_byte");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Int16, "writer.write_big_endian",
                                                              "reader.read_big_endian<std::int16_t>");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::UInt16, "writer.write_big_endian",
                                                              "reader.read_big_endian<std::uint16_t>");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Int32, "writer.write_big_endian",
                                                              "reader.read_big_endian<std::int32_t>");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::UInt32, "writer.write_big_endian",
                                                              "reader.read_big_endian<std::uint32_t>");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Int64, "writer.write_big_endian",
                                                              "reader.read_big_endian<std::int64_t>");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::UInt64, "writer.write_big_endian",
                                                              "reader.read_big_endian<std::uint64_t>");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::String, "writer.write_string",
                                                              "reader.read_string");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Float32, "writer.write_float",
                                                              "reader.read_float");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Float64, "writer.write_double",
                                                              "reader.read_double");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Varint, "writer.write_varint",
                                                              "reader.read_varint");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Varlong, "writer.write_varlong",
                                                              "reader.read_varlong");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::UnsignedVarint, "writer.write_uvarint",
                                                              "reader.read_uvarint");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::UnsignedVarlong, "writer.write_uvarlong",
                                                              "reader.read_uvarlong");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Bool, "writer.write_bool",
                                                              "reader.read_bool");
   m_property_storage.register_property<NetworkBasicProperty>(TypeClass::Uuid, "writer.write_uuid",
                                                              "reader.read_uuid");
   m_property_storage.register_property<NetworkListProperty>(TypeClass::List);
   m_property_storage.register_property<NetworkOptionalProperty>(TypeClass::Optional);
   m_property_storage.register_property<NetworkMapProperty>(TypeClass::Map);
   m_property_storage.register_property<NetworkVariantProperty>(TypeClass::Variant);
   m_property_storage.register_property<NetworkRecordProperty>(TypeClass::Record);

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

      record_class.add_public(method(
              "void", "serialize",
              {
                      {"::minecpp::network::message::Writer", "&writer"},
      },
              true, [this, is_message, &record](statement::collector &col) {
                 if (is_message) {
                    col << raw("writer.write_byte({})", record.annotations().value_at("MessageID"));
                 }

                 for (const auto &attribute : record.attributes()) {
                    CppAttribute cpp_attribute(m_document, m_table, attribute);
                    NetworkSerializeContext ctx{attribute.type(),
                                                cpp_attribute.name(),
                                                raw(fmt::format("this->{}", cpp_attribute.name())),
                                                attribute.annotations(),
                                                0,
                                                col,
                                                m_property_storage,
                                                m_table,
                                                m_document};

                    auto &property = m_property_storage.property_of(cpp_attribute.type_class());
                    property.write_serializer(ctx);
                 }
              }));

      std::vector<mb::codegen::arg> deserialize_arguments{
              {"::minecpp::network::message::Reader", "&reader"}
      };

      if (record.attributes().empty()) {
         deserialize_arguments.clear();
         deserialize_arguments.emplace_back("::minecpp::network::message::Reader", "&/*reader*/");
      }

      if (record.annotations().has_key("ArgCount")) {
         auto arg_count = std::stoi(record.annotations().value_at("ArgCount"));
         for (int i{0}; i < arg_count; ++i) {
            auto arg      = record.annotations().value_at(fmt::format("Arg{}", i));
            auto colon_at = arg.find(':');
            generator_verify(colon_at != std::string::npos, record.line(), record.column(),
                             "argument needs to be separated with a colon");

            Type arg_type{0, 0, {}, arg.substr(colon_at + 1)};
            CppType cpp_arg_type{m_document, m_table, arg_type};
            deserialize_arguments.emplace_back(cpp_arg_type.type_name(), arg.substr(0, colon_at));
         }
      }

      record_class.add_public(static_method(record.name(), "deserialize", deserialize_arguments,
                                            [this, &record](statement::collector &col) {
                                               col << raw("{} result", record.name());
                                               for (const auto &attribute : record.attributes()) {
                                                  CppAttribute cpp_attribute(m_document, m_table, attribute);

                                                  NetworkDeserializeContext ctx{attribute.type(),
                                                                              cpp_attribute.name(),
                                                                              std::make_unique<raw>(fmt::format("result.{}", cpp_attribute.name())),
                                                                              attribute.annotations(),
                                                                              0,
                                                                              col,
                                                                              m_property_storage,
                                                                              m_table,
                                                                              m_document};

                                                  auto &property = m_property_storage.property_of(cpp_attribute.type_class());
                                                  property.write_deserializer(ctx);
                                               }
                                               col << return_statement(raw("result"));
                                            }));

      m_component << record_class;
   }

   if (message_count > 0) {

      m_component << template_arguments(
              {
                      {"typename",    "TVisitor"},
                      {"typename", "TClientInfo"}
      },
              function("void", "visit_message",
                       {{"TVisitor", "&visitor"},
                        {"TClientInfo", "&client_info"},
                        {"::minecpp::network::message::Reader", "&reader"}},
                       [this](statement::collector &col) {
                          col << raw("auto message_id = reader.read_byte()");
                          switch_statement switch_stmt(raw("message_id"));
                          for (const auto &record : m_document.records()) {
                             if (not record.annotations().has_key("MessageID"))
                                continue;

                             switch_stmt.add(
                                     raw(record.annotations().value_at("MessageID")),
                                     [&record](statement::collector &col) {
                                        std::string snake_case_name;
                                        util::convert_to_snake_case(record.name().begin(),
                                                                    record.name().end(),
                                                                    std::back_inserter(snake_case_name));
                                        col << raw("auto message = {}::deserialize(reader)", record.name());
                                        col << raw("visitor.on_{}(client_info, message)", snake_case_name);
                                        col << raw("break");
                                     });
                          }
                          switch_stmt.add_default_noscope([](statement::collector &col) {
                             col << raw("visitor.on_failure(client_info, message_id)");
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
