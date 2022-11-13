#include <minecpp/crypto/AESKey.h>
#include <openssl/aes.h>

namespace minecpp::crypto {

AESKey::AESKey(container::Buffer key, container::Buffer iv) :
    m_key(std::move(key)),
    m_iv(std::move(iv)),
    m_encrypt_ctx(EVP_CIPHER_CTX_new()),
    m_decrypt_ctx(EVP_CIPHER_CTX_new())
{
}

AESKey::~AESKey()
{
   if (m_encrypt_ctx != nullptr) {
      EVP_CIPHER_CTX_free(m_encrypt_ctx);
      m_encrypt_ctx = nullptr;
   }
   if (m_decrypt_ctx != nullptr) {
      EVP_CIPHER_CTX_free(m_decrypt_ctx);
      m_decrypt_ctx = nullptr;
   }
}

Result<container::Buffer> AESKey::encrypt_message(const container::Buffer &buff)
{
   if (not EVP_EncryptInit(m_encrypt_ctx, EVP_aes_128_cfb8(), m_key.data(), m_iv.data())) {
      return ErrorType::InvalidArgument;
   }
   if (not EVP_CIPHER_CTX_set_key_length(m_encrypt_ctx, static_cast<int>(m_key.size()))) {
      return ErrorType::InvalidArgument;
   }
   if (not EVP_CIPHER_CTX_ctrl(m_encrypt_ctx, EVP_CTRL_GCM_SET_IVLEN, static_cast<int>(m_iv.size()),
                               nullptr)) {
      return ErrorType::InvalidArgument;
   }

   auto data_size = static_cast<int>(2 * buff.size());
   container::Buffer message(static_cast<std::size_t>(data_size));
   if (not EVP_EncryptUpdate(m_encrypt_ctx, message.data(), &data_size, buff.data(),
                             static_cast<int>(buff.size()))) {
      return ErrorType::InvalidArgument;
   }

   int out_size = data_size;
   if (not EVP_EncryptFinal(m_encrypt_ctx, message.data() + data_size, &out_size)) {
      return ErrorType::InvalidArgument;
   }

   message.truncate(static_cast<std::size_t>(data_size + out_size));
   return message;
}

Result<container::Buffer> AESKey::decrypt_message(const container::Buffer &buff)
{
   if (not EVP_DecryptInit(m_decrypt_ctx, EVP_aes_128_cfb8(), m_key.data(), m_iv.data())) {
      return ErrorType::InvalidArgument;
   }
   if (not EVP_CIPHER_CTX_set_key_length(m_decrypt_ctx, static_cast<int>(m_key.size()))) {
      return ErrorType::InvalidArgument;
   }
   if (not EVP_CIPHER_CTX_ctrl(m_decrypt_ctx, EVP_CTRL_GCM_SET_IVLEN, static_cast<int>(m_iv.size()),
                               nullptr)) {
      return ErrorType::InvalidArgument;
   }

   auto data_size = static_cast<int>(2 * buff.size());
   container::Buffer message(static_cast<std::size_t>(data_size));
   if (not EVP_DecryptUpdate(m_decrypt_ctx, message.data(), &data_size, buff.data(),
                             static_cast<int>(buff.size()))) {
      return ErrorType::InvalidArgument;
   }

   auto finalize_size = data_size;
   if (not EVP_DecryptFinal(m_decrypt_ctx, message.data() + data_size, &finalize_size)) {
      return ErrorType::InvalidArgument;
   }
   message.truncate(static_cast<std::size_t>(data_size + finalize_size));

   return message;
}

AESKey::AESKey(AESKey &&other) noexcept :
    m_encrypt_ctx(std::exchange(other.m_encrypt_ctx, nullptr)),
    m_decrypt_ctx(std::exchange(other.m_decrypt_ctx, nullptr))
{
}

AESKey &AESKey::operator=(AESKey &&other) noexcept
{
   m_encrypt_ctx = std::exchange(other.m_encrypt_ctx, nullptr);
   m_decrypt_ctx = std::exchange(other.m_decrypt_ctx, nullptr);
   return *this;
}


}// namespace minecpp::crypto