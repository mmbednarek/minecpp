#include "utils.h"
#include <mineutils/packed.h>

namespace Game {

int calculate_ref_count(int air_id, const long *data, std::size_t size) {
   if (air_id < 0) {
      return 4096;
   }
   int count = 0;
   Utils::for_each_packed(data, size, 4096, [&count, air_id](uint32_t value) {
      if (value == static_cast<uint32_t>(air_id))
         ++count;
   });
   return count;
}

} // namespace Game
