#pragma once
#include "Id.h"
#include <mb/result.h>

namespace minecpp::game::player {

class Player;

class Provider
{
 public:
   virtual ~Provider() noexcept = default;

   virtual mb::result<Player &> get_player(Id id) = 0;
};

}// namespace minecpp::game::player
