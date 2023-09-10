#include "NetworkDeserializeContext.h"
#include "../IGenerator.h"
#include "CppUtil.h"

namespace minecpp::tool::schema_compiler::generator {


NetworkDeserializeContext::NetworkDeserializeContext(
        Type type, std::string name, std::unique_ptr<mb::codegen::expression> in_destination,
        AnnotationList in_annotations, int depth, mb::codegen::statement::collector &collector,
        NetworkPropertyStorage &property_storage, const SymbolTable &symbol_table, const Document &document) :
    m_type(std::move(type)),
    m_name(std::move(name)),
    m_destination(std::move(in_destination)),
    m_annotations(std::move(in_annotations)),
    m_depth(depth),
    m_collector{collector},
    m_property_storage{property_storage},
    m_symbol_table{symbol_table},
    m_document{document}
{
}

const Type &NetworkDeserializeContext::type() const
{
   return m_type;
}

std::string NetworkDeserializeContext::type_name() const
{
   CppType type(m_document, m_symbol_table, m_type);
   return type.type_name();
}

const AnnotationList &NetworkDeserializeContext::annotations() const
{
   return m_annotations;
}

void NetworkDeserializeContext::assign_expression(const mb::codegen::expression &expression)
{
   if (m_destination == nullptr) {
      m_destination = expression.copy();
      return;
   }

   m_collector << mb::codegen::binary_operator(*m_destination, "=", expression);
}

std::string NetworkDeserializeContext::unique_name(std::string_view suffix)
{
   return fmt::format("{}{}_{}", m_name, suffix, m_depth);
}

void NetworkDeserializeContext::ensure_destination()
{
   if (m_destination != nullptr)
      return;

   m_collector << mb::codegen::raw("{} {}", this->type_name(), m_name);
   m_destination = std::make_unique<mb::codegen::raw>(m_name);
}

const mb::codegen::expression &NetworkDeserializeContext::destination() const
{
   generator_verify(m_destination != nullptr, 0, 0,
                    "internal error: did not ensure deserialize context has destination");
   return *m_destination;
}

void NetworkDeserializeContext::write_deserializer(const Type &type,
                                                   mb::codegen::statement::collector &collector,
                                                   const std::string &name,
                                                   const mb::codegen::expression &destination)
{
   NetworkDeserializeContext sub_ctx{type,        name,      destination.copy(), m_annotations,
                                     m_depth + 1, collector, m_property_storage, m_symbol_table,
                                     m_document};

   auto &property = m_property_storage.property_of(sub_ctx.type_class(), type.line(), type.column());
   property.write_deserializer(sub_ctx);
}

std::unique_ptr<mb::codegen::expression>
NetworkDeserializeContext::write_deserializer(const Type &type, mb::codegen::statement::collector &collector,
                                              const std::string &name)
{
   NetworkDeserializeContext sub_ctx{
           type,           name,      nullptr, m_annotations, m_depth + 1, collector, m_property_storage,
           m_symbol_table, m_document};
   auto &property = m_property_storage.property_of(sub_ctx.type_class(), type.line(), type.column());
   property.write_deserializer(sub_ctx);

   return std::move(sub_ctx.m_destination);
}

std::unique_ptr<mb::codegen::expression> NetworkDeserializeContext::write_deserializer_to_var(
        const Type &type, mb::codegen::statement::collector &collector, const std::string &name)
{
   NetworkDeserializeContext sub_ctx{
           type,           name,      nullptr, m_annotations, m_depth + 1, collector, m_property_storage,
           m_symbol_table, m_document};
   sub_ctx.ensure_destination();

   auto &property = m_property_storage.property_of(sub_ctx.type_class(), type.line(), type.column());
   property.write_deserializer(sub_ctx);

   return std::move(sub_ctx.m_destination);
}

mb::codegen::statement::collector &NetworkDeserializeContext::operator<<(const mb::codegen::statement &stmt)
{
   return m_collector << stmt;
}

mb::codegen::statement::collector &NetworkDeserializeContext::operator<<(const mb::codegen::expression &expre)
{
   return m_collector << expre;
}

std::string NetworkDeserializeContext::type_generator() const
{
   return this->symbol().generator;
}

TypeClass NetworkDeserializeContext::type_class() const
{
   return this->symbol().type_class;
}

Symbol NetworkDeserializeContext::symbol() const
{
   auto symbol = m_symbol_table.find_symbol(m_document.package_info().full_name(), m_type.full_name());
   generator_verify(symbol.has_value(), m_type.line(), m_type.column(),
                    "could not find symbol {} in package {}", m_type.full_name(),
                    m_document.package_info().full_name());
   return std::move(*symbol);
}
}// namespace minecpp::tool::schema_compiler::generator
