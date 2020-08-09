#pragma once
#include "server.h"
#include <minepb/engine.pb.h>
#include <minepb/events.pb.h>
#include <minepb/chunk_storage.grpc.pb.h>
#include <string>
#include <vector>

namespace Front {

using namespace minecpp::events;

class EventHandler {
   Server &server;

 public:
   explicit EventHandler(Server &server);

   void accept_event(const minecpp::engine::Event &e);

   void on_event(AddPlayer &msg);
   void on_event(SpawnPlayer &pos);
   void on_event(EntityMove &pos);
   void on_event(EntityLook &pos);
   void on_event(Chat &pos);
   void on_event(RemovePlayer &pos);
   void on_event(UpdateBlock &msg);
   void on_event(AnimateHand &msg);
   void on_event(LoadTerrain &msg);
   void on_event(TransferPlayer &msg);
   void on_event(UpdatePlayerAbilities &msg);
};

} // namespace Front
