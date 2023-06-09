#pragma once
#include "Error.h"
#include <iostream>
#include <minecpp/container/BasicBufferView.hpp>
#include <minecpp/container/BasicBuffer.hpp>
#include <openssl/evp.h>

namespace minecpp::crypto {

class AESKey
{
 public:
   AESKey(container::BufferView key, container::BufferView iv);
   ~AESKey();

   AESKey(const AESKey &)            = delete;
   AESKey &operator=(const AESKey &) = delete;

   AESKey(AESKey &&) noexcept;
   AESKey &operator=(AESKey &&) noexcept;

   EmptyResult initialise();
   EmptyResult finalize();

   EmptyResult encrypt_update(std::istream &in_stream, std::ostream &out_stream, std::size_t count);
   EmptyResult decrypt_update(std::istream &in_stream, std::ostream &out_stream, std::size_t count);

   EmptyResult encrypt_update_buffer(const container::BufferView &in_buffer, container::BufferView out_buffer);
   EmptyResult decrypt_update_buffer(const container::BufferView &in_buffer, container::BufferView out_buffer);

 private:
   container::Buffer m_key;
   container::Buffer m_iv;
   EVP_CIPHER_CTX *m_encrypt_ctx;
   EVP_CIPHER_CTX *m_decrypt_ctx;
};

}// namespace minecpp::crypto