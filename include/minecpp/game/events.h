#pragma once
#include <minecpp/util/enum.h>

namespace minecpp::game {

using Event =
    minecpp::util::Enum<ENU("AddPlayer"), ENU("SpawnPlayer"), ENU("EntityMove"),
                ENU("EntityLook"), ENU("RemovePlayer"), ENU("UpdateBlock"),
                ENU("Chat"), ENU("AnimateHand"), ENU("LoadTerrain"),
                ENU("TransferPlayer"), ENU("UnloadChunk")>;

} // namespace minecpp::game