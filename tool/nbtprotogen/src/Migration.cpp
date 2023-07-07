#include "Migration.h"

#include <ostream>
#include <algorithm>
#include <mb/codegen/writer.h>

std::string convert_type(const Syntax::Ast::Attribute &attribute);

std::string convert_to_snake_case(const std::string &input) {
   bool previous_lower = false;

   std::string output{};
   for (auto ch : input) {
      if (std::isupper(ch)) {
         if (previous_lower) {
            output.push_back('_');
         }
         output.push_back(static_cast<char>(std::tolower(ch)));
         previous_lower = false;
         continue;
      }
      output.push_back(ch);
      previous_lower = true;
   }

   return output;
}

void generate_output(const std::vector<Syntax::Ast::Node> &nodes, std::ostream &out) {
   mb::codegen::writer writer(out);

   for (const auto &node : nodes) {
      if (std::holds_alternative<Syntax::Ast::PackageInfo>(node)) {
         auto package_info = std::get<Syntax::Ast::PackageInfo>(node);
         if (package_info.package.empty())
            continue;

         writer.write("package ");
         writer.write(package_info.package.front());
         std::for_each(package_info.package.begin() + 1, package_info.package.end(), [&writer](const auto &part) {
           writer.write(".{}", part);
         });
         writer.line();
         writer.line();
      }

      if (std::holds_alternative<Syntax::Ast::Message>(node)) {
         auto message = std::get<Syntax::Ast::Message>(node);

         writer.line("[NBT]");
         writer.line("record {} {{", message.name);
         writer.indent_in();
         for (const auto &attribute: message.attributes) {
            if (attribute.label.empty()) {
               writer.put_indent();
               writer.write("{}: ", attribute.name);
            } else {
               auto colon_at = attribute.label.find(':');
               if (colon_at == std::string::npos) {
                  auto cc_name = convert_to_snake_case(attribute.label);
                  if (cc_name == attribute.name) {
                     writer.put_indent();
                     writer.write("{}: ", attribute.label);
                  } else {
                     writer.line("[CC_Name=\"{}\"]", attribute.name);
                     writer.put_indent();
                     writer.write("{}: ", attribute.label);
                  }
               } else {
                  auto ns = attribute.label.substr(0, colon_at);
                  auto label = attribute.label.substr(colon_at+1, std::string::npos);
                  writer.line("[Namespace=\"{}\", Path=\"{}\"]", ns, label);
                  writer.put_indent();
                  writer.write("{}: ", attribute.name);
               }
            }

            for (const auto &space : attribute.package) {
               writer.write("{}.", space);
            }
            writer.write("{}", convert_type(attribute));
            writer.line();
         }
         writer.indent_out();
         writer.line("}");
         writer.line();
      }
   }
}

std::string convert_type(const Syntax::Ast::Attribute &attribute) {
   if (attribute.optional) {
      auto sub_attrib = attribute;
      sub_attrib.optional = false;
      return fmt::format("optional[{}]", convert_type(sub_attrib));
   }

   if (attribute.repeated > 0) {
      auto sub_attrib = attribute;
      sub_attrib.repeated--;
      return fmt::format("list[{}]", convert_type(sub_attrib));
   }

   if (attribute.type == "map") {
      auto sub_attrib = attribute;
      sub_attrib.type = attribute.subtype;
      sub_attrib.subtype = "";
      return fmt::format("map[string, {}]", convert_type(sub_attrib));
   }

   if (attribute.type == "float")
      return "float32";
   if (attribute.type == "double")
      return "float64";
   if (attribute.type == "bytes")
      return "list[uint8]";
   if (attribute.type == "ints")
      return "list[int32]";
   if (attribute.type == "longs")
      return "list[int64]";
   if (attribute.type == "compound")
      return "nbt.CompoundContent";

   return attribute.type;
}
