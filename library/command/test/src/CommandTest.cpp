#include <gtest/gtest.h>
#include <minecpp/command/Command.h>
#include <minecpp/command/CommandManager.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/lexer/Lexer.h>

class EchoCommand : public minecpp::command::Command
{
 public:
   [[nodiscard]] bool is_flag(std::string_view name) const override
   {
      if (name == "f")
         return false;
      return true;
   }

   minecpp::command::Object::Ptr run(minecpp::command::RuntimeContext &ctx,
                                     minecpp::command::CommandInput &input) const override
   {
      for (auto &obj : input.arguments) {
         ctx.out().write(obj);
      }
      return {};
   }

   minecpp::command::ObjectType return_type(minecpp::command::RuntimeContext &ctx) const override
   {
      return minecpp::command::ObjectType::Null;
   }
};

class StringOutStream : public minecpp::command::OutputStream
{
 public:
   bool write(minecpp::command::Object::Ptr obj) override
   {
      m_ss << obj->to_string() << ' ';
      return true;
   }

   std::string to_string() const
   {
      return m_ss.str();
   }

 private:
   std::stringstream m_ss;
};

TEST(CommandTest, BasicTest)
{
   StringOutStream out;

   minecpp::command::CommandManager manager;
   manager.register_command<EchoCommand>("echo");

   minecpp::command::RuntimeContext ctx(manager, minecpp::command::g_null_stream, out, nullptr);

   manager.evaluate(ctx, "echo hello world");
   EXPECT_EQ(out.to_string(), "hello world ");
}