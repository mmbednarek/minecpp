#include "Generator.h"
#include "Lexer.h"
#include "Parser.h"
#include "Structgen.h"
#include <boost/program_options.hpp>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <mb/result.h>
#include <vector>

namespace opts = boost::program_options;

constexpr auto g_version = "0.0.1";

std::string find_module_name(std::string scheme_file)
{
   auto beg = scheme_file.begin() +
              (scheme_file.rend() - std::find(scheme_file.rbegin(), scheme_file.rend(), '/'));
   return std::string(beg, std::find(beg, scheme_file.end(), '.'));
}

template<typename T>
mb::result<T> get(opts::variables_map &values, const std::string &key)
{
   auto candidate = values[key];
   if (candidate.empty()) {
      return mb::error("value not specified");
   }
   return T(candidate.as<T>());
}

int main(int argc, char *argv[])
{
   opts::options_description desc("nbtc");
   desc.add_options()("help", "print help information")("version,v", "print version")(
           "source-output,s", opts::value<std::string>(), "specify source output path")(
           "header-output,h", opts::value<std::string>(), "specify header output path")(
           "module-name,m", opts::value<std::string>(), "specify alternative module name")(
           "include-path,I", opts::value<std::string>(),
           "specify include path")("scheme-file", opts::value<std::string>(), "specify a source scheme file");

   opts::positional_options_description desc_pos;
   desc_pos.add("scheme-file", -1);

   opts::variables_map values;
   opts::store(opts::command_line_parser(argc, argv).options(desc).positional(desc_pos).run(), values);

   if (auto help = values["help"]; !help.empty()) {
      std::cout << desc;
      return 0;
   }

   if (auto version = values["version"]; !version.empty()) {
      std::cout << g_version << '\n';
      return 0;
   }

   auto scheme_file_res = get<std::string>(values, "scheme-file");
   if (!scheme_file_res.ok()) {
      std::cerr << "input scheme file not specified\n";
      return 1;
   }
   auto scheme_file = scheme_file_res.unwrap();

   auto module_name   = get<std::string>(values, "module-name").unwrap(find_module_name(scheme_file));
   auto source_output = get<std::string>(values, "source-output").unwrap(".");
   auto header_output = get<std::string>(values, "header-output").unwrap(std::string(source_output));
   auto include_path  = get<std::string>(values, "include-path").unwrap("");

   std::ifstream s(scheme_file);
   if (!s.is_open()) {
      std::cerr << "could not open file\n";
      return 1;
   }

   auto tkn_reader = Lex::lex(s);
   auto parser     = Syntax::Parser(tkn_reader);
   auto nodes_res  = parser.parse();
   if (!nodes_res.ok()) {
      std::cerr << nodes_res.err()->msg() << '\n';
      return 2;
   }
   auto nodes     = nodes_res.unwrap();
   auto structure = Semantics::Structure(nodes);

   minecpp::tool::nbt_idl::Generator gen(structure, module_name, include_path);

   std::ofstream header_out(fmt::format("{}/{}.nbt.h", header_output, module_name));
   if (!header_out.is_open()) {
      std::cerr << "could not open header output file\n";
      return 1;
   }
   gen.write_header(header_out);

   std::ofstream source_out(fmt::format("{}/{}.nbt.cpp", source_output, module_name));
   if (!source_out.is_open()) {
      std::cerr << "could not open source output file, path "
                << fmt::format("{}/{}.nbt.cpp", source_output, module_name) << '\n';
      return 1;
   }
   gen.write_source(source_out);
   return 0;
}