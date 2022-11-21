#pragma once
#include <array>
#include <cassert>
#include <mb/int.h>
#include <memory>
#include <tuple>
#include <vector>

namespace minecpp::world::population {

struct Pos
{
   int x, z;
};

class PopObject
{
 public:
   virtual ~PopObject() noexcept = default;

   virtual int width() const                       = 0;
   virtual int height() const                      = 0;
   virtual int length() const                      = 0;
   virtual Pos center() const                      = 0;
   virtual int block_at(int x, int y, int z) const = 0;
};

class ObjectFactory
{
 public:
   virtual ~ObjectFactory() noexcept = default;

   virtual std::unique_ptr<PopObject> create(unsigned seed) = 0;
   [[nodiscard]] virtual int occurrence() const             = 0;
};

class StaticObjectWrapper final : public PopObject
{
 public:
   explicit StaticObjectWrapper(PopObject *object) :
       m_object(object)
   {
   }

   [[nodiscard]] int width() const override
   {
      return m_object->width();
   }

   [[nodiscard]] int height() const override
   {
      return m_object->height();
   }

   [[nodiscard]] int length() const override
   {
      return m_object->length();
   }

   [[nodiscard]] Pos center() const override
   {
      return m_object->center();
   }

   [[nodiscard]] int block_at(int x, int y, int z) const override
   {
      return m_object->block_at(x, y, z);
   }

 private:
   PopObject *m_object{};
};

class StaticObjectFactory final : public ObjectFactory
{
   std::unique_ptr<PopObject> m_object;
   int m_occurrence{};

 public:
   StaticObjectFactory(int occurrence, std::unique_ptr<PopObject> object) :
       m_object(std::move(object)),
       m_occurrence(occurrence)
   {
   }

   std::unique_ptr<PopObject> create(unsigned int seed) override
   {
      return std::make_unique<StaticObjectWrapper>(m_object.get());
   }

   [[nodiscard]] int occurrence() const override
   {
      return m_occurrence;
   }
};

template<int w, int l, int h>
class ShapedObject final : public PopObject
{
   std::array<int, w * l * h> m_shape;

 public:
   explicit ShapedObject(std::array<int, w * l * h> shape) :
       m_shape(std::move(shape))
   {
   }

   [[nodiscard]] int width() const override
   {
      return w;
   }

   [[nodiscard]] int height() const override
   {
      return h;
   }

   [[nodiscard]] int length() const override
   {
      return l;
   }

   [[nodiscard]] Pos center() const override
   {
      return Pos{.x = w / 2, .z = l / 2};
   };

   [[nodiscard]] int block_at(int x, int y, int z) const override
   {
      assert(x >= 0 && x < w);
      assert(z >= 0 && z < l);
      assert(y >= 0 && y < h);
      return m_shape[x + z * w + y * w * l];
   }
};

class ObjectRepository
{
   static ObjectRepository g_instance;

   std::vector<std::unique_ptr<ObjectFactory>> m_objects;

 public:
   [[nodiscard]] static ObjectRepository &the()
   {
      return g_instance;
   }

   void register_objects();

   mb::size find_object_id(int value);

   [[nodiscard]] std::unique_ptr<PopObject> get_object(mb::size id, unsigned seed) const
   {
      return m_objects[id]->create(seed);
   }
};

}// namespace minecpp::world::population
