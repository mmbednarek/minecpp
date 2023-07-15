#include "Ast.h"

#include <algorithm>
#include <fmt/core.h>
#include <sstream>
#include <utility>

namespace minecpp::tool::schema_compiler {

Node::Node(int line, int column) :
    m_line{line},
    m_column{column}
{
}

int Node::line() const
{
   return m_line;
}

int Node::column() const
{
   return m_column;
}

PackageInfo::PackageInfo(int line, int column, std::vector<std::string> package) :
    Node(line, column),
    m_package(std::move(package))
{
}

void PackageInfo::add_item(const std::string &item)
{
   m_package.push_back(item);
}

std::string PackageInfo::full_name() const
{
   if (m_package.empty())
      return {};

   std::stringstream ss;
   ss << m_package[0];
   std::for_each(m_package.begin() + 1, m_package.end(),
                 [&ss](const std::string &name) { ss << "." << name; });

   return ss.str();
}

std::string PackageInfo::to_cpp_namespace() const
{
   if (m_package.empty())
      return {};

   std::stringstream ss;
   ss << m_package[0];
   std::for_each(m_package.begin() + 1, m_package.end(),
                 [&ss](const std::string &name) { ss << "::" << name; });

   return ss.str();
}

Type::Type(int line, int column, std::vector<std::string> package, std::string name) :
    Node(line, column),
    m_name(std::move(name)),
    m_package(std::move(package))
{
}

void Type::add_template_arg(Type type)
{
   m_template_arguments.emplace_back(std::move(type));
}

std::string Type::full_name() const
{
   auto package = this->package_string();
   if (package.empty())
      return m_name;

   return fmt::format("{}.{}", package, m_name);
}

std::string Type::package_string() const
{
   if (m_package.empty())
      return {};

   std::stringstream ss;
   ss << m_package[0];
   std::for_each(m_package.begin() + 1, m_package.end(),
                 [&ss](const std::string &part) { ss << "." << part; });

   return ss.str();
}

std::string Type::name() const
{
   return m_name;
}

std::optional<Type> Type::template_arg_at(std::size_t index) const
{
   if (index >= m_template_arguments.size())
      return std::nullopt;

   return m_template_arguments.at(index);
}

std::size_t Type::template_args_count() const
{
   return m_template_arguments.size();
}

Attribute::Attribute(int line, int column, AnnotationList annotation_list, Type type, std::string name) :
    Node(line, column),
    m_annotation_list(std::move(annotation_list)),
    m_type(std::move(type)),
    m_name(std::move(name))
{
}

const AnnotationList &Attribute::annotations() const
{
   return m_annotation_list;
}

const std::string &Attribute::name() const
{
   return m_name;
}

const Type &Attribute::type() const
{
   return m_type;
}

Record::Record(int line, int column, std::string name, AnnotationList annotation_list) :
    Node(line, column),
    m_name(std::move(name)),
    m_annotation_list(std::move(annotation_list))
{
}

void Record::add_attribute(Attribute attribute)
{
   m_attributes.emplace_back(std::move(attribute));
}

const std::string &Record::name() const
{
   return m_name;
}

const std::vector<Attribute> &Record::attributes() const
{
   return m_attributes;
}

const AnnotationList &Record::annotations() const
{
   return m_annotation_list;
}

Import::Import(int line, int column, std::vector<std::string> path) :
    Node(line, column),
    m_path(std::move(path))
{
}

Document::Document(std::string generator, PackageInfo package_info) :
    m_generator(std::move(generator)),
    m_package_info(std::move(package_info))
{
}

void Document::add_import(Import im)
{
   m_imports.emplace_back(std::move(im));
}

void Document::add_record(Record record)
{
   m_records.emplace_back(std::move(record));
}

const std::vector<Record> &Document::records() const
{
   return m_records;
}

const PackageInfo &Document::package_info() const
{
   return m_package_info;
}

const std::string &Document::generator() const
{
   return m_generator;
}

AnnotationList::AnnotationList() :
    Node(0, 0)
{
}

AnnotationList::AnnotationList(int line, int column) :
    Node(line, column)
{
}

void AnnotationList::add_annotation(const std::string &key, const std::string &value)
{
   m_annotations.push_back(Annotation{key, value});
}

bool AnnotationList::has_key(std::string_view key) const
{
   auto it = std::find_if(
           m_annotations.begin(), m_annotations.end(),
           [seeked_key = key](const Annotation &annotation) { return annotation.key == seeked_key; });
   return it != m_annotations.end();
}

std::string AnnotationList::value_at(std::string_view key) const
{
   auto it = std::find_if(
           m_annotations.begin(), m_annotations.end(),
           [seeked_key = key](const Annotation &annotation) { return annotation.key == seeked_key; });
   return it->value;
}

GeneratorInfo::GeneratorInfo(int line, int column, std::string generator) :
    Node(line, column),
    m_generator(std::move(generator))
{
}

const std::string &GeneratorInfo::generator() const
{
   return m_generator;
}
}// namespace minecpp::tool::schema_compiler
