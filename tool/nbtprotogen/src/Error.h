#pragma once
#include <mb/enum.h>
#include <stdexcept>
#include <string>

namespace minecpp::tool::nbt_idl {

enum class ErrorTypeValue
{
   UnexpectedToken,
   InvalidMapKey
};

using ErrorType_Base = mb::enum_wrapper<ErrorTypeValue, "unexpected_token", "invalid_map_key">;

class ErrorType : public ErrorType_Base
{
 public:
   MB_ENUM_TRAITS(ErrorType)

   MB_ENUM_FIELD(UnexpectedToken)
   MB_ENUM_FIELD(InvalidMapKey)
};

class Error : public std::runtime_error
{
 public:
   Error(int line, int column, const ErrorType &type, std::string details);

   [[nodiscard]] std::string message() const;

 private:
   int m_line;
   int m_column;
   ErrorType m_type;
   std::string m_details;
};

}// namespace minecpp::tool::nbt_idl