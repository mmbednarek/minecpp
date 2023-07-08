#pragma once

namespace minecpp::lexer {

class IReader
{
 public:
   virtual bool has_next()  = 0;
   virtual char next()      = 0;
   virtual void step_back() = 0;
};

}
