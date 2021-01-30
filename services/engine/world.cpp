#include "world.h"
#include <minecpp/util/uuid.h>
#include <utility>

namespace Engine {

World::World(uuid engine_id, const Engine::ChunkService &service, Dispatcher &dispatcher)
    : service(service), dispatcher(dispatcher), engine_id(engine_id) {}

minecpp::game::Notifier &World::notifier() { return dispatcher; }

result<empty> World::add_refs(uuid player, std::vector<ChunkPos> refs) {
   using minecpp::chunk_storage::ReferenceStatus;

   grpc::ClientContext ctx;
   minecpp::chunk_storage::AddReferencesRequest req;
   minecpp::chunk_storage::AddReferencesResponse res;

   req.set_player_id(player.data, player.size());
   for (auto const &c : refs) {
      auto new_coord = req.add_coords();
      new_coord->set_x(c.x);
      new_coord->set_z(c.z);
   }
   auto status = service->AddReferences(&ctx, req, &res);
   if (!status.ok()) {
      return error(errclass::Internal, status.error_message());
   }

   if (res.status() == ReferenceStatus::MUST_MOVE) {
      uuid target_engine{};
      minecpp::util::decode_uuid(target_engine, res.target_engine_id().data());
      dispatcher.transfer_player(player, target_engine);
   }

   return result_ok;
}

result<empty> World::free_refs(uuid player, std::vector<ChunkPos> refs) {
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
      return error(errclass::Internal, status.error_message());
   }

   return result_ok;
}

result<int> World::height_at(int x, int z) {
   grpc::ClientContext ctx;
   minecpp::chunk_storage::HeightAtRequest req;
   minecpp::chunk_storage::HeightAtResponse res;
   req.set_x(x);
   req.set_z(z);
   auto status = service->HeightAt(&ctx, req, &res);
   if (!status.ok()) {
      return error(status.error_message());
   }
   return res.height();
}

} // namespace Engine
