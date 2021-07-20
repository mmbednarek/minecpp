#include "world.h"
#include <minecpp/util/uuid.h>
#include <utility>

namespace minecpp::service::engine {

World::World(uuid engine_id, const Engine::ChunkService &service, Dispatcher &dispatcher)
    : service(service), dispatcher(dispatcher), engine_id(engine_id) {}

minecpp::game::Notifier &World::notifier() { return dispatcher; }

mb::result<mb::empty> World::add_refs(player::Id, std::vector<ChunkPos> refs) {
   using minecpp::chunk_storage::ReferenceStatus;

   grpc::ClientContext ctx;
   minecpp::chunk_storage::AddReferencesRequest req;
   minecpp::chunk_storage::AddReferencesResponse result;

   req.set_player_id(minecpp::util::uuid_to_string(player));
   req.set_engine_id(minecpp::util::uuid_to_string(engine_id));
   for (auto const &c : refs) {
      auto new_coord = req.add_coords();
      new_coord->set_x(c.x);
      new_coord->set_z(c.z);
   }
   auto status = service->AddReferences(&ctx, req, &result);
   if (!status.ok()) {
      return mb::error(mb::error::status::Internal, status.error_message());
   }

   if (result.status() == ReferenceStatus::MUST_MOVE) {
      dispatcher.transfer_player(player, MB_TRY(minecpp::util::make_uuid(result.target_engine_id())));
   }

   return mb::ok;
}

mb::result<mb::empty> World::free_refs(player::Id, std::vector<ChunkPos> refs) {
   grpc::ClientContext ctx;
   minecpp::chunk_storage::RemoveReferencesRequest req;
   minecpp::chunk_storage::EmptyResponse res;

   req.set_player_id(player.data, player.size());
   for (auto const &c : refs) {
      auto new_coord = req.add_coords();
      new_coord->set_x(c.x);
      new_coord->set_z(c.z);
   }

   auto status = service->RemoveReference(&ctx, req, &res);
   if (!status.ok()) {
      return mb::error(mb::error::status::Internal, status.error_message());
   }

   return mb::ok;
}

mb::result<int> World::height_at(int x, int z) {
   grpc::ClientContext ctx;
   minecpp::chunk_storage::HeightAtRequest req;
   minecpp::chunk_storage::HeightAtResponse res;
   req.set_x(x);
   req.set_z(z);
   auto status = service->HeightAt(&ctx, req, &res);
   if (!status.ok()) {
      return mb::error(status.error_message());
   }
   return res.height();
}

} // namespace minecpp::service::engine
