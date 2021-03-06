#pragma once
#include <minecpp/util/enum.h>

namespace minecpp::game::block {

using NoteBlockInstrument =
    minecpp::util::Enum<ENU("harp"), ENU("basedrum"), ENU("snare"), ENU("hat"),
                ENU("bass"), ENU("flute"), ENU("bell"), ENU("guitar"),
                ENU("chime"), ENU("xylophone"), ENU("iron_xylophone"),
                ENU("cow_bell"), ENU("didgeridoo"), ENU("bit"), ENU("banjo"),
                ENU("pling")>;

}