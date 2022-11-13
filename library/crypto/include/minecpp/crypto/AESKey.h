#pragma once
#include "Error.h"
#include "mb/result.h"
#include <iostream>
#include <minecpp/container/BasicBuffer.h>
#include <openssl/evp.h>

namespace minecpp::crypto {

class AESKey
{
 public:
   AESKey(container::Buffer key, container::Buffer iv);
   ~AESKey();

   AESKey(const AESKey &) = delete;
   AESKey &operator=(const AESKey &) = delete;

   AESKey(AESKey &&) noexcept;
   AESKey &operator=(AESKey &&) noexcept;

   Result<container::Buffer> decrypt_message(const container::Buffer &buff);
   Result<container::Buffer> encrypt_message(const container::Buffer &buff);

 private:
   container::Buffer m_key;
   container::Buffer m_iv;
   EVP_CIPHER_CTX *m_encrypt_ctx;
   EVP_CIPHER_CTX *m_decrypt_ctx;
};

}// namespace minecpp::crypto