#pragma once

#include <optional>
#include <string>
#include <vector>

namespace minecpp::tool::schema_compiler {

class Node
{
 public:
   Node(int line, int column);

   [[nodiscard]] int line() const;
   [[nodiscard]] int column() const;

 private:
   [[maybe_unused]] int m_line;
   [[maybe_unused]] int m_column;
};

class PackageInfo : public Node
{
 public:
   PackageInfo(int line, int column, std::vector<std::string> package);

   void add_item(const std::string &item);
   [[nodiscard]] std::string full_name() const;
   [[nodiscard]] std::string to_cpp_namespace() const;

 private:
   std::vector<std::string> m_package;
};

class GeneratorInfo : public Node
{
 public:
   GeneratorInfo(int line, int column, std::string generator);

   [[nodiscard]] const std::string &generator() const;

 private:
   std::string m_generator;
};

struct Annotation
{
   std::string key;
   std::string value;
};

class AnnotationList : Node
{
 public:
   AnnotationList();
   AnnotationList(int line, int column);

   void add_annotation(const std::string &key, const std::string &value);
   [[nodiscard]] bool has_key(std::string_view key) const;
   [[nodiscard]] std::string value_at(std::string_view key) const;

 private:
   std::vector<Annotation> m_annotations;
};

class Type : public Node
{
 public:
   Type(int line, int column, std::vector<std::string> package, std::string name);

   void add_template_arg(Type type);
   [[nodiscard]] std::string name() const;
   [[nodiscard]] std::string full_name() const;
   [[nodiscard]] std::string package_string() const;
   [[nodiscard]] std::size_t template_args_count() const;

   [[nodiscard]] std::optional<Type> template_arg_at(std::size_t index) const;

 private:
   std::string m_name;
   std::vector<std::string> m_package;
   std::vector<Type> m_template_arguments;
};

class Attribute : public Node
{
 public:
   Attribute(int line, int column, AnnotationList annotation_list, Type type, std::string name);

   [[nodiscard]] const AnnotationList &annotations() const;
   [[nodiscard]] const std::string &name() const;
   [[nodiscard]] const Type &type() const;

 private:
   AnnotationList m_annotation_list;
   Type m_type;
   std::string m_name;
};

class Record : public Node
{
 public:
   Record(int line, int column, std::string name, AnnotationList annotation_list);

   void add_attribute(Attribute attribute);

   [[nodiscard]] const AnnotationList &annotations() const;
   [[nodiscard]] const std::string &name() const;
   [[nodiscard]] const std::vector<Attribute> &attributes() const;

 private:
   std::string m_name;
   AnnotationList m_annotation_list;
   std::vector<Attribute> m_attributes;
};

class Alias : public Node
{
 public:
   Alias(int line, int column, std::string name, AnnotationList annotation_list, Type aliased_type);

   [[nodiscard]] const AnnotationList &annotations() const;
   [[nodiscard]] const std::string &name() const;
   [[nodiscard]] const Type &aliased_type() const;

 private:
   std::string m_name;
   AnnotationList m_annotation_list;
   Type m_aliased_type;
};

class Import : public Node
{
 public:
   Import(int line, int column, std::vector<std::string> path);

 private:
   std::vector<std::string> m_path;
};

class Document
{
 public:
   Document(std::string generator, PackageInfo package_info);

   void add_import(Import im);
   void add_record(Record record);
   void add_alias(Alias alias);

   [[nodiscard]] const std::string &generator() const;
   [[nodiscard]] const PackageInfo &package_info() const;
   [[nodiscard]] const std::vector<Record> &records() const;
   [[nodiscard]] const std::vector<Alias> &aliases() const;

 private:
   std::string m_generator;
   PackageInfo m_package_info;
   std::vector<Import> m_imports;
   std::vector<Record> m_records;
   std::vector<Alias> m_aliases;
};

}// namespace minecpp::tool::schema_compiler