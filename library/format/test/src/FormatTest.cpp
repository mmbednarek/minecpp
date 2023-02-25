#include <gtest/gtest.h>
#include <minecpp/format/Format.h>

TEST(Format, ok)
{
   auto text = minecpp::format::Builder()
                       .text("hello ")
                       .bold(minecpp::format::Color::DarkPurple, "purple ")
                       .text(minecpp::format::Color::Green, "world")
                       .to_string();

   EXPECT_EQ(
           text,
           R"({"text": "hello ", "extra": [{"text": "purple ", "color": "dark_purple", "bold": true}, {"text": "world", "color": "green"}]})");
}