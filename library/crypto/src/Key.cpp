#include <cassert>
#include <minecpp/crypto/Key.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <vector>

namespace minecpp::crypto {

PrivateKey::PrivateKey(int bits) :
    m_rsa_key(EVP_RSA_gen(bits))
{
}

PrivateKey::PrivateKey(std::string_view pem_file, std::string_view pass_phrase)
{
   BIO *file = BIO_new_file(pem_file.data(), "r+");
   assert(file);
   PEM_read_bio_PrivateKey(file, &m_rsa_key, nullptr, const_cast<char *>(pass_phrase.data()));
   BIO_free(file);
}

PrivateKey::~PrivateKey()
{
   if (m_rsa_key != nullptr) {
      EVP_PKEY_free(m_rsa_key);
   }
}

Result<container::Buffer> PrivateKey::decrypt_message(const container::BufferView &buff)
{
   auto *ctx = EVP_PKEY_CTX_new(m_rsa_key, nullptr);

   if (not EVP_PKEY_decrypt_init(ctx)) {
      EVP_PKEY_CTX_free(ctx);
      return ErrorType::DecryptionInitError;
   }

   std::size_t output_length = 2048;
   if (not EVP_PKEY_decrypt(ctx, nullptr, &output_length, buff.data(), buff.size())) {
      EVP_PKEY_CTX_free(ctx);
      return ErrorType::DecryptionError;
   }

   container::Buffer output(output_length);

   if (not EVP_PKEY_decrypt(ctx, output.data(), &output_length, buff.data(), buff.size())) {
      EVP_PKEY_CTX_free(ctx);
      return ErrorType::DecryptionError;
   }

   EVP_PKEY_CTX_free(ctx);

   output.truncate(output_length);

   return {std::move(output)};
}

Result<container::Buffer> PrivateKey::encrypt_message(const container::BufferView &buff)
{
   auto *ctx = EVP_PKEY_CTX_new(m_rsa_key, nullptr);

   if (not EVP_PKEY_encrypt_init(ctx)) {
      EVP_PKEY_CTX_free(ctx);
      return ErrorType::EncryptionInitError;
   }

   std::size_t output_length = 2048;
   if (not EVP_PKEY_encrypt(ctx, nullptr, &output_length, buff.data(), buff.size())) {
      EVP_PKEY_CTX_free(ctx);
      return ErrorType::EncryptionError;
   }

   container::Buffer output(output_length);

   if (not EVP_PKEY_encrypt(ctx, output.data(), &output_length, buff.data(), buff.size())) {
      EVP_PKEY_CTX_free(ctx);
      return ErrorType::EncryptionError;
   }

   return {std::move(output)};
}

std::size_t PrivateKey::write_public_key(std::ostream &stream)
{
   BIO *sink = BIO_new(BIO_s_mem());
   if (sink == nullptr) {
      return 0;
   }
   if (not i2d_PUBKEY_bio(sink, m_rsa_key)) {
      BIO_free(sink);
      return 0;
   }

   std::size_t total_bytes_read{};

   int bytes_read_count{};
   do {
      char buff[1024];
      bytes_read_count = BIO_gets(sink, buff, 1024);
      stream.write(buff, bytes_read_count);
      total_bytes_read += static_cast<std::size_t>(bytes_read_count);
   } while (bytes_read_count == 1024);

   BIO_free(sink);
   return total_bytes_read;
}

Result<container::Buffer> PrivateKey::public_key()
{
   BIO *sink = BIO_new(BIO_s_mem());
   if (sink == nullptr) {
      return ErrorType::InvalidArgument;
   }
   if (not i2d_PUBKEY_bio(sink, m_rsa_key)) {
      BIO_free(sink);
      return ErrorType::InvalidArgument;
   }

   container::Buffer output(1024);
   auto read_count = BIO_read(sink, output.data(), 1024);
   output.truncate(static_cast<std::size_t>(read_count));
   BIO_free(sink);
   return output;
}

}// namespace minecpp::crypto