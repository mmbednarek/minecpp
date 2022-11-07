#include "Error.h"

namespace minecpp::service::storage::fdb {

Error::Error(fdb_error_t error_code) :
        m_error_code(error_code)
{
}

bool Error::ok() const
{
   return m_error_code == 0;
}

std::string Error::to_string() const
{
   return fdb_get_error(m_error_code);
}

}