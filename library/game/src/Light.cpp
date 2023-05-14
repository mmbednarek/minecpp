#include <minecpp/game/Light.h>

namespace minecpp::game {

namespace pb_common = minecpp::proto::common::v1;

LightType LightType::from_proto(const pb_common::LightType type)
{
   return LightType{static_cast<LightTypeValue>(type)};
}

pb_common::LightType LightType::to_proto()
{
   return static_cast<pb_common::LightType>(index());
}

LightSource::LightSource() = default;

LightSource::LightSource(const BlockPosition &position, mb::u8 strength) :
    position(position),
    strength(strength)
{
}

LightSource LightSource::from_proto(const pb_common::LightSource &source)
{
   return {
           BlockPosition::from_proto(source.position()),
           static_cast<mb::u8>(source.strength()),
   };
}

pb_common::LightSource LightSource::to_proto() const
{
   pb_common::LightSource result;
   *result.mutable_position() = position.to_proto();
   result.set_strength(strength);
   return result;
}

}// namespace minecpp::game
