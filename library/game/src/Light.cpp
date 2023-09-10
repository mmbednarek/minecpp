#include <minecpp/game/Light.h>

namespace minecpp::game {

LightSource::LightSource() = default;

LightSource::LightSource(const BlockPosition &position, mb::u8 strength) :
    position(position),
    strength(strength)
{
}

}// namespace minecpp::game
