#ifndef MINECPP_UTIL_H
#define MINECPP_UTIL_H

#define GETTER(name)                                             \
   [[nodiscard]] constexpr auto name() const->decltype(m_##name) \
   {                                                             \
      return m_##name;                                           \
   }

#endif//MINECPP_UTIL_H
