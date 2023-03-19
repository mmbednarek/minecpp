#include "Lexer.h"
#include "Parser.h"
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

namespace opts = boost::program_options;

int main(int argc, char **argv)
{
   using namespace minecpp::tool::snbt_parser;

   opts::options_description desc("snbt <input-filename> -o <output-filename>");
   // clang-format off
   desc.add_options()
      ("help",      "print help information")
      ("version,v", "print version")
      ("input,i", opts::value<std::string>(), "specify input file")
      ("output,o", opts::value<std::string>(), "specify output");
   // clang-format on

   opts::positional_options_description desc_pos;
   desc_pos.add("input", 1);
   desc_pos.add("output", 1);

   opts::variables_map values;

   try {
      opts::store(opts::command_line_parser(argc, argv).options(desc).positional(desc_pos).run(), values);
      opts::notify(values);
   } catch (boost::program_options::error &err) {
      std::cerr << "invalid input arguments: " << err.what() << '\n';
      desc.print(std::cout);
   }

   if (values["input"].empty()) {
      std::cerr << "no input file provided\n";
      return 1;
   }
   auto input_file = values["input"].as<std::string>();

   std::string output_file{"out.bin"};
   if (not values["output"].empty()) {
      output_file = values["output"].as<std::string>();
   }

   std::ifstream in_file(input_file);
   if (not in_file.is_open()) {
      std::cerr << "could not open input file\n";
      return 1;
   }

   IStreamReader reader(in_file);
   Lexer lexer(reader);
   auto tokens = lexer.lex();
   Parser parser(tokens);

   try {
      auto content = parser.read_content();

      std::ofstream out(output_file);
      content.serialize("", out);
   } catch (const std::runtime_error &err) {
      std::cerr << "Failed to parse input: " << err.what() << '\n';
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}