#ifndef MINECPP_OBJECT_H
#define MINECPP_OBJECT_H
#include <boost/uuid/uuid_io.hpp>
#include <fmt/core.h>
#include <memory>
#include <minecpp/format/Format.h>
#include <minecpp/game/BlockPosition.h>
#include <minecpp/util/Uuid.h>
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
   RuntimeError,
   BlockPosition
};

class Object
{
 public:
   using Ptr = std::shared_ptr<Object>;

   virtual ~Object() noexcept = default;

   virtual ObjectType type()       = 0;
   virtual std::string to_string() = 0;
};

template<typename T>
struct WrapperFinder
{
   using Type = Object;
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

template<>
struct WrapperFinder<std::string>
{
   using Type = StringObject;
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

template<>
struct WrapperFinder<int>
{
   using Type = IntObject;
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

template<>
struct WrapperFinder<util::uuid>
{
   using Type = UUIDObject;
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

template<typename... TArgs>
std::shared_ptr<RuntimeError> make_error(std::string command_name, fmt::format_string<TArgs...> format_str,
                                         TArgs &&...args)
{
   auto err = std::make_shared<RuntimeError>(std::move(command_name));
   auto msg = fmt::format(format_str, std::forward<TArgs>(args)...);
   err->text(msg);
   return err;
}

struct BlockPositionObject final : public Object
{
   constexpr static ObjectType object_type = ObjectType::BlockPosition;

   game::BlockPosition value;

   explicit BlockPositionObject(game::BlockPosition position) :
       value{position}
   {
   }

   BlockPositionObject(int x, int y, int z) :
       value{x, y, z}
   {
   }

   ObjectType type() override
   {
      return object_type;
   }

   std::string to_string() override
   {
      return fmt::format("({}, {}, {})", value.x(), value.y(), value.z());
   }
};

template<>
struct WrapperFinder<game::BlockPosition>
{
   using Type = BlockPositionObject;
};

struct ArrayObject final : public Object
{
   constexpr static ObjectType object_type = ObjectType::Array;

   std::vector<Object::Ptr> value;

   ObjectType type() override
   {
      return object_type;
   }

   template<typename TObj>
   void emplace_back(TObj &&obj)
   {
      this->value.emplace_back(std::make_shared<typename WrapperFinder<TObj>::Type>(std::forward<TObj>(obj)));
   }

   [[nodiscard]] std::string to_string() override;
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

template<typename TResult, typename... TArgs>
std::shared_ptr<typename WrapperFinder<TResult>::Type> make_obj(TArgs &&...args)
{
   return std::make_shared<typename WrapperFinder<TResult>::Type>(std::forward<TArgs>(args)...);
}

}// namespace minecpp::command

#endif//MINECPP_OBJECT_H