#include "World.h"
#include <minecpp/util/Uuid.h>
#include <utility>

using minecpp::game::Face;

namespace minecpp::service::engine {

World::World(uuid engine_id, ChunkService &service, Dispatcher &dispatcher, PlayerManager &player_manager,
             EntityManager &entity_manager, controller::BlockManager &block_controller) :
    service(service),
    m_dispatcher(dispatcher),
    m_player_manager(player_manager),
    m_entity_manager(entity_manager),
    m_block_controller(block_controller),
    engine_id(engine_id)
{
}

minecpp::game::Notifier &World::notifier()
{
   return m_dispatcher;
}

mb::result<mb::empty> World::add_refs(game::PlayerId player_id, std::vector<game::ChunkPosition> refs)
{
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
      return mb::error(status.error_message());
   }

   if (result.status() == ReferenceStatus::MUST_MOVE) {
      m_dispatcher.transfer_player(player_id, MB_TRY(minecpp::util::make_uuid(result.target_engine_id())));
   }

   return mb::ok;
}

mb::result<mb::empty> World::free_refs(game::PlayerId player_id, std::vector<game::ChunkPosition> refs)
{
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
      return mb::error(status.error_message());
   }

   return mb::ok;
}

mb::result<int> World::height_at(int x, int z)
{
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

mb::result<mb::empty> World::set_block_no_notify(const game::BlockPosition &pos, game::BlockStateId state)
{
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

   m_dispatcher.update_block(pos, state);

   return mb::ok;
}

mb::result<mb::empty> World::set_block(const game::BlockPosition &pos, game::BlockStateId state)
{
   if (auto res = set_block_no_notify(pos, state); res.has_failed()) {
      return std::move(res.err());
   }

   notify_neighbours(pos, state);
   return mb::ok;
}

mb::result<game::BlockStateId> World::get_block(const game::BlockPosition &pos)
{
   ::grpc::ClientContext ctx;

   auto proto_pos = pos.to_proto();

   proto::common::v1::BlockState state;
   auto status = service.GetBlock(&ctx, proto_pos, &state);
   if (!status.ok()) {
      return mb::error(status.error_message());
   }

   return game::block_state_from_proto(state);
}

game::player::Provider &World::players()
{
   return m_player_manager;
}

EntityManager &World::entities()
{
   return m_entity_manager;
}

void World::notify_neighbours(game::BlockPosition position, game::BlockStateId state)
{
   for (auto face : game::g_faces) {
      auto neighbour_pos = position.neighbour_at(face);

      auto old_neighbour_state = get_block(neighbour_pos);
      if (old_neighbour_state.has_failed())
         continue;

      auto new_neighbour_state = m_block_controller.on_neighbour_change(
              *this, *old_neighbour_state, state, neighbour_pos, game::opposite_face(face));
      if (not new_neighbour_state.has_value())
         continue;

      if (*new_neighbour_state != *old_neighbour_state) {
         set_block_no_notify(neighbour_pos, *new_neighbour_state);
      }
   }
}

mb::result<game::LightLevel> World::get_light(game::LightType light_type, const game::BlockPosition &pos)
{
   proto::service::chunk_storage::v1::GetLightLevelRequest req{};
   req.set_light_type(static_cast<proto::common::v1::LightType>(light_type));
   *req.mutable_position() = pos.to_proto();

   proto::common::v1::LightLevel level;

   ::grpc::ClientContext ctx;
   auto status = service.GetLightLevel(&ctx, req, &level);
   if (!status.ok()) {
      return mb::error(status.error_message());
   }

   return level.level();
}

mb::emptyres World::set_light(game::LightType light_type, const game::BlockPosition &pos,
                              game::LightLevel level)
{
   proto::service::chunk_storage::v1::SetLightLevelRequest req{};
   req.set_light_type(static_cast<proto::common::v1::LightType>(light_type));
   req.mutable_level()->set_level(static_cast<mb::u32>(level));
   *req.mutable_position() = pos.to_proto();

   proto::service::chunk_storage::v1::EmptyResponse resp{};
   ::grpc::ClientContext ctx;
   auto status = service.SetLightLevel(&ctx, req, &resp);
   if (!status.ok()) {
      return mb::error(status.error_message());
   }

   return mb::ok;
}

mb::emptyres World::recalculate_light(game::LightType light_type, const game::BlockPosition &pos)
{
   auto original_light_value = MB_TRY(get_light(light_type, pos));

   std::array<game::LightLevel, 6> neighbour_light_levels{
           MB_TRY(get_light(light_type, pos.neighbour_at(Face::Bottom))),
           MB_TRY(get_light(light_type, pos.neighbour_at(Face::Top))),
           MB_TRY(get_light(light_type, pos.neighbour_at(Face::North))),
           MB_TRY(get_light(light_type, pos.neighbour_at(Face::South))),
           MB_TRY(get_light(light_type, pos.neighbour_at(Face::West))),
           MB_TRY(get_light(light_type, pos.neighbour_at(Face::East))),
   };

   auto max_neighbour = std::max_element(neighbour_light_levels.begin(), neighbour_light_levels.end());
   auto projected_light_level = *max_neighbour - 1;

   if (projected_light_level <= original_light_value) {
      return mb::ok;
   }

   set_light(light_type, pos, static_cast<game::LightLevel>(projected_light_level));

   for (unsigned face_id{0}; face_id < 6; ++face_id) {
      if ((projected_light_level - 1) <= neighbour_light_levels[face_id])
         continue;

      recalculate_light(light_type, pos.neighbour_at(static_cast<Face>(face_id)));
   }

   return mb::ok;
}

}// namespace minecpp::service::engine
