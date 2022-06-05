#include <gtest/gtest.h>
#include <minecpp/command/command.h>
#include <minecpp/command/command_manager.h>
#include <minecpp/command/parser.h>
#include <minecpp/command/runtime_context.h>
#include <minecpp/lexer/lexer.h>
#include <minecpp/lexer/reader.h>

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
};

class StdOutStream : public minecpp::command::OutputStream
{
 public:
   bool write(minecpp::command::Object::Ptr obj) override
   {
      std::cout << obj->to_string() << '\n';
      return true;
   }
};

TEST(CommandTest, BasicTest)
{
   StdOutStream out;

   minecpp::command::CommandManager manager;
   manager.register_command<EchoCommand>("echo");

   minecpp::command::RuntimeContext ctx(manager, minecpp::command::g_null_stream, out);

   manager.evaluate(ctx, "echo hello world");
}