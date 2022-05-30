#pragma once
#include <grpcpp/impl/codegen/status.h>
#include <mb/error.h>

#define MCPP_GRPC_TRY(stmt)                                                       \
   ({                                                                             \
      auto __mb_res = stmt;                                                       \
      if (!__mb_res.ok()) {                                                       \
         return grpc::Status(grpc::StatusCode::INTERNAL, __mb_res.err()->msg());  \
      }                                                                           \
      ::mb::forward_container<decltype(__mb_res)::value_type>{__mb_res.unwrap()}; \
   }).contained
