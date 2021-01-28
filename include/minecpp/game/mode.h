#pragma once
#include <cstdint>

namespace minecpp::game {

enum class Mode : uint8_t {
   Survival,
   Creative,
   Adventure,
   Spectator,
   Hardcore,
};

}
