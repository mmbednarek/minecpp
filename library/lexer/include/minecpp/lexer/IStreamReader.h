#pragma once

#include "IReader.h"

#include <istream>

namespace minecpp::lexer {

class IStreamReader : public IReader
{
 public:
   explicit IStreamReader(std::istream &stream);

   bool has_next() override;
   char next() override;
   void step_back() override;

 private:
   std::istream &m_stream;
   char m_next_char;
};

}// namespace minecpp::lexer