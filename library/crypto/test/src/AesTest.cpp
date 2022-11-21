#include <gtest/gtest.h>
#include <minecpp/crypto/AESKey.h>

using minecpp::container::Buffer;
using minecpp::crypto::AESKey;

TEST(MinecppCrypto, AES_ProvidedKey)
{
   auto key = Buffer::from_string("AAAAAAAAAAAAAAAAA");
   key.truncate(16);

   auto iv = Buffer::from_string("BBBBBBBBBBBBBBBBB");
   key.truncate(16);

   minecpp::crypto::AESKey aes(key, iv);
   ASSERT_TRUE(aes.initialise().ok());

   std::string original_message_1{"secret message 1"};
   std::string original_message_2{"secret message 2"};

   std::stringstream plaintext_stream;
   plaintext_stream << original_message_1;

   std::stringstream ciphertext_stream;
   ASSERT_TRUE(aes.encrypt_update(plaintext_stream, ciphertext_stream, original_message_1.size()).ok());

   plaintext_stream << original_message_2;
   ASSERT_TRUE(aes.encrypt_update(plaintext_stream, ciphertext_stream, original_message_2.size()).ok());

   std::stringstream decrypted_stream;
   ASSERT_TRUE(aes.decrypt_update(ciphertext_stream, decrypted_stream, original_message_1.size()).ok());
   ASSERT_TRUE(aes.decrypt_update(ciphertext_stream, decrypted_stream, original_message_2.size()).ok());

   ASSERT_TRUE(aes.finalize().ok());

   auto decrypted_message = Buffer::from_istream(decrypted_stream);

   ASSERT_EQ(decrypted_message.to_string(), "secret message 1secret message 2");
}

TEST(MinecppCrypto, AES_DecryptByByte)
{
   auto key = Buffer::from_string("AAAAAAAAAAAAAAAAA");
   key.truncate(16);

   auto iv = Buffer::from_string("BBBBBBBBBBBBBBBBB");
   key.truncate(16);

   minecpp::crypto::AESKey aes(key, iv);
   ASSERT_TRUE(aes.initialise().ok());

   std::string original_message_1{"secret message 1"};
   std::string original_message_2{"secret message 2"};

   std::stringstream plaintext_stream;
   plaintext_stream << original_message_1;

   std::stringstream ciphertext_stream;
   ASSERT_TRUE(aes.encrypt_update(plaintext_stream, ciphertext_stream, original_message_1.size()).ok());

   plaintext_stream << original_message_2;
   ASSERT_TRUE(aes.encrypt_update(plaintext_stream, ciphertext_stream, original_message_2.size()).ok());

   std::stringstream decrypted_stream;
   for (std::size_t i = 0; i < (original_message_1.size() + original_message_2.size()); ++i) {
      ASSERT_TRUE(aes.decrypt_update(ciphertext_stream, decrypted_stream, 1).ok());
   }

   ASSERT_TRUE(aes.finalize().ok());

   auto decrypted_message = Buffer::from_istream(decrypted_stream);

   ASSERT_EQ(decrypted_message.to_string(), "secret message 1secret message 2");
}
