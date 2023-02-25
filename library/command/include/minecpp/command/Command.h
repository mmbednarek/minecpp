#ifndef MINECPP_COMMAND_H
#define MINECPP_COMMAND_H
#include "Object.h"
#include <memory>
#include <minecpp/command/ast/Ast.h>
#include <minecpp/command/Object.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace minecpp::command {

class RuntimeContext;

class InputStream
{
 public:
   virtual ~InputStream() noexcept = default;

   virtual Object::Ptr read() = 0;
};

class OutputStream
{
 public:
   virtual ~OutputStream() noexcept = default;

   virtual bool write(Object::Ptr obj) = 0;
};

class NullStream : public InputStream,
                   public OutputStream
{
 public:
   Object::Ptr read() override
   {
      return {};
   }

   bool write(Object::Ptr obj) override
   {
      return false;
   }
};

extern NullStream g_null_stream;

class CommandInput
{
 public:
   using iterator = std::vector<Object::Ptr>::iterator;
   CommandInput(RuntimeContext &ctx, const std::vector<ast::Expression::Ptr> &arguments,
                const std::unordered_set<std::string> &flags,
                const std::unordered_map<std::string, ast::Expression::Ptr> &params);
   [[nodiscard]] std::size_t arg_count() const;
   [[nodiscard]] Object::Ptr obj_org(std::size_t index) const;
   [[nodiscard]] std::string string_arg(std::size_t index) const;

   iterator begin();
   iterator end();

 private:
   std::vector<Object::Ptr> m_arguments;
   std::unordered_set<std::string> m_flags;
   std::unordered_map<std::string, Object::Ptr> m_params;
};

class Command
{
 public:
   virtual ~Command() noexcept = default;

   virtual bool is_flag(std::string_view name) const                       = 0;
   virtual ObjectType return_type(RuntimeContext &ctx) const               = 0;
   virtual Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const = 0;
};

}// namespace minecpp::command

#endif//MINECPP_COMMAND_H
