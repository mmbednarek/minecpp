#include <cstdio>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <minecpp/nbt/Parser.h>
#include <minecpp/util/Compression.h>
#include <minecpp/util/Scriptw.h>
#include <set>

static std::string to_camel_case(const std::string_view name)
{
   std::string result;

   auto it = name.begin();
   result.push_back(static_cast<char>(std::toupper(*it)));

   bool next_upper{false};
   std::for_each(it + 1, name.end(), [&result, &next_upper](char c) {
      if (c == ':' || c == '_') {
         next_upper = true;
      } else if (next_upper) {
         next_upper = false;
         result.push_back(static_cast<char>(std::toupper(c)));
      } else {
         result.push_back(c);
      }
   });

   return result;
}

struct NameProvider
{
   int index = 0;
   std::set<std::string> names;
   std::unordered_map<std::string, std::string> labels;

   std::string next_name()
   {
      return fmt::format("Type{}", index++);
   }

   std::string register_name(std::string_view scoped_name, std::string_view parent_label,
                             std::string_view label)
   {
      auto label_camel = to_camel_case(label);
      if (!names.contains(label_camel)) {
         names.insert(label_camel);
         labels[std::string(scoped_name)] = label_camel;
         return label_camel;
      }

      auto label_with_parent = to_camel_case(parent_label) + label_camel;
      if (!names.contains(label_with_parent)) {
         names.insert(label_with_parent);
         labels[std::string(scoped_name)] = label_with_parent;
         return label_with_parent;
      }

      return register_name(scoped_name, parent_label, std::string(label) + "X");
   }

   std::string_view get_type(const std::string &scoped_name)
   {
      return labels[scoped_name];
   }
};

struct Message
{
   minecpp::nbt::CompoundContent content;
   std::string name;
};

bool all_upper_case(const std::string_view name)
{
   return std::all_of(name.begin(), name.end(), [](char c) { return std::isupper(c) || c == '_'; });
}

std::string format_name(const std::string_view name)
{
   std::string result;

   if (all_upper_case(name)) {
      std::for_each(name.begin(), name.end(),
                    [&result](char c) { result.push_back(static_cast<char>(std::tolower(c))); });
      return result;
   }

   auto it    = name.begin();
   auto first = *it;
   if (std::isupper(first)) {
      result.push_back(static_cast<char>(std::tolower(first)));
   } else {
      result.push_back(first);
   }

   std::for_each(it + 1, name.end(), [&result](char c) {
      if (c == ':') {
         result.push_back('_');
      } else if (std::isupper(c)) {
         result.push_back('_');
         result.push_back(static_cast<char>(std::tolower(c)));
      } else {
         result.push_back(c);
      }
   });

   return result;
}

static std::string to_lower(std::string_view s)
{
   std::string out(s.size(), ' ');
   std::transform(s.begin(), s.end(), out.begin(), [](char c) { return std::tolower(c); });
   return out;
}

static std::string element_name(std::string_view name)
{
   if (name.empty()) {
      return "Element";
   }
   if (to_lower(name.substr(name.size() - 3, name.size())) == "ies") {
      return std::string(name.substr(0, name.size() - 3)) + "y";
   }
   if (std::tolower(name.at(name.size() - 1)) == 's') {
      return std::string(name.substr(0, name.size() - 1));
   }
   return std::string(name) + "Element";
}

std::vector<Message> find_dependencies(minecpp::nbt::CompoundContent &content, std::string_view scope,
                                       std::string_view parent_label, NameProvider &np)
{
   std::vector<Message> m;
   std::for_each(content.begin(), content.end(),
                 [&np, &m, &scope, parent_label](std::pair<std::string, minecpp::nbt::Content> pair) {
                    if (pair.second.tag_id == minecpp::nbt::TagId::Compound) {
                       m.emplace_back(Message{
                               .content = pair.second.as<minecpp::nbt::CompoundContent>(),
                               .name = np.register_name(fmt::format("{}_{}", scope, pair.first), parent_label,
                                                        pair.first),
                       });
                    } else if (pair.second.tag_id == minecpp::nbt::TagId::List) {
                       auto list = pair.second.as<minecpp::nbt::ListContent>();
                       if (list.tag_id == minecpp::nbt::TagId::Compound) {
                          auto element = *list.begin();
                          m.emplace_back(Message{
                                  .content = element.as<minecpp::nbt::CompoundContent>(),
                                  .name    = np.register_name(fmt::format("{}_{}", scope, pair.first),
                                                              parent_label, element_name(pair.first)),
                          });
                       }
                       if (list.tag_id == minecpp::nbt::TagId::List) {
                          auto lt    = *list.begin();
                          auto list2 = lt.as<minecpp::nbt::ListContent>();
                          if (list2.tag_id == minecpp::nbt::TagId::Compound) {
                             auto element = *list2.begin();
                             m.emplace_back(Message{
                                     .content = element.as<minecpp::nbt::CompoundContent>(),
                                     .name    = np.register_name(fmt::format("{}_{}", scope, pair.first),
                                                                 parent_label, element_name(pair.first)),
                             });
                          }
                       }
                    }
                 });
   return m;
}

std::string find_type(NameProvider &np, std::string_view scope, minecpp::nbt::Content &content)
{
   switch (content.tag_id) {
   case minecpp::nbt::TagId::Byte: return "int8";
   case minecpp::nbt::TagId::Short: return "int16";
   case minecpp::nbt::TagId::Int: return "int32";
   case minecpp::nbt::TagId::Long: return "int64";
   case minecpp::nbt::TagId::Float: return "float";
   case minecpp::nbt::TagId::Double: return "double";
   case minecpp::nbt::TagId::ByteArray: return "bytes";
   case minecpp::nbt::TagId::String: return "string";
   case minecpp::nbt::TagId::IntArray: return "ints";
   case minecpp::nbt::TagId::LongArray: return "longs";
   case minecpp::nbt::TagId::List: {
      auto list = content.as<minecpp::nbt::ListContent>();
      if (list.elements.empty()) {
         return "repeated <unknown>";
      }
      auto element = *list.begin();
      return fmt::format("repeated {}", find_type(np, scope, element));
   }
   case minecpp::nbt::TagId::Compound: {
      return std::string(np.get_type(std::string(scope)));
   }
   default: break;
   }

   return "<unknown>";
}

void write_attribute(NameProvider &np, minecpp::util::ScriptWriter &w, std::string_view scope,
                     std::string_view name, minecpp::nbt::Content content, int index)
{
   auto formatted_name = format_name(name);
   if (formatted_name == name) {
      w.line("{} {} = {};", find_type(np, fmt::format("{}_{}", scope, name), content), format_name(name),
             index, name);
   } else {
      w.line("{} {} = {} [label = \"{}\"];", find_type(np, fmt::format("{}_{}", scope, name), content),
             format_name(name), index, name);
   }
}

void write_message(minecpp::util::ScriptWriter &w, NameProvider &np, const std::string_view scope,
                   const std::string_view name, minecpp::nbt::CompoundContent cont)
{
   auto dependencies = find_dependencies(cont, scope, name, np);
   for (auto &msg : dependencies) {
      write_message(w, np, fmt::format("{}_{}", scope, msg.name), msg.name, msg.content);
   }
   int index = 1;
   w.scope("message {}", name);
   {
      for (auto &pair : cont) {
         write_attribute(np, w, scope, pair.first, pair.second, index);
         ++index;
      }
   }
   w.descope();
   w.line();
}

int main(int argc, char **argv)
{
   if (argc < 3) {
      fmt::print(stderr, "not enough arguments");
      return 1;
   }

   std::ifstream file(argv[1]);
   if (!file.is_open()) {
      fmt::print(stderr, "missing file {}", argv[1]);
      return 1;
   }

   minecpp::util::GZipInputStream stream(file);

   minecpp::nbt::Parser p(stream);
   auto tag = p.read_tag();

   std::cout << tag.content.to_string();

   NameProvider np;

   minecpp::util::ScriptWriter w(std::cout);

   w.line("syntax = \"proto3\";");
   w.line("package {};", argv[1]);
   w.line();

   write_message(w, np, "", argv[2], tag.content.as<minecpp::nbt::CompoundContent>());
   return 0;
}