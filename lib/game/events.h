#pragma once
#include <mineutils/enum.h>

namespace Game {

using Event = Utils::Enum<ENU("EntityMove"), ENU("EntityLook"),
                          ENU("RemovePlayer"), ENU("UpdateBlock"), ENU("Chat")>;

} // namespace Game