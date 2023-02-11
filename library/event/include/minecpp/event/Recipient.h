#pragma once
#include <minecpp/game/Game.h>
#include <span>

namespace minecpp::event {

enum class RecipientType
{
   All,
   Some,
   Excluding,
};

struct RecipientList
{
   RecipientType type{};
   std::span<game::PlayerId> list{};
};

}// namespace minecpp::event
