#pragma once
#include <cstdint>
#include <minepb/game.pb.h>

namespace Game {

enum class Dimension : int8_t { Overworld = 0, Nether = -1, End = 1 };

minecpp::game::DimensionType dimension_to_proto(Dimension d);

}