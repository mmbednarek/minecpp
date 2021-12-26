#include "world.h"
#include <minecpp/util/uuid.h>
#include <utility>

namespace minecpp::service::engine {

World::World(uuid engine_id, ChunkService &service, Dispatcher &dispatcher)
    : service(service), dispatcher(dispatcher), engine_id(engine_id) {}

minecpp::game::Notifier &World::notifier() { return dispatcher; }

mb::result<mb::empty> World::add_refs(player::Id player_id, std::vector<game::ChunkPosition> refs) {
   using proto::service::chunk_storage::v1::ReferenceStatus;

   ::grpc::ClientContext ctx;
   proto::service::chunk_storage::v1::AddReferencesRequest req;
   proto::service::chunk_storage::v1::AddReferencesResponse result;

   req.set_player_id(minecpp::util::uuid_to_string(player_id));
   req.set_engine_id(minecpp::util::uuid_to_string(engine_id));
   for (auto const &c : refs) {
      auto new_coord = req.add_coords();
      new_coord->set_x(c.x);
      new_coord->set_z(c.z);
   }
   auto status = service.AddReferences(&ctx, req, &result);
   if (!status.ok()) {
      return mb::error(mb::error::status::Internal, status.error_message());
   }

   if (result.status() == ReferenceStatus::MUST_MOVE) {
      dispatcher.transfer_player(player_id, MB_TRY(minecpp::util::make_uuid(result.target_engine_id())));
   }

   return mb::ok;
}

mb::result<mb::empty> World::free_refs(player::Id player_id, std::vector<game::ChunkPosition> refs) {
   ::grpc::ClientContext ctx;
   proto::service::chunk_storage::v1::RemoveReferencesRequest req;
   proto::service::chunk_storage::v1::EmptyResponse res;

   req.set_player_id(player_id.data, player_id.size());
   for (auto const &c : refs) {
      auto new_coord = req.add_coords();
      new_coord->set_x(c.x);
      new_coord->set_z(c.z);
   }

   auto status = service.RemoveReference(&ctx, req, &res);
   if (!status.ok()) {
      return mb::error(mb::error::status::Internal, status.error_message());
   }

   return mb::ok;
}

mb::result<int> World::height_at(int x, int z) {
   ::grpc::ClientContext ctx;
   proto::service::chunk_storage::v1::HeightAtRequest req;
   proto::service::chunk_storage::v1::HeightAtResponse res;
   req.set_x(x);
   req.set_z(z);
   auto status = service.HeightAt(&ctx, req, &res);
   if (!status.ok()) {
      return mb::error(status.error_message());
   }
   return res.height();
}

mb::result<mb::empty> World::set_block(const game::BlockPosition &pos, game::BlockState state) {
   ::grpc::ClientContext ctx;
   proto::service::chunk_storage::v1::SetBlockRequest req;
   req.set_x(pos.x);
   req.set_y(pos.y);
   req.set_z(pos.z);
   req.set_state(static_cast<int>(state));
   proto::service::chunk_storage::v1::EmptyResponse res;
   auto status = service.SetBlock(&ctx, req, &res);
   if (!status.ok()) {
      return mb::error(status.error_message());
   }
   return mb::ok;
}

} // namespace minecpp::service::engine
