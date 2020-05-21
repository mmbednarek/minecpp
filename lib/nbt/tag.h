#pragma once
#include "exception.h"
#include <cstdint>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace NBT {

enum TagID : uint8_t {
   End,
   Byte,
   Short,
   Int,
   Long,
   Float,
   Double,
   ByteArray,
   String,
   List,
   Compound,
   IntArray,
   LongArray,
};

class ListPayload {
 public:
   ListPayload();
   ListPayload(TagID type, void *ptr);
   TagID type();

   template <typename T> std::vector<T> &value();

 private:
   TagID _type;
   void *ptr;
};

std::string tagid_to_str(TagID tagid);

template <TagID t> inline auto tagid_default() = delete;
template <typename T> constexpr TagID tagid_from_type() {
   return TagID::List; // list is the only not specified type
}

#define tagid_type(tagid) decltype(tagid_default<tagid>())

#define tagid_default_of(tagid, ...)                                           \
   template <> inline auto tagid_default<tagid>() { return __VA_ARGS__; };     \
   template <> constexpr TagID tagid_from_type<tagid_type(tagid)>() {          \
      return tagid;                                                            \
   };

class Tag;
class ListPayload;
typedef std::shared_ptr<Tag> TagPtr;
typedef std::map<std::string, std::shared_ptr<Tag>> TagMap;

tagid_default_of(TagID::Byte, static_cast<uint8_t>(0)) tagid_default_of(
    TagID::Short, static_cast<short>(0)) tagid_default_of(TagID::Int,
                                                          static_cast<int>(0))
 tagid_default_of(TagID::Long, static_cast<long long>(0))

tagid_default_of(TagID::Float, static_cast<float>(0.0f))

tagid_default_of(TagID::Double, static_cast<double>(0))

tagid_default_of(TagID::ByteArray, std::vector<uint8_t>())

tagid_default_of(TagID::String, std::string())

tagid_default_of(TagID::List, ListPayload(End, nullptr))

tagid_default_of(TagID::Compound, TagMap())

tagid_default_of(TagID::IntArray, std::vector<int>())

tagid_default_of(TagID::LongArray, std::vector<long long>())

class Tag {
 public:
   Tag(TagID t, std::string &s);

   TagID type();
   std::string name();

   template <typename T> T &value();

 private:
   TagID _type;
   std::string _name;
};

template <typename P> class PayloadTag : public Tag {
 public:
   PayloadTag(std::string &name, P payload)
       : Tag(tagid_from_type<P>(), name), _payload(std::move(payload)) {}

   P &payload() { return _payload; }

 private:
   P _payload;
};

template <typename T> T &Tag::value() {
   if (tagid_from_type<T>() != _type)
      throw Exception("incorrect type");

   return static_cast<PayloadTag<T> *>(this)->payload();
}

template <typename T> std::vector<T> &ListPayload::value() {
   if (tagid_from_type<T>() != _type)
      throw Exception("invalid list payload type");
   return *reinterpret_cast<std::vector<T> *>(ptr);
}

} // namespace NBT
