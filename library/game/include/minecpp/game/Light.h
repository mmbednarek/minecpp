#pragma once

#include "BlockPosition.h"

#include <mb/enum.h>
#include <mb/int.h>
#include <minecpp/proto/common/v1/Common.pb.h>

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

   [[nodiscard]] proto::common::v1::LightType to_proto();

   [[nodiscard]] static LightType from_proto(proto::common::v1::LightType type);
};

struct LightSource
{
   BlockPosition position{};
   mb::u8 strength{};

   LightSource();

   LightSource(const BlockPosition &position, mb::u8 strength);

   [[nodiscard]] proto::common::v1::LightSource to_proto() const;

   [[nodiscard]] static LightSource from_proto(const proto::common::v1::LightSource &source);
};

}// namespace minecpp::game