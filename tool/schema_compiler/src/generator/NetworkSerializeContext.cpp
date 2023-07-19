#include "NetworkSerializeContext.h"
#include "../IGenerator.h"

#include <utility>

namespace minecpp::tool::schema_compiler::generator {

NetworkSerializeContext::NetworkSerializeContext(Type type, std::string_view name,
                                                 const mb::codegen::expression &source_expression,
                                                 AnnotationList annotations, int depth,
                                                 mb::codegen::statement::collector &collector,
                                                 NetworkPropertyStorage &property_storage,
                                                 const SymbolTable &symbol_table, const Document &document) :
    m_type(std::move(type)),
    m_name(std::string{name}),
    m_source_property(source_expression.copy()),
    m_annotations(std::move(annotations)),
    m_depth(depth),
    m_collector(collector),
    m_property_storage(property_storage),
    m_symbol_table{symbol_table},
    m_document{document}
{
}

const mb::codegen::expression &NetworkSerializeContext::source_property()
{
   return *m_source_property;
}

const Type &NetworkSerializeContext::type() const
{
   return m_type;
}

mb::codegen::statement::collector &NetworkSerializeContext::operator<<(const mb::codegen::statement &stmt)
{
   return m_collector.operator<<(stmt);
}

mb::codegen::statement::collector &NetworkSerializeContext::operator<<(const mb::codegen::expression &expre)
{
   return m_collector.operator<<(expre);
}

void NetworkSerializeContext::write_serializer(const Type &type,
                                               const mb::codegen::expression &source_expression,
                                               std::string_view name,
                                               mb::codegen::statement::collector &collector)
{
   NetworkSerializeContext sub_ctx(type, name, source_expression, m_annotations, m_depth + 1, collector,
                                   m_property_storage, m_symbol_table, m_document);

   auto &type_generator = m_property_storage.property_of(sub_ctx.type_class(), type.line(), type.column());
   type_generator.write_serializer(sub_ctx);
}

const AnnotationList &NetworkSerializeContext::annotations() const
{
   return m_annotations;
}

std::string NetworkSerializeContext::unique_name(std::string_view suffix) const
{
   return fmt::format("{}{}_{}", m_name, suffix, m_depth);
}

mb::codegen::statement::collector &NetworkSerializeContext::collector()
{
   return m_collector;
}

std::string NetworkSerializeContext::type_generator() const
{
   auto symbol = m_symbol_table.find_symbol(m_document.package_info().full_name(), m_type.full_name());
   generator_verify(symbol.has_value(), m_type.line(), m_type.column(),
                    "could not find symbol {} in package {}", m_type.full_name(),
                    m_document.package_info().full_name());
   return symbol->generator;
}

TypeClass NetworkSerializeContext::type_class() const
{
   auto symbol = m_symbol_table.find_symbol(m_document.package_info().full_name(), m_type.full_name());
   generator_verify(symbol.has_value(), m_type.line(), m_type.column(),
                    "could not find symbol {} in package {}", m_type.full_name(),
                    m_document.package_info().full_name());
   return symbol->type_class;
}

}// namespace minecpp::tool::schema_compiler::generator
