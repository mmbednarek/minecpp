#pragma once
#include <cstdint>

template <typename A> concept IndexAssignable = requires(A a, std::size_t i) {
   a[i] = (uint16_t)0;
};

template <typename A> concept Indexable = requires(A a, std::size_t i, int v) {
   v = a[i];
};
