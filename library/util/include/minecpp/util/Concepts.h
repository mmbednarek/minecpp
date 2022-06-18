#pragma once
#include <cstdint>

template<typename A>
concept IndexAssignable = requires(A a, std::size_t i)
{
   a[i] = (uint16_t) 0;
};
