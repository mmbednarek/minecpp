#pragma once
#include "error.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>

struct empty {};
constexpr empty result_ok = empty{};

template<typename T>
class result {
   struct container {
      T value;
   };
   std::variant<container, std::unique_ptr<error>> value;

   result() = default;

 public:
   result(error e);
   result(error::ptr e);
   result(T value);
   result(const result &other);

   result &operator=(T value);
   T unwrap();
   T unwrap(T alt);
   [[nodiscard]] bool ok() const;
   [[nodiscard]] std::string msg() const;
   [[nodiscard]] error::ptr err();
   [[nodiscard]] error::ptr err_cp() const;
};

template<typename T>
result<T>::result(T value) : value(container{std::forward<T>(value)}) {}

template<typename T>
result<T>::result(error e) : value(std::make_unique<error>(e)) {}

template<typename T>
result<T>::result(error::ptr e) : value(std::move(e)) {}

template<typename T>
result<T>::result(const result &other) {
   if (!other.ok()) {
      value = std::move(other.err_cp());
   }

   if constexpr (std::is_copy_constructible_v<T>) {
      value = container{T(std::get<T>(other.value))};
   } else {
      value = container{std::move(std::get<T>(other.value))};
   }
}

template<typename T>
result<T> &result<T>::operator=(T val) {
   value = std::move(val);
   return *this;
}

template<typename T>
T result<T>::unwrap() {
   if (ok()) {
      if constexpr (std::is_reference<T>::value) {
         return std::get<container>(value).value;
      } else {
         return std::move(std::get<container>(value).value);
      }
   }
   throw std::runtime_error(msg());
}

template<typename T>
T result<T>::unwrap(T alt) {
   if (ok()) {
      return std::move(std::get<container>(value).value);
   }
   return alt;
}

template<typename T>
bool result<T>::ok() const { return std::holds_alternative<container>(value); }

template<typename T>
std::string result<T>::msg() const {
   if (ok()) {
      return std::string();
   }
   return std::get<error::ptr>(value)->msg();
}

template<typename T>
error::ptr result<T>::err() {
   if (ok()) {
      return error::ptr(nullptr);
   }
   return std::move(std::get<error::ptr>(value));
}

template<typename T>
[[nodiscard]] error::ptr result<T>::err_cp() const {
   if (ok()) {
      return error::ptr(nullptr);
   }
   return std::make_unique<error>(*std::get<error::ptr>(value));
}

#define tryget(stmt) ({ \
   auto res = stmt;     \
   if (!res.ok())       \
      return res.err(); \
   res.unwrap();        \
})