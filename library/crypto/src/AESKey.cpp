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

Result<mb::empty> AESKey::initialise()
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

   return mb::ok;
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

EmptyResult AESKey::encrypt_update(std::istream &in_stream, std::ostream &out_stream, std::size_t count)
{
   char in_data[count];
   in_stream.read(in_data, static_cast<int>(count));

   int data_size = static_cast<int>(count);
   unsigned char out_data[data_size];

   if (not EVP_EncryptUpdate(m_encrypt_ctx, out_data, &data_size, reinterpret_cast<std::uint8_t *>(in_data),
                             static_cast<int>(count))) {
      return ErrorType::EncryptionError;
   }

   out_stream.write(reinterpret_cast<const char *>(out_data), data_size);
   return mb::ok;
}

EmptyResult AESKey::decrypt_update(std::istream &in_stream, std::ostream &out_stream, std::size_t count)
{
   char in_data[count];
   in_stream.read(in_data, static_cast<int>(count));

   unsigned char out_data[count];
   int data_size = static_cast<int>(count);

   if (not EVP_DecryptUpdate(m_decrypt_ctx, out_data, &data_size, reinterpret_cast<std::uint8_t *>(in_data),
                             static_cast<int>(count))) {
      return ErrorType::DecryptionError;
   }

   out_stream.write(reinterpret_cast<const char *>(out_data), data_size);
   return mb::ok;
}

Result<mb::empty> AESKey::finalize()
{
   char data[128];
   int data_size = 128;

   if (not EVP_DecryptFinal(m_decrypt_ctx, reinterpret_cast<std::uint8_t *>(data), &data_size)) {
      return ErrorType::InvalidArgument;
   }

   data_size = 128;
   if (not EVP_EncryptFinal(m_encrypt_ctx, reinterpret_cast<std::uint8_t *>(data), &data_size)) {
      return ErrorType::InvalidArgument;
   }

   return mb::ok;
}


}// namespace minecpp::crypto