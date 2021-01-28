#pragma once
#include <minecpp/mineutils/enum.h>

namespace Game::Block {

using StructureMode =
    Utils::Enum<ENU("save"), ENU("load"), ENU("corner"), ENU("data")>;

}
