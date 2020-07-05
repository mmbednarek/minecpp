#pragma once
#include <mineutils/enum.h>

namespace Game {

using Event =
    Utils::Enum<ENU("AddPlayer"), ENU("SpawnPlayer"), ENU("EntityMove"),
                ENU("EntityLook"), ENU("RemovePlayer"), ENU("UpdateBlock"),
                ENU("Chat"), ENU("AnimateHand"), ENU("LoadTerrain"),
                ENU("TransferPlayer")>;

} // namespace Game