#ifndef MINECPP_OBJECT_H
#define MINECPP_OBJECT_H
#include <boost/uuid/uuid_io.hpp>
#include <memory>
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
   UUID
};

class Object
{
 public:
   using Ptr = std::shared_ptr<Object>;

   virtual ~Object() noexcept = default;

   virtual ObjectType type() = 0;
   virtual std::string to_string() = 0;
};

struct StringObject final : public Object {
   constexpr static ObjectType object_type = ObjectType::String;

   std::string value;

   explicit StringObject(std::string value) :
       value(std::move(value))
   {
   }

   ObjectType type() override {
      return object_type;
   }

   std::string to_string() override {
      return value;
   }
};

struct IntObject final : public Object {
   constexpr static ObjectType object_type = ObjectType::Int32;

   int value;

   explicit IntObject(int value) :
           value(value)
   {
   }

   ObjectType type() override {
      return object_type;
   }

   std::string to_string() override {
      return std::to_string(value);
   }
};

struct UUIDObject final : public Object {
   constexpr static ObjectType object_type = ObjectType::UUID;

   util::uuid value;

   explicit UUIDObject (util::uuid value) :
           value(value)
   {
   }

   ObjectType type() override {
      return object_type;
   }

   std::string to_string() override {
      return boost::uuids::to_string(value);
   }
};

template<typename T>
T *cast(const Object::Ptr& object) {
   if  (object == nullptr) {
      return nullptr;
   }
   if (object->type() != T::object_type) {
      return nullptr;
   }
   return dynamic_cast<T *>(object.get());
}

}// namespace minecpp::command

#endif//MINECPP_OBJECT_H