#include "generator.h"
#include <set>
#include <sstream>
#include <utility>

namespace Semantics {

using minecpp::util::ScriptWriter;

std::string variant_to_nbt_tag(TypeVariant variant) {
   switch (variant) {
   case TypeVariant::Int8: return "minecpp::nbt::TagId::Byte";
   case TypeVariant::Int16: return "minecpp::nbt::TagId::Short";
   case TypeVariant::Int32: return "minecpp::nbt::TagId::Int";
   case TypeVariant::Int64: return "minecpp::nbt::TagId::Long";
   case TypeVariant::String: return "minecpp::nbt::TagId::String";
   case TypeVariant::Float: return "minecpp::nbt::TagId::Float";
   case TypeVariant::Double: return "minecpp::nbt::TagId::Double";
   case TypeVariant::Bytes: return "minecpp::nbt::TagId::ByteArray";
   case TypeVariant::Ints: return "minecpp::nbt::TagId::IntArray";
   case TypeVariant::Longs: return "minecpp::nbt::TagId::LongArray";
   default: break;
   }
   return "minecpp::nbt::TagId::Compound";
}

std::string variant_to_type(TypeVariant variant) {
   switch (variant) {
   case TypeVariant::Int8: return "std::int8_t";
   case TypeVariant::Int16: return "std::int16_t";
   case TypeVariant::Int32: return "std::int32_t";
   case TypeVariant::Int64: return "std::int64_t";
   case TypeVariant::String: return "std::string";
   case TypeVariant::Float: return "float";
   case TypeVariant::Double: return "double";
   case TypeVariant::Bytes: return "std::vector<std::uint8_t>";
   case TypeVariant::Ints: return "std::vector<std::int32_t>";
   case TypeVariant::Longs: return "std::vector<std::int64_t>";
   default: break;
   }
   return "";
}

Structure::Structure(std::vector<Syntax::Ast::Node> nodes) {
   for (auto &node : nodes) {
      if (std::holds_alternative<Syntax::Ast::SyntaxInfo>(node)) {
         auto &ver = std::get<Syntax::Ast::SyntaxInfo>(node).version;
         if (ver.size() < 2) {
            continue;
         }
         version = ver.substr(1, ver.size() - 2);
         continue;
      }
      if (std::holds_alternative<Syntax::Ast::PackageInfo>(node)) {
         auto pkg = std::get<Syntax::Ast::PackageInfo>(node).package;
         if (pkg.empty()) {
            continue;
         }
         std::stringstream ss;
         auto iter = pkg.begin();
         ss << *iter;
         std::for_each(iter + 1, pkg.end(), [&ss](const auto &e) {
            ss << "::" << e;
         });
         package = ss.str();
         continue;
      }
      if (std::holds_alternative<Syntax::Ast::Message>(node)) {
         auto astMsg = std::get<Syntax::Ast::Message>(node);
         Message msg(astMsg.name);
         msg.attribs.resize(astMsg.attributes.size());
         std::transform(astMsg.attributes.begin(), astMsg.attributes.end(), msg.attribs.begin(), [](const Syntax::Ast::Attribute &attrib) {
            return Attribute(Type(attrib.package, attrib.type, attrib.repeated, attrib.subtype), attrib.name, attrib.label, attrib.pos);
         });
         messages.emplace_back(msg);
         continue;
      }
      if (std::holds_alternative<Syntax::Ast::Import>(node)) {
         auto astImport = std::get<Syntax::Ast::Import>(node);
         imports.emplace_back(astImport.path);
      }
   }
}

Type::Type(const std::vector<std::string> &ns, const std::string &name, int repeated, const std::string &subtype) : m_repeated(repeated),
                                                                                                                    ns(ns),
                                                                                                                    name(name),
                                                                                                                    subtype(subtype.empty() ? nullptr : std::make_unique<Type>(std::vector<std::string>(), subtype, 0, "")) {
   if (name == "int8") {
      variant = TypeVariant::Int8;
      return;
   }
   if (name == "int16") {
      variant = TypeVariant::Int16;
      return;
   }
   if (name == "int32") {
      variant = TypeVariant::Int32;
      return;
   }
   if (name == "int64") {
      variant = TypeVariant::Int64;
      return;
   }
   if (name == "string") {
      variant = TypeVariant::String;
      return;
   }
   if (name == "float") {
      variant = TypeVariant::Float;
      return;
   }
   if (name == "double") {
      variant = TypeVariant::Double;
      return;
   }
   if (name == "bytes") {
      variant = TypeVariant::Bytes;
      return;
   }
   if (name == "ints") {
      variant = TypeVariant::Ints;
      return;
   }
   if (name == "longs") {
      variant = TypeVariant::Longs;
      return;
   }
   if (name == "compound") {
      variant = TypeVariant::Compound;
      return;
   }
   if (name == "map") {
      variant = TypeVariant::Map;
      return;
   }
}

std::string Type::to_cpp_type() const {
   auto result = [](const TypeVariant variant, const std::string &name, const std::unique_ptr<Type> &subtype) -> std::string {
      switch (variant) {
      case TypeVariant::Int8: return "std::int8_t";
      case TypeVariant::Int16: return "std::int16_t";
      case TypeVariant::Int32: return "std::int32_t";
      case TypeVariant::Int64: return "std::int64_t";
      case TypeVariant::String: return "std::string";
      case TypeVariant::Float: return "float";
      case TypeVariant::Double: return "double";
      case TypeVariant::Bytes: return "std::vector<std::uint8_t>";
      case TypeVariant::Ints: return "std::vector<std::int32_t>";
      case TypeVariant::Longs: return "std::vector<std::int64_t>";
      case TypeVariant::Compound: return "minecpp::nbt::CompoundContent";
      case TypeVariant::Map: return fmt::format("std::map<std::string, {}>", subtype->to_cpp_type());
      }
      return name;
   }(variant, name, subtype);

   if (m_repeated == 0 && ns.empty()) {
      return result;
   }

   std::stringstream ss;
   for (int i = 0; i < m_repeated; ++i) {
      ss << "std::vector<";
   }
   for (const auto &item : ns) {
      ss << item << "::";
   }
   ss << result;
   for (int i = 0; i < m_repeated; ++i) {
      ss << ">";
   }
   return ss.str();
}

std::string Type::nbt_tagid() const {
   if (m_repeated) {
      return "minecpp::nbt::TagId::List";
   }
   switch (variant) {
   case TypeVariant::Int8: return "minecpp::nbt::TagId::Byte";
   case TypeVariant::Int16: return "minecpp::nbt::TagId::Short";
   case TypeVariant::Int32: return "minecpp::nbt::TagId::Int";
   case TypeVariant::Int64: return "minecpp::nbt::TagId::Long";
   case TypeVariant::String: return "minecpp::nbt::TagId::String";
   case TypeVariant::Float: return "minecpp::nbt::TagId::Float";
   case TypeVariant::Double: return "minecpp::nbt::TagId::Double";
   case TypeVariant::Bytes: return "minecpp::nbt::TagId::ByteArray";
   case TypeVariant::Ints: return "minecpp::nbt::TagId::IntArray";
   case TypeVariant::Longs: return "minecpp::nbt::TagId::LongArray";
   }
   return "minecpp::nbt::TagId::Compound";
}

bool Type::operator==(const Type &other) const {
   return variant == other.variant;
}

bool Type::operator<(const Type &other) const {
   return variant < other.variant;
}

Type &Type::operator=(const Type &type) {
   variant = type.variant;
   m_repeated = type.m_repeated;
   name = type.name;
   subtype = type.subtype == nullptr ? nullptr : std::make_unique<Type>(*type.subtype);
   return *this;
}

Type::Type(TypeVariant variant, int repeated) : variant(variant),
                                                m_repeated(repeated) {}

Type::Type(const Type &other) : variant(other.variant),
                                m_repeated(other.m_repeated),
                                ns(other.ns),
                                name(other.name),
                                subtype(other.subtype == nullptr ? nullptr : std::make_unique<Type>(*other.subtype)) {}

Type::Type(Type &&other) noexcept : variant(std::exchange(other.variant, TypeVariant::Struct)),
                                    m_repeated(std::exchange(other.m_repeated, 0)),
                                    ns(std::exchange(other.ns, {})),
                                    name(std::move(other.name)),
                                    subtype(std::move(other.subtype)) {}

Type &Type::operator=(Type &&other) noexcept {
   variant = std::exchange(other.variant, TypeVariant::Struct);
   m_repeated = std::exchange(other.m_repeated, 0);
   ns = std::exchange(other.ns, {});
   name = std::move(other.name);
   subtype = std::move(other.subtype);
   return *this;
}

std::map<TypeVariant, std::any> make_message_des(const std::vector<Attribute> &attribs) {
   std::map<TypeVariant, std::any> res;
   std::vector<Attribute> list;

   for (const auto &att : attribs) {
      if (att.type.m_repeated > 0) {
         auto copied = att;
         --copied.type.m_repeated;
         list.emplace_back(std::move(copied));
         continue;
      }
      if (att.type.variant == TypeVariant::Struct) {
         auto it = res.find(TypeVariant::Struct);
         if (it == res.end()) {
            res[TypeVariant::Struct] = CompoundDeserializer{.elems{
                    {
                            .kind = CompoundKind::Struct,
                            .typeName = att.type.to_cpp_type(),
                            .name = att.name,
                            .id = att.id,
                            .label = att.label,
                    }}};
            continue;
         }
         auto compound = std::any_cast<CompoundDeserializer>(&it->second);
         compound->elems.emplace_back(CompoundDeserializer::Elem{
                 .kind = CompoundKind::Struct,
                 .typeName = att.type.to_cpp_type(),
                 .name = att.name,
                 .id = att.id,
                 .label = att.label,
         });
         continue;
      }
      if (att.type.variant == TypeVariant::Map) {
         if (att.type.subtype == nullptr) {
            continue;
         }
         auto it = res.find(TypeVariant::Struct);
         if (it == res.end()) {
            res[TypeVariant::Struct] = CompoundDeserializer{.elems{
                    {
                            .kind = CompoundKind::Map,
                            .typeName = att.type.to_cpp_type(),
                            .name = att.name,
                            .id = att.id,
                            .subtype = att.type.subtype->variant,
                            .subtypeName = att.type.subtype->name,
                            .label = att.label,
                    },
            }};
            continue;
         }
         auto compound = std::any_cast<CompoundDeserializer>(&it->second);
         compound->elems.emplace_back(CompoundDeserializer::Elem{
                 .kind = CompoundKind::Map,
                 .typeName = att.type.to_cpp_type(),
                 .name = att.name,
                 .id = att.id,
                 .subtype = att.type.subtype->variant,
                 .subtypeName = att.type.subtype->to_cpp_type(),
                 .label = att.label,
         });
         continue;
      }
      if (att.type.variant == TypeVariant::Compound) {
         auto it = res.find(TypeVariant::Struct);
         if (it == res.end()) {
            res[TypeVariant::Struct] = CompoundDeserializer{.elems{
                    {
                            .kind = CompoundKind::Compound,
                            .typeName = att.type.to_cpp_type(),
                            .name = att.name,
                            .id = att.id,
                            .label = att.label,
                    },
            }};
            continue;
         }
         auto compound = std::any_cast<CompoundDeserializer>(&it->second);
         compound->elems.emplace_back(CompoundDeserializer::Elem{
                 .kind = CompoundKind::Compound,
                 .typeName = att.type.to_cpp_type(),
                 .name = att.name,
                 .id = att.id,
                 .label = att.label,
         });
         continue;
      }
      res[att.type.variant] = StaticDeserializer{
              .variant = att.type.variant,
      };
   }
   if (!list.empty()) {
      res[TypeVariant::List] = ListDeserializer{
              .elems = make_message_des(list),
      };
   }

   return res;
}

std::string put_static_read(const StaticDeserializer &des) {
   switch (des.variant) {
   case TypeVariant::Int8:
      return "r.read_byte()";
   case TypeVariant::Int16:
      return "r.read_short()";
   case TypeVariant::Int32:
      return "r.read_int()";
   case TypeVariant::Int64:
      return "r.read_long()";
   case TypeVariant::String:
      return "r.read_str()";
   case TypeVariant::Float:
      return "r.read_float32()";
   case TypeVariant::Double:
      return "r.read_float64()";
   case TypeVariant::Bytes:
      return "r.read_byte_vector()";
   case TypeVariant::Ints:
      return "r.read_int_vec()";
   case TypeVariant::Longs:
      return "r.read_long_vec()";
   case TypeVariant::Compound:
      return "r.read_compound_content()";
   default:
      break;
   }
   return "";
}

Message::Message(std::string name) : name(std::move(name)) {}

Attribute::Attribute(Type t, const std::string_view name, const std::string_view label, int id) : type(std::move(t)), name(name), label(label.empty() ? name : label), id(id) {}

}// namespace Semantics
