#pragma once
#include <grpcpp/impl/codegen/status.h>
#include <mb/error.h>

namespace minecpp::util {

grpc::StatusCode grpc_status_code(const mb::error &err);

}