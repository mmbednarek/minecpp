#include "generator.h"
#include <minecpp/util/string.h>
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
            return Attribute(Type(attrib.type, attrib.repeated), attrib.name, attrib.label, attrib.pos);
         });
         messages.emplace_back(msg);
      }
   }
}

Type::Type(std::string name, int repeated) : m_repeated(repeated), name(name) {
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
}
std::string Type::to_cpp_type() const {
   auto result = [](const TypeVariant variant, const std::string &name) -> std::string {
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
      }
      return name;
   }(variant, name);

   if (m_repeated == 0) {
      return result;
   }

   std::stringstream ss;
   for (int i = 0; i < m_repeated; ++i) {
      ss << "std::vector<";
   }
   ss << result;
   for (int i = 0; i < m_repeated; ++i) {
      ss << ">";
   }
   return ss.str();
}

void Type::write_value(ScriptWriter &w, const std::string_view name, const std::string_view label) const {
   if (m_repeated > 0) {
      w.line("w.begin_list(\"{1}\", {2}, {0}.size());", name, label, (m_repeated == 1 ? variant_to_nbt_tag(variant) : "minecpp::nbt::TagId::List"));
      w.scope("for (const auto &val0 : {})", name);
      for (int i = 1; i < m_repeated; ++i) {
         w.line("w.begin_list_no_header({}, val{}.size());", (m_repeated == (i + 1) ? variant_to_nbt_tag(variant) : "minecpp::nbt::TagId::List"), (i - 1));
         w.scope("for (const auto &val{} : val{})", i, i - 1);
      }
      switch (variant) {
      case TypeVariant::Int8:
         w.line("w.write_byte_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Int16:
         w.line("w.write_short_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Int32:
         w.line("w.write_int_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Int64:
         w.line("w.write_long_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::String:
         w.line("w.write_string_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Float:
         w.line("w.write_float_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Double:
         w.line("w.write_double_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Bytes:
         w.line("w.write_bytes_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Ints:
         w.line("w.write_ints_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Longs:
         w.line("w.write_longs_content(val{});", m_repeated - 1);
         break;
      case TypeVariant::Compound:
         w.line("minecpp::nbt::serialize_compound_content(w, val{});", m_repeated - 1);
         break;
      default:
         w.line("val{}.serialize_no_header(w);", m_repeated - 1);
      }
      for (int i = 0; i < m_repeated; ++i) {
         w.descope();
      }
      return;
   }

   switch (variant) {
   case TypeVariant::Int8:
      w.line("w.write_byte(\"{1}\", this->{0});", name, label);
      break;
   case TypeVariant::Int16:
      w.line("w.write_short(\"{1}\", this->{0});", name, label);
      break;
   case TypeVariant::Int32:
      w.line("w.write_int(\"{1}\", this->{0});", name, label);
      break;
   case TypeVariant::Int64:
      w.line("w.write_long(\"{1}\", this->{0});", name, label);
      break;
   case TypeVariant::String:
      w.line("w.write_string(\"{1}\", this->{0});", name, label);
      break;
   case TypeVariant::Float:
      w.line("w.write_float(\"{1}\", this->{0});", name, label);
      break;
   case TypeVariant::Double:
      w.line("w.write_double(\"{1}\", {0});", name, label);
      break;
   case TypeVariant::Bytes:
      w.line("w.write_bytes(\"{1}\", {0});", name, label);
      break;
   case TypeVariant::Ints:
      w.line("w.write_ints(\"{1}\", {0});", name, label);
      break;
   case TypeVariant::Longs:
      w.line("w.write_longs(\"{1}\", {0});", name, label);
      break;
   case TypeVariant::Compound:
      w.line("w.write_header(minecpp::nbt::TagId::Compound, \"{}\");", label);
      w.line("minecpp::nbt::serialize_compound_content(w, {});", name);
      break;
   default:
      w.line("w.begin_compound(\"{}\");", label);
      w.line("this->{0}.serialize_no_header(w);", name);
   }
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
   return *this;
}

Type::Type(TypeVariant variant, int repeated) : variant(variant),
                                                m_repeated(repeated) {}

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
            res[att.type.variant] = CompoundDeserializer{.elems{
                    {
                            .typeName = att.type.name,
                            .id = att.id,
                    }}};
            continue;
         }
         auto compound = std::any_cast<CompoundDeserializer>(&it->second);
         compound->elems.emplace_back(CompoundDeserializer::Elem{
                 .typeName = att.type.name,
                 .id = att.id,
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

static std::string put_compound_read(std::string_view name) {
   return fmt::format("{}::deserialize_no_header(r)", name);
}

static void put_list_read(std::map<TypeVariant, std::any> &attribs, ScriptWriter &w, int level = 0) {
   using minecpp::util::repeat_string;

   w.line("auto list_info{} = r.peek_list();", level);
   w.flat_scope("switch (list_info{}.tagid)", level);
   for (const auto &pair : attribs) {
      if (!pair.second.has_value())
         continue;

      if (pair.second.type() == typeid(StaticDeserializer)) {
         auto deser = std::any_cast<StaticDeserializer>(pair.second);
         w.scope("case {}:", variant_to_nbt_tag(deser.variant));
         for (int i = 1; i < level + 1; ++i) {
            w.line("{}{}{} ls(list_info{}.size);", repeat_string("std::vector<", i + 1), variant_to_type(deser.variant), std::string(i + 1, '>'), i);
            w.scope("std::generate(ls.begin(), ls.end(), [&r, &list_info{}]()", i);
         }
         w.line("std::vector<{}> ls(list_info{}.size);", variant_to_type(deser.variant), level);
         w.line("std::generate(ls.begin(), ls.end(), [&r]() {{ return {}; }});", put_static_read(std::any_cast<StaticDeserializer>(pair.second)));
         for (int i = level; i > 0; --i) {
            w.line("list_info{} = r.peek_list();", level);
            w.line("return ls");
            w.descope(");");
         }
         w.line("res.__xx_put(name, ls);");
         w.line("return;");
         w.descope();
         continue;
      }

      if (pair.second.type() == typeid(CompoundDeserializer)) {
         w.scope("case minecpp::nbt::TagId::Compound:");
         auto deser = std::any_cast<CompoundDeserializer>(pair.second);
         w.flat_scope("switch(res.__xx_get_id(name))");
         for (const auto &el : deser.elems) {
            w.scope("case {}:", el.id);
            for (int i = 1; i <= level; ++i) {
               w.line("{}{}{} ls(list_info{}.size);", repeat_string("std::vector<", i + 1), el.typeName, std::string(i + 1, '>'), i - 1);
               w.scope("if (list_info{}.size == 0)", i);
               {
                  w.line("return;");
               }
               w.descope();
               w.line("std::vector<{}> ls_first(list_info{}.size);", el.typeName, i);
               w.line("std::generate(ls_first.begin(), ls_first.end(), [&r]() {{ return {}; }});", put_compound_read(el.typeName));
               w.line("ls[0] = ls_first;");

               w.scope("std::generate(ls.begin()+1, ls.end(), [&r, &list_info{}]()", i);
               w.line("list_info{} = r.peek_list();", i);
            }
            w.line("std::vector<{}> ls(list_info{}.size);", el.typeName, level);
            w.line("std::generate(ls.begin(), ls.end(), [&r]() {{ return {}; }});", put_compound_read(el.typeName));
            for (int i = level; i > 0; --i) {
               w.line("return ls;");
               w.descope(");");
            }
            w.line("res.__xx_put(name, ls);");
            w.line("return;");
            w.descope();
         }
         w.line("}");
         w.line("break;");
         w.descope();
         continue;
      }

      if (pair.second.type() == typeid(ListDeserializer)) {
         auto deser = std::any_cast<ListDeserializer>(pair.second);
         w.scope("case minecpp::nbt::TagId::List:");
         put_list_read(deser.elems, w, level + 1);
         w.line("return;");
         w.descope();
         continue;
      }
   }
   w.line("}");
   w.scope("for (std::size_t i = 0; i < list_info{}.size; ++i)", level);
   w.line("r.skip_payload(list_info{}.tagid);", level);
   w.descope();
}

static void put_deserializer(std::map<TypeVariant, std::any> &attribs, ScriptWriter &w) {
   w.flat_scope("switch (tagid)");
   for (const auto &pair : attribs) {
      if (!pair.second.has_value())
         continue;

      if (pair.second.type() == typeid(StaticDeserializer)) {
         auto var = std::any_cast<StaticDeserializer>(pair.second);
         w.line("case {}: ", variant_to_nbt_tag(var.variant));
         w.ident();
         w.line("res.__xx_put(name, {});", put_static_read(var));
         w.line("return;");
         w.deindent();
         continue;
      }

      if (pair.second.type() == typeid(CompoundDeserializer)) {
         w.scope("case minecpp::nbt::TagId::Compound:");
         auto deser = std::any_cast<CompoundDeserializer>(pair.second);
         w.scope("switch(res.__xx_get_id(name))");
         {
            for (const auto &el : deser.elems) {
               w.line("case {}:", el.id);
               w.ident();
               w.line("res.__xx_put(name, {}::deserialize_no_header(r));", el.typeName);
               w.line("return;");
               w.deindent();
            }
         }
         w.descope();
         w.line("break;");
         w.descope();
         continue;
      }

      if (pair.second.type() == typeid(ListDeserializer)) {
         w.scope("case minecpp::nbt::TagId::List:");
         auto deser = std::any_cast<ListDeserializer>(pair.second);
         put_list_read(deser.elems, w);
         w.line("return;");
         w.descope();
      }
   }
   w.line("}");
   w.line("r.skip_payload(tagid);");
}

Message::Message(const std::string &name) : name(name) {}

Attribute::Attribute(Type t, const std::string_view name, const std::string_view label, int id) : type(std::move(t)), name(name), label(label.empty() ? name : label), id(id) {}

void generate_header(Structure &s, std::ostream &output) {
   ScriptWriter w(output);
   w.line("// Generated using ProtoNBT generator");
   w.line("#pragma once");
   w.line("#include <iostream>");
   w.line("#include <map>");
   w.line("#include <mb/result.h>");
   w.line("#include <minecpp/nbt/writer.h>");
   w.line("#include <minecpp/nbt/reader.h>");
   w.line("#include <string>");
   w.line("#include <vector>");
   w.line();
   w.flat_scope("namespace {}", s.package);
   w.line();
   w.line("struct __nbt_offset { std::size_t offset, size; int id; };");
   w.line();
   std::for_each(s.messages.begin(), s.messages.end(), [&w](const auto &el) {
      w.line("struct {};", el.name);
   });
   w.line();
   std::for_each(s.messages.begin(), s.messages.end(), [&w](const auto &el) {
      w.scope("struct {}", el.name);
      std::for_each(el.attribs.begin(), el.attribs.end(), [&w](const Attribute &attrib) {
         w.line("{} {}{};", attrib.type.to_cpp_type(), attrib.name, "{}");
      });

      w.line();
      w.line("{}() = default;", el.name);
      w.line();
      w.line("void serialize_no_header(minecpp::nbt::Writer &w) const;");
      w.line("void serialize(std::ostream &out, std::string_view name = \"\") const;");
      w.line();
      w.line("static {} deserialize_no_header(minecpp::nbt::Reader &r);", el.name);
      w.line("static {} deserialize(std::istream &in);", el.name);
      w.line();
      w.line_ignore("private:");
      w.line("static std::unordered_map<std::string, __nbt_offset> __xx_offsets;");
      w.line("int __xx_get_id(const std::string &name) const;");
      w.line();
      w.line("template<typename T>");
      w.scope("void __xx_put(const std::string &name, T value)");
      {
         w.line("auto it = __xx_offsets.find(name);");
         w.line("if (it == __xx_offsets.end()) return;");
         w.line("if (it->second.size != sizeof(T)) return;");
         w.line("T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);");
         w.line("ptr->~T();");
         w.line("*ptr = std::forward<T>(value);");
      }
      w.descope();
      w.descope(";");
      w.line();
   });
   w.descope("//namespace {}", s.package);
}

result<empty> generate_cpp(Structure &s, std::ostream &output, std::string &header_file) {
   ScriptWriter w(output);
   w.line("// Generated using ProtoNBT generator");
   w.line("#include \"{}\"", header_file);
   w.line();
   w.flat_scope("namespace {}", s.package);
   w.line();
   for (const auto &el : s.messages) {
      w.scope("int {}::__xx_get_id(const std::string &name) const", el.name);
      {
         w.line("auto it = __xx_offsets.find(name);");
         w.line("if (it == __xx_offsets.end()) return -1;");
         w.line("return it->second.id;");
      }
      w.descope();
      w.line();
      w.scope("void {}::serialize_no_header(minecpp::nbt::Writer &w) const", el.name);
      {
         std::for_each(el.attribs.begin(), el.attribs.end(), [&w](const Attribute &attrib) {
            attrib.type.write_value(w, attrib.name, attrib.label);
         });
         w.line("w.end_compound();");
      }
      w.descope();
      w.line();
      w.scope("void {}::serialize(std::ostream &out, const std::string_view name) const", el.name);
      {
         w.line("minecpp::nbt::Writer w(out);");
         w.line("w.begin_compound(name);");
         w.line("this->serialize_no_header(w);");
      }
      w.descope();
      w.line();
      w.scope("std::unordered_map<std::string, __nbt_offset> {}::__xx_offsets", el.name);
      std::for_each(el.attribs.begin(), el.attribs.end(), [&w, el](const Attribute &attrib) {
         w.line("{{\"{0}\", {{offsetof({2}, {1}), sizeof({2}::{1}), {3}}}}},", attrib.label, attrib.name, el.name, attrib.id);
      });
      w.descope(";");
      w.line();
      w.scope("{0} {0}::deserialize_no_header(minecpp::nbt::Reader &r)", el.name);
      {
         w.line("{} res;", el.name);
         w.scope("r.read_compound([&res] (minecpp::nbt::Reader &r, NBT::TagId tagid, const std::string &name)");
         {
            auto deser = make_message_des(el.attribs);
            put_deserializer(deser, w);
         }
         w.descope(");");
         w.line();
         w.line("return res;");
      }
      w.descope();
      w.line();
      w.scope("{0} {0}::deserialize(std::istream &in)", el.name);
      {
         w.line("minecpp::nbt::Reader r(in);");
         w.line("auto peek = r.peek_tag();");
         w.scope("if (peek.id != minecpp::nbt::TagId::Compound)");
         {
            w.line("return {}();", el.name);
         }
         w.descope();
         w.line("return {}::deserialize_no_header(r);", el.name);
      }
      w.descope();
      w.line();
   }

   w.descope("// namespace {}", s.package);
   return result_ok;
}

}// namespace Semantics
