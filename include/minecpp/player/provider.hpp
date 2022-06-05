#ifndef MINECPP_PROVIDER_HPP
#define MINECPP_PROVIDER_HPP
#include "player.h"
#include <mb/result.h>

namespace minecpp::player {

class Provider
{
 public:
   virtual ~Provider() noexcept = default;

   virtual mb::result<Player &> get_player(Id id) = 0;
};

}// namespace minecpp::player

#endif//MINECPP_PROVIDER_HPP
