#include <minecpp/util/grpc.h>

namespace minecpp::util {

grpc::StatusCode grpc_status_code(const mb::error &err) {
   switch (err.err_class()) {
   case mb::error::status::Internal:
      return grpc::StatusCode::INTERNAL;
   case mb::error::status::InvalidArgument:
      return grpc::StatusCode::INVALID_ARGUMENT;
   case mb::error::status::NotFound:
      return grpc::StatusCode::NOT_FOUND;
   case mb::error::status::NotImplemented:
      return grpc::StatusCode::UNIMPLEMENTED;
   case mb::error::status::AlreadyExists:
      return grpc::StatusCode::ALREADY_EXISTS;
   }
   return grpc::StatusCode::UNAVAILABLE;
}

}
