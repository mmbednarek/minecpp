#pragma once
#include "handler.h"
#include "message.h"

namespace Front::Protocol {

class PlayClient {
 public:
   PlayClient(Connection &c);

   void spawn_object(Message::SpawnObject msg);
   void spawn_experience_orb(Message::SpawnExperienceOrb msg);
   void join_game(Message::JoinGame msg);
 private:
   Connection &conn;
};

} // namespace Front::Protocol
