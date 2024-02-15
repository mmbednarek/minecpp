#include "minecpp/nbt/Parser.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using minecpp::nbt::CompoundContent;

auto format_time(std::int64_t raw_time)
{
   const auto epoch_time = std::chrono::time_point<std::chrono::system_clock>{};
   auto time             = epoch_time + std::chrono::nanoseconds{raw_time};

   std::time_t c_time = std::chrono::system_clock::to_time_t(time);
   return std::put_time(std::localtime(&c_time), "%FT%T%z");
}

int main(int argc, char **argv)
{
   if (argc < 2)
      return 1;
   std::string filename{argv[1]};

   std::vector<std::string> fields{};
   std::set<std::string> filter{};

   bool read_filter{false};
   for (int i = 2; i < argc; ++i) {
      if (read_filter) {
         filter.emplace(argv[i]);
         read_filter = false;
         continue;
      }
      if (std::strcmp(argv[i], "-f") == 0) {
         read_filter = true;
         continue;
      }

      fields.emplace_back(argv[i]);
   }

   std::ifstream input_stream{filename};

   minecpp::nbt::Parser parser(input_stream);

   auto is_first = true;
   for (const auto &field : fields) {
      if (is_first) {
         is_first = false;
      } else {
         std::cout << ',';
      }

      std::cout << field;
   }
   std::cout << '\n';

   for (;;) {
      auto tag = parser.read_tag();
      if (tag.content.empty())
         break;


      auto trace = tag.content.as<CompoundContent>();
      auto name  = trace["name"].as<std::string>();

      if (not filter.empty() and not filter.contains(name))
         continue;

      auto data     = trace["data"].as<CompoundContent>();
      bool is_first = true;

      for (const auto &field : fields) {
         if (is_first) {
            is_first = false;
         } else {
            std::cout << ',';
         }

         if (field == "name") {
            std::cout << name;
            continue;
         }
         if (field == "time") {
            std::cout << format_time(trace["time"].as<std::int64_t>());
            continue;
         }

         if (not data.contains(field)) {
            std::cout << '-';
         } else {
            std::cout << data[field].to_string();
         }
      }

      std::cout << '\n';
   }

   return 0;
}