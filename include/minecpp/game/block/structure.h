#pragma once
#include <minecpp/util/enum.h>

namespace Game::Block {

using StructureMode =
    Utils::Enum<ENU("save"), ENU("load"), ENU("corner"), ENU("data")>;

}
