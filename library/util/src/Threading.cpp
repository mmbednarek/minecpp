#include "Threading.h"

#ifdef unix
#include <pthread.h>
#endif

namespace minecpp::util {

std::array<const char *, 32> g_thread_names{
        "TickThread",
        "WorkerThread_0",
        "WorkerThread_1",
        "WorkerThread_2",
        "WorkerThread_3",
        "WorkerThread_4",
        "WorkerThread_5",
        "WorkerThread_6",
        "WorkerThread_7",
        "WorkerThread_8",
        "WorkerThread_9",
        "WorkerThread_10",
        "WorkerThread_11",
        "WorkerThread_12",
        "WorkerThread_13",
        "WorkerThread_14",
        "WorkerThread_15",
        "WorkerThread_16",
        "WorkerThread_17",
        "WorkerThread_18",
        "WorkerThread_19",
        "WorkerThread_20",
        "WorkerThread_21",
        "WorkerThread_22",
        "WorkerThread_23",
        "WorkerThread_24",
        "WorkerThread_25",
        "WorkerThread_26",
        "WorkerThread_27",
        "WorkerThread_28",
        "WorkerThread_29",
        "WorkerThread_30"
};

std::array<std::pair<std::size_t, std::size_t>, 2> g_thread_names_indices{
        std::pair{0, 1},
        std::pair{1, 31}
};

std::array<const char *, 2> g_thread_excess_names{
        "TickThread",
        "WorkingThread"
};

namespace {

static void label_thread(const char *thread_name)
{
#ifdef unix
   pthread_setname_np(pthread_self(), thread_name);
#endif
}

}

void set_debug_thread_info(ThreadType type, std::size_t index)
{
   auto [start_index, count] = g_thread_names_indices[static_cast<std::size_t>(type)];
   if (index >= count) {
      label_thread(g_thread_excess_names[static_cast<std::size_t>(type)]);
      return;
   }

   label_thread(g_thread_names[start_index + index]);
}

}
