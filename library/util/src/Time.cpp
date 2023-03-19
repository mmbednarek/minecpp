#include <chrono>

namespace minecpp::util {

int64_t now()
{
   return std::chrono::duration_cast<std::chrono::seconds>(
                  std::chrono::system_clock::now().time_since_epoch())
           .count();
}

int64_t now_milis()
{
   return std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch())
           .count();
}

}// namespace minecpp::util
