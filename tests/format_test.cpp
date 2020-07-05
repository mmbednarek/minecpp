#include <gtest/gtest.h>
#include <format/format.h>

TEST(Format, ok) {
   Format::Builder test;
   test.text("hello ");
   test.bold(Format::Color::DarkPurple, "purple ");
   test.text(Format::Color::Green, "world");

   EXPECT_EQ(test.build(), R"({"extra":[{"color":"white","text":"hello "},{"color":"dark_purple","bold":true,"text":"purple "},{"color":"green","text":"world"}],"text":""})");
}