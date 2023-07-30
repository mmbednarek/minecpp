#pragma once
#include "minecpp/math/Vector2.h"
#include "minecpp/math/Vector3.h"
#include "minecpp/nbt/item/Item.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net::play {

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
