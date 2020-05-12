#pragma once
#include "handler.h"
#include "message.h"
#include <game/mode.h>

namespace Front::Protocol {

class PlayClient {
 public:
   PlayClient(Connection &c);

   void spawn_object(Message::SpawnObject msg);
   void spawn_experience_orb(Message::SpawnExperienceOrb msg);
   void difficulty(uint8_t diff, bool locked);
   void server_brand(std::string_view brand);
   void join_game(Message::JoinGame msg);
   void player_abilities(Message::PlayerAbilities msg);
   void held_item(uint8_t pos);
 private:
   Connection &conn;
};

} // namespace Front::Protocol
