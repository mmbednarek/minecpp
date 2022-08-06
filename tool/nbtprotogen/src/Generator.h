#pragma once
#include "Ast.h"
#include <any>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace Semantics {

enum class TypeVariant
{
   Int8,
   Int16,
   Int32,
   Int64,
   String,
   Float,
   Double,
   Bytes,
   Ints,
   Longs,
   Struct,
   List,
   Compound,
   Map
};

struct Type
{
   TypeVariant variant = TypeVariant::Struct;
   int m_repeated      = 0;
   bool m_optional     = false;
   std::vector<std::string> ns;
   std::string name;
   std::unique_ptr<Type> subtype;// subtype for map

   Type() = default;
   Type(std::vector<std::string> ns, const std::string &name, int repeated, bool optional,
        const std::string &subtype);
   Type(TypeVariant variant, int repeated);
   Type(const Type &type);
   Type &operator=(const Type &type);
   Type(Type &&other) noexcept;
   Type &operator=(Type &&other) noexcept;

   bool operator==(const Type &other) const;
   bool operator<(const Type &other) const;

   [[nodiscard]] std::string to_cpp_type() const;
   [[nodiscard]] std::string nbt_tagid() const;
};

struct Attribute
{
   Type type;
   std::string name;
   std::string label;
   int id{};

   Attribute() = default;
   Attribute(Type t, std::string_view name, std::string_view label, int id);
};

struct Message
{
   std::string name;
   std::vector<Attribute> attribs;
   Message() = default;
   explicit Message(std::string name);
};

struct Structure
{
   std::string version;
   std::string package;
   std::vector<Message> messages;
   std::vector<std::string> imports;

   explicit Structure(std::vector<Syntax::Ast::Node> nodes);
};

struct StaticDeserializer
{
   TypeVariant variant;
};

enum class CompoundKind
{
   Struct,
   Map,
   Compound
};

struct CompoundDeserializer
{
   struct Elem
   {
      CompoundKind kind = CompoundKind::Struct;
      std::string typeName;
      std::string name;
      int id;
      TypeVariant subtype;
      std::string subtypeName;
      std::string label;
   };

   std::vector<Elem> elems;
};

struct ListDeserializer
{
   std::map<TypeVariant, std::any> elems;
};

std::map<TypeVariant, std::any> make_message_des(const std::vector<Attribute> &attribs);

std::string variant_to_nbt_tag(TypeVariant variant);
std::string put_static_read(const StaticDeserializer &des);
std::string variant_to_type(TypeVariant variant);

}// namespace Semantics