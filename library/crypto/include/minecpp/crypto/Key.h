#pragma once
#include "Error.h"
#include <mb/result.h>
#include <memory>
#include <minecpp/container/BasicBuffer.h>
#include <openssl/rsa.h>
#include <span>
#include <string>
#include <vector>

namespace minecpp::crypto {

class PrivateKey
{
 public:
   explicit PrivateKey(int bits);
   PrivateKey(std::string_view pem_file, std::string_view pass_phrase);
   ~PrivateKey();

   Result<container::Buffer> decrypt_message(const container::Buffer &buff);
   Result<container::Buffer> encrypt_message(const container::Buffer &buff);

   std::size_t write_public_key(std::ostream &stream);
   Result<container::Buffer> public_key();

 private:
   EVP_PKEY *m_rsa_key{};
};

}// namespace minecpp::crypto