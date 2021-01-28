#pragma once
#include "tag.h"
#include <functional>
#include <minecpp/mineutils/reader.h>

namespace NBT {

class Parser {
   Utils::Reader reader;

 public:
   explicit Parser(std::istream &stream);

   NamedTag read_tag();
   std::map<std::string, Content> read_compound();

 private:
   TagId read_tag_id();
   std::any read_content(TagId id);
   std::vector<std::any> read_content_n(TagId id, std::size_t amount);
   std::function<std::any()> content_reader(TagId id);

   int8_t read_content_byte();
   int16_t read_content_short();
   int32_t read_content_int();
   int64_t read_content_long();
   float read_content_float();
   double read_content_double();
   std::vector<uint8_t> read_content_byte_array();
   std::string read_content_string();
   ListContent read_content_list();
   std::vector<int32_t> read_content_int_array();
   std::vector<int64_t> read_content_long_array();
};

}// namespace NewNBT