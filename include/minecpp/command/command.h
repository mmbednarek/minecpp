#ifndef MINECPP_COMMAND_H
#define MINECPP_COMMAND_H
#include "object.h"
#include <memory>
#include <minecpp/command/object.h>
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

struct CommandInput
{
   std::vector<Object::Ptr> arguments;
   std::unordered_set<std::string> flags;
   std::unordered_map<std::string, Object::Ptr> params;
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
