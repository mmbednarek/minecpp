#include "Error.h"
#include <fmt/core.h>

#include <utility>

namespace minecpp::tool::nbt_idl {

Error::Error(int line, int column, const ErrorType &type, std::string details) :
    runtime_error(type.to_string().data()),
    m_line(line),
    m_column(column),
    m_type(type),
    m_details(std::move(details))
{
}

std::string Error::message() const
{
   return fmt::format("[{}:{}] {}: {}", m_line, m_column, m_type.to_string(), m_details);
}

}// namespace minecpp::tool::nbt_idl