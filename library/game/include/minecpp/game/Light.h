#pragma once

#include "BlockPosition.h"

#include <mb/enum.h>
#include <mb/int.h>
#include <minecpp/proto/common/Common.pb.h>

namespace minecpp::game {

enum class LightTypeValue
{
   Block,
   Sky
};

using LightType_Base = mb::enum_wrapper<LightTypeValue, "block", "sky">;

class LightType final : public LightType_Base
{
 public:
   MB_ENUM_TRAITS(LightType);

   MB_ENUM_FIELD(Block)
   MB_ENUM_FIELD(Sky)

   [[nodiscard]] proto::common::LightType to_proto();

   [[nodiscard]] static LightType from_proto(proto::common::LightType type);
};

struct LightSource
{
   BlockPosition position{};
   mb::u8 strength{};

   LightSource();

   LightSource(const BlockPosition &position, mb::u8 strength);

   [[nodiscard]] proto::common::LightSource to_proto() const;

   [[nodiscard]] static LightSource from_proto(const proto::common::LightSource &source);
};

}// namespace minecpp::game