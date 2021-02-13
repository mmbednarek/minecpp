#pragma once
#include "ast.h"
#include <any>
#include <map>
#include <minecpp/error/result.h>
#include <minecpp/util/scriptw.h>
#include <string>
#include <variant>
#include <vector>

namespace Semantics {

enum class TypeVariant {
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
   Compound
};

struct Type {
   TypeVariant variant = TypeVariant::Struct;
   int m_repeated = 0;
   std::string name;

   Type() = default;
   Type(std::string name, int repeated);
   Type(TypeVariant variant, int repeated);
   Type(const Type &type) = default;
   Type &operator=(const Type &type);

   bool operator==(const Type &other) const;
   bool operator<(const Type &other) const;

   [[nodiscard]] std::string to_cpp_type() const;
   void write_value(minecpp::util::ScriptWriter &w, std::string_view name, std::string_view label) const;
   [[nodiscard]] std::string nbt_tagid() const;
};

struct Attribute {
   Type type;
   std::string name;
   std::string label;
   int id;

   Attribute() = default;
   Attribute(Type t, std::string_view name, std::string_view label, int id);
};

struct Message {
   std::string name;
   std::vector<Attribute> attribs;
   Message() = default;
   explicit Message(const std::string &name);
};

struct Structure {
   std::string version;
   std::string package;
   std::vector<Message> messages;

   explicit Structure(std::vector<Syntax::Ast::Node> nodes);
};

struct StaticDeserializer {
   TypeVariant variant;
};

struct CompoundDeserializer {
   struct Elem {
      std::string typeName;
      int id;
   };
   std::vector<Elem> elems;
};

struct ListDeserializer {
   std::map<TypeVariant, std::any> elems;
};

std::map<TypeVariant, std::any> make_message_des(const std::vector<Attribute> &attribs);

void generate_header(Structure &s, std::ostream &output);
result<empty> generate_cpp(Structure &s, std::ostream &output, std::string &header_file);

std::string variant_to_nbt_tag(TypeVariant variant);
std::string put_static_read(const StaticDeserializer &des);
std::string variant_to_type(TypeVariant variant);

}// namespace Semantics