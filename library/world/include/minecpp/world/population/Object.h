#pragma once
#include <array>
#include <cassert>
#include <mb/int.h>
#include <memory>
#include <minecpp/math/Vector2.h>
#include <minecpp/math/Vector3.h>
#include <tuple>
#include <vector>

namespace minecpp::world::population {

class PopObject
{
 public:
   virtual ~PopObject() noexcept = default;

   [[nodiscard]] virtual math::Vector3i extent() const                                  = 0;
   [[nodiscard]] virtual math::Vector2i center() const                                  = 0;
   [[nodiscard]] virtual game::BlockStateId block(const math::Vector3i &position) const = 0;
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

   [[nodiscard]] math::Vector3i extent() const override
   {
      assert(m_object);
      return m_object->extent();
   }

   [[nodiscard]] math::Vector2i center() const override
   {
      assert(m_object);
      return m_object->center();
   }

   [[nodiscard]] game::BlockStateId block(const math::Vector3i &position) const override
   {
      assert(m_object);
      return m_object->block(position);
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

   std::unique_ptr<PopObject> create(unsigned int /*seed*/) override
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
   std::array<game::BlockStateId, w * l * h> m_shape;

 public:
   explicit ShapedObject(std::array<game::BlockStateId, w * l * h> shape) :
       m_shape(std::move(shape))
   {
   }

   [[nodiscard]] math::Vector3i extent() const override
   {
      return {w, h, l};
   }

   [[nodiscard]] math::Vector2i center() const override
   {
      return extent().flat() / 2;
   }

   [[nodiscard]] game::BlockStateId block(const math::Vector3i &position) const override
   {
      assert(position.x() >= 0 && position.x() < w);
      assert(position.y() >= 0 && position.y() < h);
      assert(position.z() >= 0 && position.z() < l);
      const auto offset = position.x() + position.z() * w + position.y() * w * l;
      return m_shape[static_cast<std::size_t>(offset)];
   }
};

class ObjectRepository
{
   static ObjectRepository s_instance;

   std::vector<std::unique_ptr<ObjectFactory>> m_objects;

 public:
   [[nodiscard]] static ObjectRepository &the()
   {
      return s_instance;
   }

   void register_objects();

   std::optional<std::size_t> find_object_id(int value);

   [[nodiscard]] std::unique_ptr<PopObject> get_object(mb::size id, unsigned seed) const
   {
      return m_objects[id]->create(seed);
   }
};

}// namespace minecpp::world::population
