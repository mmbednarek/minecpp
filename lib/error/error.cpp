#include "error.h"

static grpc::StatusCode map_grpc_code(error_class c) {
   switch (c) {
   case error_class::Internal: return grpc::StatusCode::INTERNAL;
   case error_class::InvalidArgument: return grpc::StatusCode::INVALID_ARGUMENT;
   case error_class::NotFound: return grpc::StatusCode::NOT_FOUND;
   case error_class::NotImplemented: return grpc::StatusCode::UNIMPLEMENTED;
   case error_class::AlreadyExists: return grpc::StatusCode::ALREADY_EXISTS;
   }
   return grpc::StatusCode::INTERNAL;
}

error::error(std::string message) : message(std::move(message)) {}

error::error(error_class cl, std::string message) : message(std::move(message)), _class(cl) {}

const std::string &error::msg() const {
   return message;
}
error_class error::err_class() const {
   return _class;
}

grpc::Status error::grpc_status() const {
   return grpc::Status(map_grpc_code(err_class()), msg());
}
