#ifndef MINECPP_ERROR_H
#define MINECPP_ERROR_H
#include <string_view>
#include <mb/result.h>

namespace minecpp::lexer {

enum class ErrorType {
   UnexpectedToken
};

struct Error {
   int line, column;
   ErrorType type;
};

constexpr std::string_view to_string(minecpp::lexer::ErrorType type) {
   using namespace std::string_view_literals;
   using minecpp::lexer::ErrorType;
   switch (type) {
   case minecpp::lexer::ErrorType::UnexpectedToken:
      return "unexpected token";
   }
   return "";
}

template<typename T>
using Result = mb::result<T, Error>;

}

#endif//MINECPP_ERROR_H
