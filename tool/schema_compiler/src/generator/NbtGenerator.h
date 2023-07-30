#pragma once

#include "../IGenerator.h"

#include <mb/codegen/component.h>
#include <set>

namespace minecpp::tool::schema_compiler::generator {

class NbtGeneratorFactory : public IGeneratorFactory
{
 public:
   std::unique_ptr<IGenerator> create_generator(const Document &document, const SymbolTable &table,
                                                const PathInfo &path_info) override;

 public:
};

class NbtGenerator : public IGenerator
{
 public:
   NbtGenerator(const Document &document, const SymbolTable &table, const PathInfo &path_info);

   [[nodiscard]] std::string target_header_path() const override;
   [[nodiscard]] std::string target_source_path() const override;

   void generate_header(std::ostream &output) override;
   void generate_source(std::ostream &output) override;

 private:
   [[nodiscard]] std::string corresponding_header(std::string_view document_path) const;
   [[nodiscard]] std::string header_base_name() const;
   [[nodiscard]] std::set<std::string> collect_headers() const;
   [[nodiscard]] std::string cpp_type_of(const Type &type) const;
   [[nodiscard]] std::string nbt_tag_id(const Type &type) const;
   [[nodiscard]] std::string cpp_name(const Attribute &attribute) const;
   [[nodiscard]] std::string nbt_name(const Attribute &attribute) const;
   [[nodiscard]] std::optional<std::string> static_deserializer_of(const Type &type) const;
   [[nodiscard]] mb::codegen::raw put_deserialize_procedure(const Type &type,
                                                            mb::codegen::statement::collector &collector,
                                                            bool should_move);

   void put_serialize_logic(mb::codegen::statement::collector &col, const Type &type,
                            const mb::codegen::expression &value, int depth);
   void put_deserialize_logic(const Record &record, mb::codegen::statement::collector &col);

   const Document &m_document;
   const SymbolTable &m_table;
   const PathInfo &m_path_info;
   mb::codegen::component m_component;
};

}// namespace minecpp::tool::schema_compiler::generator