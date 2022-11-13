#include <gtest/gtest.h>
#include <minecpp/crypto/AESKey.h>

using minecpp::container::Buffer;
using minecpp::crypto::AESKey;

TEST(MinecppCrypto, AES_ProvidedKey)
{
   std::string message("hello world");
   auto input_buffer = minecpp::container::Buffer::from_string(message);

   auto key = minecpp::container::Buffer::from_string("AAAAAAAAAAAAAAAAA");
   auto iv  = minecpp::container::Buffer::from_string("BBBBBBBBBBBBBBBBB");

   minecpp::crypto::AESKey aes(key, iv);

   auto encrypted_message = aes.encrypt_message(input_buffer);
   ASSERT_TRUE(encrypted_message.ok());

   auto decrypted_message = aes.decrypt_message(*encrypted_message);
   ASSERT_TRUE(decrypted_message.ok());

   ASSERT_EQ(decrypted_message->to_string(), message);
}
