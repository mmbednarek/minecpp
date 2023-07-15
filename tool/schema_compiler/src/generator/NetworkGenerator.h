#pragma once

#include "../IGenerator.h"

#include <mb/codegen/component.h>
#include <set>

namespace minecpp::tool::schema_compiler::generator {

class NetworkGeneratorFactory : public IGeneratorFactory
{
 public:
   std::unique_ptr<IGenerator> create_generator(const Document &document, const SymbolTable &table,
                                                const PathInfo &path_info) override;
};

class NetworkGenerator : public IGenerator {
 public:
   NetworkGenerator(const Document &document, const SymbolTable &table, const PathInfo &path_info);

   [[nodiscard]] std::string target_header_path() const override;
   [[nodiscard]] std::string target_source_path() const override;

   void generate_header(std::ostream &output) override;
   void generate_source(std::ostream &output) override;

   void put_attribute_serializer(const Type &type, std::string_view attribute_name, const AnnotationList& annotations, int depth, mb::codegen::statement::collector &col);
   void put_attribute_deserializer(const Type &type, std::string_view attribute_dst, std::string_view attribute_name, const AnnotationList& annotations, mb::codegen::statement::collector &col);

 private:
   [[nodiscard]] std::string corresponding_header(std::string_view document_path) const;
   [[nodiscard]] std::set<std::string> collect_headers() const;

   const Document &m_document;
   const SymbolTable &m_table;
   const PathInfo &m_path_info;
   mb::codegen::component m_component;
};

}
