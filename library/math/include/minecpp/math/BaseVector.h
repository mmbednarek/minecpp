#pragma once
#include <algorithm>
#include <functional>
#include <numeric>

namespace minecpp::math {

template<typename TValue, int CCount>
   requires std::floating_point<TValue> || std::integral<TValue>
class BaseVector
{};

}// namespace minecpp::math

#define MCC_MATH_DEFINE_INDEX_GETTER_SETTER(name, index)   \
   [[nodiscard]] constexpr ValueType name() const noexcept \
   {                                                       \
      return m_storage[index];                             \
   }                                                       \
   constexpr void set_##name(ValueType value) noexcept     \
   {                                                       \
      m_storage[index] = value;                            \
   }

#define MCC_MATH_DECLARE_VEC_BINARY_OP(op, op_cb)                                             \
   [[nodiscard]] constexpr SelfType operator op(const SelfType &other) const                  \
   {                                                                                          \
      SelfType output{};                                                                      \
      std::transform(m_storage, m_storage + Count, other.m_storage, output.m_storage, op_cb); \
      return output;                                                                          \
   }

#define MCC_MATH_DECLARE_VEC_ASSIGN_BINARY_OP(op, op_cb)                               \
   constexpr SelfType &operator op(const SelfType &other)                              \
   {                                                                                   \
      std::transform(m_storage, m_storage + Count, other.m_storage, m_storage, op_cb); \
      return *this;                                                                    \
   }

#define MCC_MATH_DECLARE_VEC_TRANSFORM_FUNCTION(method_name, func_name) \
   [[nodiscard]] constexpr SelfType method_name() const                 \
   {                                                                    \
      SelfType result{};                                                \
      std::transform(m_storage, m_storage + Count, result.m_storage,    \
                     [](ValueType value) { return func_name(value); }); \
      return result;                                                    \
   }

#define MCC_MATH_DECLARE_UNIT_BINARY_OP(op)                          \
   [[nodiscard]] SelfType operator op(ValueType rhs) const           \
   {                                                                 \
      SelfType result{};                                             \
      std::transform(m_storage, m_storage + Count, result.m_storage, \
                     [rhs](ValueType lhs) { return lhs op rhs; });   \
      return result;                                                 \
   }

#define MCC_MATH_DECLARE_UNIT_ASSIGN_BINARY_OP(op)                                                          \
   SelfType &operator op(ValueType rhs)                                                                     \
   {                                                                                                        \
      std::transform(m_storage, m_storage + Count, m_storage, [rhs](ValueType lhs) { return lhs op rhs; }); \
      return *this;                                                                                         \
   }

#define MCC_MATH_DECLARE_EQUAL_OP                                                                       \
   [[nodiscard]] bool operator==(const SelfType &other) const                                           \
   {                                                                                                    \
      return std::equal(m_storage, m_storage + Count, other.m_storage);                                 \
   }                                                                                                    \
   [[nodiscard]] bool operator!=(const SelfType &other) const                                           \
   {                                                                                                    \
      return std::equal(m_storage, m_storage + Count, other.m_storage, std::not_equal_to<ValueType>{}); \
   }

#define MCC_MATH_DECLARE_TRANSFORM_FUNC                                         \
   template<typename TCallback>                                                 \
   [[nodiscard]] SelfType transform(TCallback callback) const                   \
   {                                                                            \
      SelfType result;                                                          \
      std::transform(m_storage, m_storage + Count, result.m_storage, callback); \
      return result;                                                            \
   }

#define MCC_MATH_DECLARE_ACCUMULATE_METHOD                               \
   [[nodiscard]] ValueType sum() const                                   \
   {                                                                     \
      return std::accumulate(m_storage, m_storage + Count, ValueType{}); \
   }

#define MCC_MATH_DEFINE_VECTOR_TRAITS(count)                               \
   using ValueType             = TValue;                                   \
   using SelfType              = BaseVector<ValueType, count>;             \
   static constexpr auto Count = count;                                    \
   ValueType m_storage[Count];                                             \
   MCC_MATH_DECLARE_VEC_BINARY_OP(+, std::plus<ValueType>{})               \
   MCC_MATH_DECLARE_VEC_BINARY_OP(-, std::minus<ValueType>{})              \
   MCC_MATH_DECLARE_VEC_BINARY_OP(*, std::multiplies<ValueType>{})         \
   MCC_MATH_DECLARE_VEC_BINARY_OP(/, std::divides<ValueType>{})            \
   MCC_MATH_DECLARE_VEC_ASSIGN_BINARY_OP(+=, std::plus<ValueType>{})       \
   MCC_MATH_DECLARE_VEC_ASSIGN_BINARY_OP(-=, std::minus<ValueType>{})      \
   MCC_MATH_DECLARE_VEC_ASSIGN_BINARY_OP(*=, std::multiplies<ValueType>{}) \
   MCC_MATH_DECLARE_VEC_ASSIGN_BINARY_OP(/=, std::divides<ValueType>{})    \
   MCC_MATH_DECLARE_UNIT_BINARY_OP(+)                                      \
   MCC_MATH_DECLARE_UNIT_BINARY_OP(-)                                      \
   MCC_MATH_DECLARE_UNIT_BINARY_OP(*)                                      \
   MCC_MATH_DECLARE_UNIT_BINARY_OP(/)                                      \
   MCC_MATH_DECLARE_UNIT_ASSIGN_BINARY_OP(+=)                              \
   MCC_MATH_DECLARE_UNIT_ASSIGN_BINARY_OP(-=)                              \
   MCC_MATH_DECLARE_UNIT_ASSIGN_BINARY_OP(*=)                              \
   MCC_MATH_DECLARE_UNIT_ASSIGN_BINARY_OP(/=)                              \
   MCC_MATH_DECLARE_EQUAL_OP                                               \
   MCC_MATH_DECLARE_VEC_TRANSFORM_FUNCTION(floor, ::std::floor)            \
   MCC_MATH_DECLARE_VEC_TRANSFORM_FUNCTION(ceil, ::std::ceil)              \
   MCC_MATH_DECLARE_ACCUMULATE_METHOD                                      \
   MCC_MATH_DECLARE_TRANSFORM_FUNC
