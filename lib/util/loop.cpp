#include <minecpp/util/loop.h>

namespace Utils {

void around(int x, int y, std::function<void(int, int)> f) {
   for (int oy = -1; oy < 2; oy += 2) {
      for (int ox = -1; ox < 2; ox += 2) {
         f(x + ox, y + oy);
      }
   }
   for (int ox = -1; ox < 2; ox += 2) {
      f(x + ox, y);
   }
   for (int oy = -1; oy < 2; oy += 2) {
      f(x, y + oy);
   }
}

}// namespace Utils