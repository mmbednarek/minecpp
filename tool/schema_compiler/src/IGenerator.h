#pragma once

#include "Ast.h"
#include "SymbolTable.h"

#include <fmt/core.h>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

namespace minecpp::tool::schema_compiler {

constexpr auto g_nbt_generator_name = "nbt";
constexpr auto g_network_generator_name = "net";

struct PathInfo
{

   std::string root_origin_dir;
   // Output of the source files
   std::string root_source_target_dir;
   // Output of the header files
   std::string root_header_target_dir;
   // Original document
   std::string origin_document_path;
   // Path that should be used to include local headers
   std::string root_include_path;
};

class IGenerator
{
 public:
   virtual ~IGenerator() = default;

   [[nodiscard]] virtual std::string target_header_path() const = 0;
   [[nodiscard]] virtual std::string target_source_path() const = 0;
   virtual void generate_header(std::ostream &output)           = 0;
   virtual void generate_source(std::ostream &output)           = 0;
};

class IGeneratorFactory
{
 public:
   virtual ~IGeneratorFactory() = default;

   [[nodiscard]] virtual std::unique_ptr<IGenerator>
   create_generator(const Document &document, const SymbolTable &table, const PathInfo &path_info) = 0;
};

class GeneratorError : public std::runtime_error
{
 public:
   explicit GeneratorError(int line, int column, const std::string_view msg) :
       std::runtime_error(fmt::format("[{}:{}] {}", line, column, msg))
   {
   }
};

template<typename... TArgs>
inline void generator_verify(bool check, int line, int column, fmt::format_string<TArgs...> format_str, TArgs &&...args)
{
   if (not check) {
      throw GeneratorError(line, column, fmt::format(format_str, std::forward<TArgs>(args)...));
   }
}

}// namespace minecpp::tool::schema_compiler