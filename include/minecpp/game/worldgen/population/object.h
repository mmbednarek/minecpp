#pragma once
#include <array>
#include <cassert>
#include <tuple>

namespace Game::WorldGen::Population {

struct Pos {
   int x, z;
};

class PopObject {
 public:
   virtual int width() const = 0;
   virtual int height() const = 0;
   virtual int length() const = 0;
   virtual int occurrence() const = 0;
   virtual Pos center() const = 0;
   virtual int block_at(int x, int y, int z) const = 0;
};

template<int w, int l, int h>
class ShapedObject : public PopObject {
   int occurr;
   std::array<int, w * l * h> shape;

 public:
   ShapedObject(int occ, std::array<int, w * l * h> shape) : occurr(occ), shape(std::move(shape)) {}

   [[nodiscard]] int width() const override {
      return w;
   }
   [[nodiscard]] int height() const override {
      return h;
   }
   [[nodiscard]] int length() const override {
      return l;
   }
   [[nodiscard]] int occurrence() const override {
       return occurr;
   };
   [[nodiscard]] Pos center() const override {
           return Pos{.x = w / 2, .z = l / 2};
   };
   [[nodiscard]] int block_at(int x, int y, int z) const override {
      assert(x >= 0 && x < w);
      assert(z >= 0 && z < l);
      assert(y >= 0 && y < h);
      return shape[x + z * w + y * w * l];
   }
};

extern std::array<const PopObject *, 7> pop_objects;

int find_object_id(int value);

}// namespace Game::WorldGen
