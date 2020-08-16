#pragma once
#include <algorithm>
#include <any>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace NBT {

enum class TagId : uint8_t {
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

struct Content {
   TagId tag_id;
   std::any content;

   template<typename T>
   [[nodiscard]] T as() const {
      if (typeid(T) == content.type()) {
         return std::any_cast<T>(content);
      }
      if constexpr (std::is_same<T, std::string>::value) {
         return to_string();
      }
      return T{};
   }

   template<typename T>
   [[nodiscard]] T as_or(T alt) const {
      if (typeid(T) == content.type()) {
         return std::any_cast<T>(content);
      }
      return alt;
   }

   template<typename T>
   std::vector<T> as_vec();

   std::string to_string(int padding = 0) const;
   bool empty() const;
};

Content make_string(std::string s);

using CompoundContent = std::map<std::string, Content>;

struct ListContent {
   TagId tag_id;
   std::vector<std::any> elements;
   class Iterator {
      ListContent &list;
      std::size_t at;

    public:
      explicit Iterator(ListContent &list, std::size_t at = 0) : list(list), at(at) {}

      Iterator &operator++() {
         if (at >= list.elements.size()) {
            return *this;
         }
         at++;
         return *this;
      }

      Iterator operator++(int) {
         auto value = *this;
         ++(*this);
         return value;
      }

      bool operator==(Iterator other) const {
         return at == other.at;
      }

      bool operator!=(Iterator other) const {
         return at != other.at;
      }

      Content operator*() const {
         return Content{
                 .tag_id = list.tag_id,
                 .content = list.elements.at(at),
         };
      }

      using difference_type = Content;
      using value_type = Content;
      using pointer = const Content *;
      using reference = const Content &;
      using iterator_category = std::forward_iterator_tag;
   };

   Content operator[](const std::size_t index) {
      return Content{
              .tag_id = tag_id,
              .content = elements[index],
      };
   }

   Iterator begin() {
      return Iterator(*this, 0);
   }

   Iterator end() {
      return Iterator(*this, elements.size());
   }

   template<typename T>
   std::vector<T> as_vec() {
      std::vector<T> result(elements.size());
      std::transform(begin(), end(), result.begin(), [](const NBT::Content &el) {
         return el.as<T>();
      });
      return result;
   }
};

struct NamedTag {
   std::string name;
   Content content;

   NamedTag(std::string name, TagId tag_id, std::any content);
};

template<typename T>
std::vector<T> Content::as_vec() {
   switch (tag_id) {
   case TagId::List:
      return as<ListContent>().as_vec<T>();
   case TagId::ByteArray:
      if constexpr (std::is_same<T, uint8_t>::value) {
         return as<std::vector<T>>();
      }
      break;
   case TagId::IntArray:
      if constexpr (std::is_same<T, int32_t>::value) {
         return as<std::vector<T>>();
      }
      break;
   case TagId::LongArray:
      if constexpr (std::is_same<T, int64_t>::value) {
         return as<std::vector<T>>();
      }
      break;
   default:
      break;
   }
   return std::vector<T>();
}

}// namespace NBT
