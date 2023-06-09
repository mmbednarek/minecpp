#include <gtest/gtest.h>
#include <minecpp/crypto/Key.h>

using minecpp::container::Buffer;
using minecpp::crypto::PrivateKey;

TEST(MinecppCrypto, RSA_GeneratedKey)
{
   std::string message("hello world");
   auto input_buffer = minecpp::container::Buffer::from_string(message);

   minecpp::crypto::PrivateKey key(1024);

   auto encrypted_message = key.encrypt_message(input_buffer.as_view());
   ASSERT_TRUE(encrypted_message.ok());

   auto decrypted_message = key.decrypt_message(encrypted_message->as_view());
   ASSERT_TRUE(decrypted_message.ok());

   auto original_message = decrypted_message->to_string();

   ASSERT_EQ(message, original_message);
}

TEST(MinecppCrypto, RSA_KeyLoadedFromFile)
{
   std::string message("hello world");
   auto input_buffer = minecpp::container::Buffer::from_string(message);

   minecpp::crypto::PrivateKey key("key.pem", "");

   auto encrypted_message = key.encrypt_message(input_buffer.as_view());
   ASSERT_TRUE(encrypted_message.ok());

   auto decrypted_message = key.decrypt_message(encrypted_message->as_view());
   ASSERT_TRUE(decrypted_message.ok());

   auto original_message = decrypted_message->to_string();

   ASSERT_EQ(message, original_message);
}
