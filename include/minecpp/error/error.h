#pragma once
#include "../../../cmake-build-debug/_deps/grpc-src/include/grpcpp/impl/codegen/status.h"
#include <memory>
#include <minecpp/util/format.h>

enum class errclass {
   Internal = 0,
   InvalidArgument = 1,
   NotFound = 2,
   NotImplemented = 3,
   AlreadyExists = 4,
};

class error {
   std::string message;
   errclass _class = errclass::InvalidArgument;

 public:
   typedef std::unique_ptr<error> ptr;

   explicit error(std::string message) noexcept;
   error(errclass cl, std::string message);

   [[nodiscard]] virtual const std::string &msg() const;

   [[nodiscard]] virtual errclass err_class() const;

   [[nodiscard]] grpc::Status grpc_status() const;
};

template<typename... Args>
error errorf(std::string fmt, Args... a) {
   return error(Utils::format(fmt, a...));
}
