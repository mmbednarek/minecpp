#pragma once
#include <grpcpp/impl/codegen/status.h>
#include <memory>
#include <mineutils/format.h>

enum class error_class {
   Internal = 0,
   InvalidArgument = 1,
   NotFound = 2,
   NotImplemented = 3,
   AlreadyExists = 4,
};

class error {
   std::string message;
   error_class _class = error_class::InvalidArgument;

 public:
   typedef std::unique_ptr<error> ptr;

   explicit error(std::string message);
   error(error_class cl, std::string message);

   [[nodiscard]] virtual const std::string &msg() const;

   [[nodiscard]] virtual error_class err_class() const;

   [[nodiscard]] grpc::Status grpc_status() const;
};

template<typename... Args>
error errorf(std::string fmt, Args... a) {
   return error(Utils::format(fmt, a...));
}
