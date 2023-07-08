#include "generator/NbtGenerator.h"
#include "IGenerator.h"
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"

#include <boost/program_options.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace opts = boost::program_options;
using Path     = std::filesystem::path;
using minecpp::tool::schema_compiler::Document;
using minecpp::tool::schema_compiler::GeneratorError;
using minecpp::tool::schema_compiler::Symbol;
using minecpp::tool::schema_compiler::TypeClass;
using minecpp::tool::schema_compiler::generator::NbtGenerator;

void register_core_types(minecpp::tool::schema_compiler::SymbolTable &table);
void list_schema_files(const Path &path, std::vector<Path> &out);
void ensure_directory(const std::string &path);

constexpr auto g_version = "0.1.0";

int main(int argc, char **argv)
{
   opts::options_description desc("schema_compiler");

   // clang-format off
   desc.add_options()
      ("help", "print help information")
      ("version,v", "print version")
      ("generator,g", "specify generator")
      ("input-path,i", opts::value<std::string>(), "specify schema input path")
      ("include-path,I", opts::value<std::string>(), "specify header include path")
      ("source-output,s", opts::value<std::string>(), "specify source output path")
      ("header-output,h", opts::value<std::string>(), "specify header output path");
   // clang-format on

   opts::variables_map values;
   opts::store(opts::command_line_parser(argc, argv).options(desc).run(), values);

   if (auto help = values["help"]; !help.empty()) {
      std::cerr << desc;
      return EXIT_SUCCESS;
   }

   if (auto version = values["version"]; !version.empty()) {
      std::cerr << g_version << '\n';
      return EXIT_SUCCESS;
   }

   if (not values.contains("input-path")) {
      std::cerr << "schema_compiler: missing input path" << '\n';
      std::cerr << desc;
      return EXIT_FAILURE;
   }
   if (not values.contains("header-output")) {
      std::cerr << "schema_compiler: missing header output path" << '\n';
      std::cerr << desc;
      return EXIT_FAILURE;
   }
   if (not values.contains("source-output")) {
      std::cerr << "schema_compiler: missing source output path" << '\n';
      std::cerr << desc;
      return EXIT_FAILURE;
   }
   if (not values.contains("include-path")) {
      std::cerr << "schema_compiler: missing include path" << '\n';
      std::cerr << desc;
      return EXIT_FAILURE;
   }

   const std::filesystem::path api{values["input-path"].as<std::string>()};

   std::vector<Path> files;
   list_schema_files(api, files);

   minecpp::tool::schema_compiler::SymbolTable table;
   register_core_types(table);

   std::vector<std::pair<std::string, Document>> documents;

   for (const auto &file : files) {
      std::ifstream stream(file);
      if (not stream.is_open())
         return 1;

      auto tokens = minecpp::tool::schema_compiler::lex_input(stream);
      minecpp::tool::schema_compiler::Parser parser(tokens);

      auto document = parser.parse_document();
      if (document.has_failed()) {
         std::cerr << "schema_compiler: failed to parse document " << file.string() << ": \n\t";
         std::cerr << "[" << document.err().line << ":" << document.err().column << "] " << document.err().to_string() << '\n';
         return 1;
      }

      table.read_document(file.string(), *document);

      documents.emplace_back(file.string(), std::move(*document));
   }

   for (const auto &[filename, document] : documents) {
      minecpp::tool::schema_compiler::PathInfo path_info{
              .root_origin_dir{fmt::format("{}/", values["input-path"].as<std::string>())},
              .root_source_target_dir{values["source-output"].as<std::string>()},
              .root_header_target_dir{values["header-output"].as<std::string>()},
              .origin_document_path{filename},
              .root_include_path{values["include-path"].as<std::string>()}};

      try {
         minecpp::tool::schema_compiler::generator::NbtGenerator generator(document, table, path_info);

         {
            std::cerr << "schema_compiler: writing header to " << generator.target_header_path() << '\n';
            ensure_directory(generator.target_header_path());
            std::ofstream header_output{generator.target_header_path()};
            assert(header_output.is_open());
            generator.generate_header(header_output);
         }
         {
            std::cerr << "schema_compiler: writing source to " << generator.target_source_path() << '\n';
            ensure_directory(generator.target_source_path());
            std::ofstream source_output{generator.target_source_path()};
            assert(source_output.is_open());
            generator.generate_source(source_output);
         }
      } catch (GeneratorError &err) {
         std::cerr << "schema_compiler: failed to compile source " << filename << ":\n\t" << err.what()
                   << '\n';
         return 1;
      }
   }

   return 0;
}

void register_core_types(minecpp::tool::schema_compiler::SymbolTable &table)
{
   table.register_symbol(Symbol{
           .type_class = TypeClass::Int8,
           .name{"int8"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::Int16,
           .name{"int16"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::Int32,
           .name{"int32"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::Int64,
           .name{"int64"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::UInt8,
           .name{"uint8"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::UInt16,
           .name{"uint16"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::UInt32,
           .name{"uint32"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::UInt64,
           .name{"uint64"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::Float32,
           .name{"float32"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::Float64,
           .name{"float64"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::String,
           .name{"string"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::Map,
           .name{"map"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::List,
           .name{"list"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::Optional,
           .name{"optional"},
   });
   table.register_symbol(Symbol{
           .type_class = TypeClass::Variant,
           .name{"variant"},
   });
   table.register_symbol(Symbol{.type_class = TypeClass::NbtCompoundContent,
                                .name{"CompoundContent"},
                                .package{"minecpp.nbt"}});
}

void list_schema_files(const Path &path, std::vector<Path> &out)
{
   for (const auto &file : std::filesystem::directory_iterator{path}) {
      if (file.is_directory()) {
         list_schema_files(file.path(), out);
         continue;
      }

      if (file.path().string().ends_with(".schema")) {
         out.push_back(file.path());
      }
   }
}

void ensure_directory(const std::string &path)
{
   auto res = path.find_last_of('/');
   if (res == std::string::npos)
      return;

   std::filesystem::create_directories(std::filesystem::path{path.substr(0, res)});
}
