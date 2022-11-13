#pragma once
#include <mb/result.h>

namespace minecpp::crypto {

enum class ErrorType
{
   InvalidArgument,
   EncryptionInitError,
   EncryptionError,
   DecryptionInitError,
   DecryptionError,
};

template<typename TValue>
using Result = mb::result<TValue, ErrorType>;

using EmptyResult = Result<mb::empty>;

}// namespace minecpp::crypto
