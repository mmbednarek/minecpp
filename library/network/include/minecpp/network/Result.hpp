#pragma once

#include <mb/enum.h>
#include <mb/result.h>

namespace minecpp::network {

enum class ErrorValues
{
   AddressLoopUpFailed,
};

using Error_Base = mb::enum_wrapper<ErrorValues, "AddressLookUpFailed">;

class Error : public Error_Base
{
 public:
   MB_ENUM_TRAITS(Error)

   MB_ENUM_FIELD(AddressLoopUpFailed)
};

template<typename TValue>
using Result = mb::result<TValue, Error>;

}// namespace minecpp::network