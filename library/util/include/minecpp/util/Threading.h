#pragma once
#ifdef unix
#define _GNU_SOURCE
#include <pthread.h>
#endif

namespace minecpp::util {

inline void label_thread(const char *thread_name)
{
#ifdef unix
   pthread_setname_np(pthread_self(), thread_name);
#endif
}

}// namespace minecpp::util
