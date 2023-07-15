#pragma once
#include "minecpp/nbt/item/Item.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::play {

class Vector3 {
 public:
   double x{};
   double y{};
   double z{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Vector3 deserialize(::minecpp::network::message::Reader &reader);
};

class Vector3f {
 public:
   float x{};
   float y{};
   float z{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Vector3f deserialize(::minecpp::network::message::Reader &reader);
};

class Vector3s {
 public:
   std::int16_t x{};
   std::int16_t y{};
   std::int16_t z{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Vector3s deserialize(::minecpp::network::message::Reader &reader);
};

class Vector2i {
 public:
   std::int32_t x{};
   std::int32_t y{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Vector2i deserialize(::minecpp::network::message::Reader &reader);
};

class Vector2vi {
 public:
   std::int32_t x{};
   std::int32_t y{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Vector2vi deserialize(::minecpp::network::message::Reader &reader);
};

class Chat {
 public:
   std::string format{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Chat deserialize(::minecpp::network::message::Reader &reader);
};

class Slot {
 public:
   std::int32_t item_id{};
   std::int8_t item_count{};
   nbt::item::SlotData data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Slot deserialize(::minecpp::network::message::Reader &reader);
};

}
