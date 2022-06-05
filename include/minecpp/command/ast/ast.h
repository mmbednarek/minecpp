#ifndef MINECPP_AST_H
#define MINECPP_AST_H
#include "../object.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace minecpp::command {
class RuntimeContext;
}

namespace minecpp::command::ast {

class Expression
{
 public:
   using Ptr = std::unique_ptr<Expression>;

   virtual ~Expression() noexcept = default;

   virtual Object::Ptr execute(RuntimeContext &ctx)                 = 0;
   [[nodiscard]] virtual ObjectType type(RuntimeContext &ctx) const = 0;
};

class Command : public Expression
{
 public:
   std::string name;
   std::vector<Expression::Ptr> arguments;
   std::unordered_set<std::string> flags;
   std::unordered_map<std::string, Expression::Ptr> params;

   Object::Ptr execute(RuntimeContext &ctx) override;
   [[nodiscard]] ObjectType type(RuntimeContext &ctx) const override;
};

struct String : public Expression
{
   std::string value;

   explicit String(std::string value) :
       value(std::move(value))
   {
   }

   Object::Ptr execute(RuntimeContext &) override
   {
      return std::make_unique<StringObject>(value);
   }

   [[nodiscard]] ObjectType type(RuntimeContext &ctx) const override
   {
      return ObjectType::String;
   }
};

struct Int : public Expression
{
   int value;

   explicit Int(int value) :
       value(value)
   {
   }

   Object::Ptr execute(RuntimeContext &) override
   {
      return std::make_unique<IntObject>(value);
   }

   [[nodiscard]] ObjectType type(RuntimeContext &ctx) const override
   {
      return ObjectType::Int32;
   }
};

struct Variable : public Expression
{
   std::string name;

   explicit Variable(std::string name) :
       name(std::move(name))
   {
   }

   Object::Ptr execute(RuntimeContext &ctx) override;

   [[nodiscard]] ObjectType type(RuntimeContext &ctx) const override;
};

}// namespace minecpp::command::ast

#endif//MINECPP_AST_H
