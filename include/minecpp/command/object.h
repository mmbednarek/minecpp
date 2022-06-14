#ifndef MINECPP_OBJECT_H
#define MINECPP_OBJECT_H
#include <boost/uuid/uuid_io.hpp>
#include <fmt/core.h>
#include <memory>
#include <minecpp/format/format.h>
#include <minecpp/util/uuid.h>
#include <string>
#include <utility>

namespace minecpp::command {

enum class ObjectType
{
   Null,
   Int32,
   String,
   Boolean,
   Array,
   List,
   UUID,
   FormattedString,
   RuntimeError
};

class Object
{
 public:
   using Ptr = std::shared_ptr<Object>;

   virtual ~Object() noexcept = default;

   virtual ObjectType type()       = 0;
   virtual std::string to_string() = 0;
};

struct StringObject final : public Object
{
   constexpr static ObjectType object_type = ObjectType::String;

   std::string value;

   explicit StringObject(std::string value) :
       value(std::move(value))
   {
   }

   ObjectType type() override
   {
      return object_type;
   }

   std::string to_string() override
   {
      return value;
   }
};

struct IntObject final : public Object
{
   constexpr static ObjectType object_type = ObjectType::Int32;

   int value;

   explicit IntObject(int value) :
       value(value)
   {
   }

   ObjectType type() override
   {
      return object_type;
   }

   std::string to_string() override
   {
      return std::to_string(value);
   }
};

struct UUIDObject final : public Object
{
   constexpr static ObjectType object_type = ObjectType::UUID;

   util::uuid value;

   explicit UUIDObject(util::uuid value) :
       value(value)
   {
   }

   ObjectType type() override
   {
      return object_type;
   }

   std::string to_string() override
   {
      return boost::uuids::to_string(value);
   }
};

struct FormattedString : public Object
{
   constexpr static ObjectType object_type = ObjectType::FormattedString;

   struct Node
   {
      minecpp::format::Color color;
      bool bold;
      std::string text;

      void format(format::Builder &builder) const
      {
         if (bold) {
            builder.bold(color, text);
            return;
         }
         builder.text(color, text);
      }
   };

   std::vector<Node> nodes;

   FormattedString &text(std::string_view text)
   {
      nodes.push_back(FormattedString::Node{format::Color::White, false, std::string(text)});
      return *this;
   }

   FormattedString &text(format::Color color, std::string_view text)
   {
      nodes.push_back(FormattedString::Node{color, false, std::string(text)});
      return *this;
   }

   FormattedString &bold(std::string_view text)
   {
      nodes.push_back(FormattedString::Node{format::Color::White, true, std::string(text)});
      return *this;
   }

   FormattedString &bold(format::Color color, std::string_view text)
   {
      nodes.push_back(FormattedString::Node{color, true, std::string(text)});
      return *this;
   }

   ObjectType type() override
   {
      return object_type;
   }

   std::string to_string() override
   {
      format::Builder builder;
      for (const auto &node : nodes) {
         node.format(builder);
      }
      return builder.to_string();
   }
};

struct RuntimeError : public FormattedString
{
   constexpr static ObjectType object_type = ObjectType::RuntimeError;
   std::string command;

   explicit RuntimeError(std::string command) :
       command(std::move(command))
   {
   }

   ObjectType type() override
   {
      return object_type;
   }

   std::string to_string() override
   {
      format::Builder builder;
      builder.bold(format::Color::Red, "COMMAND FAILED ");
      builder.text("error running command ").text(format::Color::Yellow, command).text(": ");
      for (const auto &node : nodes) {
         node.format(builder);
      }
      return builder.to_string();
   }
};

template<typename T>
T *cast(const Object::Ptr &object)
{
   if (object == nullptr) {
      return nullptr;
   }
   if (object->type() != T::object_type) {
      return nullptr;
   }
   return dynamic_cast<T *>(object.get());
}

}// namespace minecpp::command

#endif//MINECPP_OBJECT_H