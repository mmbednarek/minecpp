#pragma once
#include <cstdint>

namespace Game {

enum class Mode : uint8_t {
   Survival,
   Creative,
   Adventure,
   Spectator,
   Hardcore,
};

}
