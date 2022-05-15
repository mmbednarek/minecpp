#pragma once
#include <grpcpp/impl/codegen/status.h>
#include <mb/error.h>

namespace minecpp::util {

grpc::StatusCode grpc_status_code(const mb::error &err);

}

#define MCPP_GRPC_TRY(stmt)                                                       \
   ({                                                                             \
      auto __mb_res = stmt;                                                       \
      if (!__mb_res.ok()) {                                                       \
         auto err = __mb_res.err();                                               \
         return grpc::Status(minecpp::util::grpc_status_code(*err), err->msg());  \
      }                                                                           \
      ::mb::forward_container<decltype(__mb_res)::value_type>{__mb_res.unwrap()}; \
   }).contained
