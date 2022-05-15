#include <minecpp/error/error.h>

static grpc::StatusCode map_grpc_code(errclass c)
{
   switch (c) {
   case errclass::Internal: return grpc::StatusCode::INTERNAL;
   case errclass::InvalidArgument: return grpc::StatusCode::INVALID_ARGUMENT;
   case errclass::NotFound: return grpc::StatusCode::NOT_FOUND;
   case errclass::NotImplemented: return grpc::StatusCode::UNIMPLEMENTED;
   case errclass::AlreadyExists: return grpc::StatusCode::ALREADY_EXISTS;
   }
   return grpc::StatusCode::INTERNAL;
}

error::error(std::string message) noexcept : message(std::move(message)) {}

error::error(errclass cl, std::string message) : message(std::move(message)), _class(cl) {}

const std::string &error::msg() const { return message; }
errclass error::err_class() const { return _class; }

grpc::Status error::grpc_status() const { return grpc::Status(map_grpc_code(err_class()), msg()); }
