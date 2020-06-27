#pragma once
#include <optional>

template <typename T> class Result {
   std::optional<T> result;
   std::string message;

   Result() = default;

 public:
   explicit Result(T value);
   Result(const Result &other);

   Result &operator=(T value);
   T unwrap();
   bool ok();
   const std::string &msg();

   static Result error(std::string message);
};

template <typename T> Result<T>::Result(T value) : result(std::move(result)) {}

template <typename T> Result<T>::Result(const Result &other) {
   if (other.ok()) {
      result = other.result;
      return;
   }
   message = other.message;
}

template <typename T> Result<T> &Result<T>::operator=(T value) {
   result = std::move(value);
   message.clear();
   return *this;
}

template <typename T> T Result<T>::unwrap() {
   if (!message.empty()) {
      throw std::runtime_error(message);
   }
   return std::move(result.value());
}
template <typename T> Result<T> Result<T>::error(std::string message) {
   auto r = Result<T>();
   r.message = std::move(message);
   return r;
}

template <typename T> bool Result<T>::ok() { return message.empty(); }

template <typename T> const std::string &Result<T>::msg() { return message; }
