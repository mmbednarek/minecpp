#pragma once
#include <mineutils/enum.h>

namespace Game::Block {

using NoteBlockInstrument =
    Utils::Enum<ENU("harp"), ENU("basedrum"), ENU("snare"), ENU("hat"),
                ENU("bass"), ENU("flute"), ENU("bell"), ENU("guitar"),
                ENU("chime"), ENU("xylophone"), ENU("iron_xylophone"),
                ENU("cow_bell"), ENU("didgeridoo"), ENU("bit"), ENU("banjo"),
                ENU("pling")>;

}