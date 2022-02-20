#include "structgen.h"
#include <fmt/format.h>
#include <mb/codegen/class.h>
#include <mb/codegen/lambda.h>
#include <sstream>

namespace minecpp::tool::nbt_idl {

constexpr auto g_offset_class_name = "__nbt_idl_offset";
constexpr auto g_offset_attribute = "__xx_offsets";
constexpr auto g_get_offset_id = "__xx_get_id";
constexpr auto g_put_method = "__xx_put";
constexpr auto g_offset_class_constant = "NBT_IDL_OFFSET_CLASS";

Generator::Generator(Semantics::Structure &structure, const std::string &module_name, const std::string &header_path) : m_header_name(make_header_constant(structure.package, module_name)),
                                                                                                                        m_component(structure.package, m_header_name) {
   using namespace mb::codegen;
   m_component.header_include("iostream");
   m_component.header_include("map");
   m_component.header_include("mb/result.h");
   m_component.header_include("mb/int.h");
   m_component.header_include("minecpp/nbt/writer.h");
   m_component.header_include("minecpp/nbt/reader.h");
   m_component.header_include("string");
   m_component.header_include("vector");
   if (header_path.empty()) {
      m_component.source_include_local(fmt::format("{}.nbt.h", module_name));
   } else {
      m_component.source_include(fmt::format("{}/{}.nbt.h", header_path, module_name));
   }

   for (const auto &path : structure.imports) {
      m_component.header_include(path + ".h");
   }

   class_spec offset_class(g_offset_class_name, fmt::format("{}_OFFSET_CLASS", m_header_name));
   offset_class.add_public("mb::size", "offset");
   offset_class.add_public("mb::size", "size");
   offset_class.add_public("int", "id");
   m_component << offset_class;

   std::for_each(structure.messages.begin(), structure.messages.end(), [this](const Semantics::Message &msg) {
      class_spec message_class(msg.name);
      std::for_each(msg.attribs.begin(), msg.attribs.end(), [&message_class](const Semantics::Attribute &attr) {
         message_class.add_public(attr.type.to_cpp_type(), attr.name);
      });

      std::map<std::string, std::vector<Semantics::Attribute>> type_names{};
      for (auto &attrib : msg.attribs) {
         auto name = attrib.type.to_cpp_type();
         type_names[name].push_back(attrib);
      }

      // public:

      message_class.add_public(default_constructor());

      // void serialize_no_header()
      message_class.add_public(method("void", "serialize_no_header", {{"minecpp::nbt::Writer", "&w"}}, true, [&msg](statement::collector &col) {
         std::for_each(msg.attribs.begin(), msg.attribs.end(), [&col](const Semantics::Attribute &attr) {
            col << call("w.write_header", raw(attr.type.nbt_tagid()), raw("\"{}\"", attr.label));
            put_serialize_logic(col, attr.type, raw(attr.name));
         });
         col << call("w.end_compound");
      }));

      // void serialize()
      message_class.add_public(method("void", "serialize", {{"std::ostream", "&out"}, {"std::string_view", "name"}}, true, [](statement::collector &col) {
         col << call("minecpp::nbt::Writer w", raw("out"));
         col << call("w.begin_compound", raw("name"));
         col << call("serialize_no_header", raw("w"));
      }));

      // static Msg deserialize_no_header
      message_class.add_public(static_method(msg.name, "deserialize_no_header", {{"minecpp::nbt::Reader", "&r"}}, [&msg](statement::collector &col) {
         col << raw("{} res", msg.name);
         col << call("r.read_compound", lambda(
                                                {{"minecpp::nbt::Reader", "&r"}, {"minecpp::nbt::TagId", "tagid"}, {"const std::string", "&name"}}, [&msg](statement::collector &col) {
                                                   put_deserialize_logic(msg, col);
                                                },
                                                raw("&res")));
         col << raw("return res");
      }));

      // static Msg deserialize
      message_class.add_public(static_method(msg.name, "deserialize", {{"std::istream", "&in"}}, [&msg](statement::collector &col) {
         col << call("minecpp::nbt::Reader r", raw("in"));
         col << assign("auto peek", call("r.peek_tag"));
         col << if_statement(raw("peek.id != minecpp::nbt::TagId::Compound"), [&msg](statement::collector &col) {
            col << raw("return {}()", msg.name);
         });
         col << raw("return {}::deserialize_no_header(r)", msg.name);
      }));

      // public:

      items offset_map;
      std::for_each(msg.attribs.begin(), msg.attribs.end(), [&msg, &offset_map](const Semantics::Attribute &attr) {
         struct_constructor pair;
         pair.add(raw("\"{}\"", attr.label));
         struct_constructor offset;
         offset.add(call("offsetof", raw(msg.name), raw(attr.name)));
         offset.add(call("sizeof", raw("{}::{}", msg.name, attr.name)));
         offset.add(raw("{}", attr.id));
         pair.add(offset);
         offset_map.add(pair);
      });
      // static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
      //      message_class.add_private(static_attribute("std::unordered_map<std::string, __nbt_idl_offset>", g_offset_attribute, offset_map));

      // void __x_get_id()
      //      message_class.add_private(method("int", g_get_offset_id, {{"const std::string", "&name"}}, true, [](statement::collector &col) {
      //         col << assign("auto it", call("__xx_offsets.find", raw("name")));
      //         col << if_statement(raw("it == __xx_offsets.end()"), [](statement::collector &col) {
      //            col << raw("return -1");
      //         });
      //         col << raw("return it->second.id");
      //      }));

      // void __xx_put()
      message_class.add_private(method_template("void", g_put_method, {{"typename", "T"}}, {{"const std::string", "&name"}, {"T", "&&value"}}, [&type_names](statement::collector &col) {
         for (auto &pair : type_names) {
            if (pair.second.empty())
               continue;

            auto stmt = if_statement(raw("std::is_same_v<T, {}>", pair.first), [&pair](statement::collector &col) {
               for (auto &item : pair.second) {
                  col << if_statement(raw("name == \"{}\"", item.label), [&item](statement::collector &col) {
                     col << raw("this->{} = std::forward<T>(value)", item.name);
                     col << raw("return");
                  });
               }
               col << raw("return");
            });
            stmt.with_constexpr();
            col << stmt;
         }
      }));

      m_component << message_class;
   });
}

void Generator::write_header(std::ostream &out) {
   m_component.write_header(out);
}

void Generator::write_source(std::ostream &out) {
   m_component.write_source(out);
}

std::string make_header_constant(const std::string &package_name, const std::string &module_name) {
   std::stringstream result;
   std::for_each(package_name.begin(), package_name.end(), [&result, sep = false](const char c) mutable {
      if (sep) {
         sep = false;
         if (c == ':') {
            result << "_";
            return;
         }
      }

      if ((c >= 'a' && c <= 'z')) {
         result << static_cast<char>(toupper(c));
      } else if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
         result << c;
      } else if (c == ':') {
         sep = true;
      }
   });
   result << "_";
   std::string lower_module(module_name.size(), ' ');
   std::transform(module_name.begin(), module_name.end(), lower_module.begin(), toupper);
   result << lower_module << "_H";
   return result.str();
}

void put_deserialize_logic(const Semantics::Message &msg, mb::codegen::statement::collector &col) {
   using namespace mb::codegen;
   auto attribs = Semantics::make_message_des(msg.attribs);
   switch_statement tag_switch(raw("tagid"));
   std::for_each(attribs.begin(), attribs.end(), [&tag_switch](const std::pair<const Semantics::TypeVariant, std::any> &pair) {
      if (!pair.second.has_value())
         return;

      if (pair.second.type() == typeid(Semantics::StaticDeserializer)) {
         auto deserializer = std::any_cast<Semantics::StaticDeserializer>(pair.second);
         tag_switch.add_noscope(raw(Semantics::variant_to_nbt_tag(deserializer.variant)), [&deserializer](statement::collector &col) {
            col << call("res.__xx_put", raw("name"), raw(Semantics::put_static_read(deserializer)));
            col << raw("return");
         });
         return;
      }
      if (pair.second.type() == typeid(Semantics::CompoundDeserializer)) {
         auto deserializer = std::any_cast<Semantics::CompoundDeserializer>(pair.second);
         tag_switch.add_noscope(raw("minecpp::nbt::TagId::Compound"), [&deserializer](statement::collector &col) {
            std::for_each(deserializer.elems.begin(), deserializer.elems.end(), [&col](const Semantics::CompoundDeserializer::Elem &elem) {
               col << if_statement(raw("name == \"{}\"", elem.label), [&elem](statement::collector &col) {
                  switch (elem.kind) {
                  case Semantics::CompoundKind::Struct:
                     col << call("res.__xx_put", raw("name"), raw("{}::deserialize_no_header(r)", elem.typeName));
                     col << raw("return");
                     return;
                  case Semantics::CompoundKind::Map:
                     col << call("r.read_compound", lambda(
                                                            {{"minecpp::nbt::Reader", "&r"}, {"minecpp::nbt::TagId", "tagid"}, {"const std::string", "&name"}}, [&elem](statement::collector &col) {
                                                               col << if_statement(raw("tagid != {}", Semantics::variant_to_nbt_tag(elem.subtype)), [](statement::collector &col) {
                                                                  col << call("r.skip_payload", raw("tagid"));
                                                                  col << raw("return");
                                                               });
                                                               if (elem.subtype == Semantics::TypeVariant::Struct) {
                                                                  col << method_call(raw("res.{}", elem.name), "insert", call("std::make_pair", raw("name"), call(raw("{}::deserialize_no_header", elem.subtypeName), raw("r"))));
                                                               } else {
                                                                  col << method_call(raw("res.{}", elem.name), "insert", call("std::make_pair", raw("name"), raw(Semantics::put_static_read(Semantics::StaticDeserializer{elem.subtype}))));
                                                               }
                                                            },
                                                            raw("&res")));
                     col << raw("return");
                     return;
                  case Semantics::CompoundKind::Compound:
                     col << call("res.__xx_put", raw("name"), call("r.read_compound_content"));
                     col << raw("return");
                     return;
                  }
                  col << raw("break");
               });
            });
            col << raw("break");
         });
         return;
      }
      if (pair.second.type() == typeid(Semantics::ListDeserializer)) {
         auto deserializer = std::any_cast<Semantics::ListDeserializer>(pair.second);
         tag_switch.add(raw("minecpp::nbt::TagId::List"), [&deserializer](statement::collector &col) {
            put_deserialize_list_logic(deserializer, col);
         });
         return;
      }
   });
   col << tag_switch;
   col << call("r.skip_payload", raw("tagid"));
}

void put_deserialize_list_logic(const Semantics::ListDeserializer &deserializer, mb::codegen::statement::collector &col, mb::size depth) {
   using namespace mb::codegen;
   using minecpp::util::repeat_string;

   col << raw("auto list_info{} = r.peek_list()", depth);
   col << if_statement(raw("list_info{}.size > 0", depth), [&deserializer, depth](statement::collector &col) {
      switch_statement list_type_switch(raw("list_info{}.tagid", depth));
      std::for_each(deserializer.elems.begin(), deserializer.elems.end(), [depth, &list_type_switch](const std::pair<const Semantics::TypeVariant, std::any> &pair) {
         if (!pair.second.has_value()) {
            return;
         }

         if (pair.second.type() == typeid(Semantics::StaticDeserializer)) {
            auto elem_deserializer = std::any_cast<Semantics::StaticDeserializer>(pair.second);
            list_type_switch.add(raw(Semantics::variant_to_nbt_tag(elem_deserializer.variant)), [depth, &elem_deserializer](statement::collector &col) {
               put_deserialize_list_logic_static(elem_deserializer, col, 0, depth);
            });
         }

         if (pair.second.type() == typeid(Semantics::CompoundDeserializer)) {
            auto elem_deserializer = std::any_cast<Semantics::CompoundDeserializer>(pair.second);
            list_type_switch.add(raw("minecpp::nbt::TagId::Compound"), [&elem_deserializer, depth](statement::collector &col) {
               std::for_each(elem_deserializer.elems.begin(), elem_deserializer.elems.end(), [&col, depth](const Semantics::CompoundDeserializer::Elem &elem) {
                  col << if_statement(raw("name == \"{}\"", elem.label), [&elem, depth](statement::collector &col) {
                     put_deserialize_list_logic_compound(elem, col, 0, depth);
                  });
               });
               col << raw("break");
            });
         }

         if (pair.second.type() == typeid(Semantics::ListDeserializer)) {
            auto elem_deserializer = std::any_cast<Semantics::ListDeserializer>(pair.second);
            list_type_switch.add(raw("minecpp::nbt::TagId::List"), [&elem_deserializer, depth](statement::collector &col) {
               put_deserialize_list_logic(elem_deserializer, col, depth + 1);
            });
         }
      });
      col << list_type_switch;
      col << for_statement(raw("mb::size i = 0"), raw("i < list_info{}.size", depth), raw("++i"), [depth](statement::collector &col) {
         col << call("r.skip_payload", raw("list_info{}.tagid", depth));
      });
   });
   col << return_statement();
}

void put_deserialize_list_logic_static(const Semantics::StaticDeserializer &deserializer, mb::codegen::statement::collector &col, mb::size depth, mb::size target_depth) {
   using namespace mb::codegen;
   using minecpp::util::repeat_string;

   if (depth == target_depth) {
      col << raw("std::vector<{}> ls(list_info{}.size)", Semantics::variant_to_type(deserializer.variant), depth);
      col << call("std::generate", call("ls.begin"), call("ls.end"), lambda(
                                                                             {}, [&deserializer](statement::collector &col) {
                                                                                col << raw("return {}", Semantics::put_static_read(deserializer));
                                                                             },
                                                                             raw("&r")));
   } else {
      col << raw("{}{}{} ls(list_info{}.size)", repeat_string("std::vector<", target_depth - depth + 1), Semantics::variant_to_type(deserializer.variant), std::string(target_depth - depth + 1, '>'), depth);

      col << if_statement(raw("list_info{}.size != 0", depth), [&deserializer, depth, target_depth](statement::collector &col) {
         col << assign("auto it", call("ls.begin"));
         lambda gen_lambda_first(
                 {}, [&deserializer, depth, target_depth](statement::collector &col) {
                    put_deserialize_list_logic_static(deserializer, col, depth + 1, target_depth);
                 },
                 raw("&r"));
         for (mb::size i = depth + 1; i <= target_depth; ++i) {
            gen_lambda_first.add_capture(raw("&list_info{}", i));
         }
         col << assign("*it", call(gen_lambda_first));
         lambda gen_lambda(
                 {}, [&deserializer, depth, target_depth](statement::collector &col) {
                    col << raw("auto list_info{} = r.peek_list()", depth + 1);
                    put_deserialize_list_logic_static(deserializer, col, depth + 1, target_depth);
                 },
                 raw("&r"));
         for (mb::size i = depth + 2; i <= target_depth; ++i) {
            gen_lambda.add_capture(raw("&list_info{}", i));
         }
         col << call("std::generate", raw("it + 1"), call("ls.end"), gen_lambda);
      });
   }

   if (depth == 0) {
      col << call("res.__xx_put", raw("name"), raw("ls"));
      col << return_statement();
   } else {
      col << return_statement(raw("ls"));
   }
}

void put_deserialize_list_logic_compound(const Semantics::CompoundDeserializer::Elem &elem, mb::codegen::statement::collector &col, mb::size depth, mb::size target_depth) {
   using namespace mb::codegen;
   using minecpp::util::repeat_string;

   if (depth == target_depth) {
      col << raw("std::vector<{}> ls(list_info{}.size)", elem.typeName, depth);
      col << call("std::generate", call("ls.begin"), call("ls.end"), lambda(
                                                                             {}, [&elem](statement::collector &col) {
                                                                                col << raw("return {}::deserialize_no_header(r)", elem.typeName);
                                                                             },
                                                                             raw("&r")));
   } else {
      col << raw("{}{}{} ls(list_info{}.size)", repeat_string("std::vector<", target_depth - depth + 1), elem.typeName, std::string(target_depth - depth + 1, '>'), depth);

      col << if_statement(raw("list_info{}.size != 0", depth), [&elem, depth, target_depth](statement::collector &col) {
         col << assign("auto it", call("ls.begin"));
         lambda gen_lambda_first(
                 {}, [&elem, depth, target_depth](statement::collector &col) {
                    put_deserialize_list_logic_compound(elem, col, depth + 1, target_depth);
                 },
                 raw("&r"));
         for (mb::size i = depth + 1; i <= target_depth; ++i) {
            gen_lambda_first.add_capture(raw("&list_info{}", i));
         }
         col << assign("*it", call(gen_lambda_first));
         lambda gen_lambda(
                 {}, [&elem, depth, target_depth](statement::collector &col) {
                    col << raw("auto list_info{} = r.peek_list()", depth + 1);
                    put_deserialize_list_logic_compound(elem, col, depth + 1, target_depth);
                 },
                 raw("&r"));
         for (mb::size i = depth + 2; i <= target_depth; ++i) {
            gen_lambda.add_capture(raw("&list_info{}", i));
         }
         col << call("std::generate", raw("it + 1"), call("ls.end"), gen_lambda);
      });
   }

   if (depth == 0) {
      col << call("res.__xx_put", raw("name"), raw("ls"));
      col << return_statement();
   } else {
      col << return_statement(raw("ls"));
   }
}

void put_serialize_logic(mb::codegen::statement::collector &col, Semantics::Type type, const mb::codegen::expression &value) {
   using namespace mb::codegen;

   if (type.m_repeated > 0) {
      col << call("w.begin_list_no_header", raw(type.m_repeated == 1 ? variant_to_nbt_tag(type.variant) : "minecpp::nbt::TagId::List"), method_call(value, "size"));
      col << call("std::for_each", method_call(value, "begin"), method_call(value, "end"), lambda(
                                                                                                   {{"const auto", "&value"}}, [&type](statement::collector &col) {
                                                                                                      put_serialize_logic(col, Semantics::Type(type.variant, type.m_repeated - 1), raw("value"));
                                                                                                   },
                                                                                                   raw("&w")));
      return;
   }

   switch (type.variant) {
   case Semantics::TypeVariant::Int8:
      col << call("w.write_byte_content", value);
      break;
   case Semantics::TypeVariant::Int16:
      col << call("w.write_short_content", value);
      break;
   case Semantics::TypeVariant::Int32:
      col << call("w.write_int_content", value);
      break;
   case Semantics::TypeVariant::Int64:
      col << call("w.write_long_content", value);
      break;
   case Semantics::TypeVariant::String:
      col << call("w.write_string_content", value);
      break;
   case Semantics::TypeVariant::Float:
      col << call("w.write_float_content", value);
      break;
   case Semantics::TypeVariant::Double:
      col << call("w.write_double_content", value);
      break;
   case Semantics::TypeVariant::Bytes:
      col << call("w.write_bytes_content", value);
      break;
   case Semantics::TypeVariant::Ints:
      col << call("w.write_ints_content", value);
      break;
   case Semantics::TypeVariant::Longs:
      col << call("w.write_longs_content", value);
      break;
   case Semantics::TypeVariant::Compound:
      col << call("minecpp::nbt::serialize_compound_content", raw("w"), value);
      break;
   case Semantics::TypeVariant::Map:
      if (type.subtype != nullptr) {
         col << call("std::for_each", method_call(value, "begin"), method_call(value, "end"), lambda(
                                                                                                      {{"const auto", "&pair"}}, [&type](statement::collector &col) {
                                                                                                         col << call("w.write_header", raw(Semantics::variant_to_nbt_tag(type.subtype->variant)), raw("pair.first"));
                                                                                                         put_serialize_logic(col, *type.subtype, raw("pair.second"));
                                                                                                      },
                                                                                                      raw("&w")));
         col << call("w.end_compound");
      }
      break;
   default:
      col << method_call(value, "serialize_no_header", raw("w"));
   }
}

}// namespace minecpp::tool::nbt_idl
