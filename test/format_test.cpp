#include <gtest/gtest.h>
#include <minecpp/format/format.h>

TEST(Format, ok)
{
   auto text = minecpp::format::Builder()
                       .text("hello ")
                       .bold(minecpp::format::Color::DarkPurple, "purple ")
                       .text(minecpp::format::Color::Green, "world")
                       .to_string();

   EXPECT_EQ(
           text,
           R"({"extra":[{"color":"white","text":"hello "},{"color":"dark_purple","bold":true,"text":"purple "},{"color":"green","text":"world"}],"text":""})");
}