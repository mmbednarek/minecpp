#pragma once
#include "Api.h"
#include "EventManager.h"
#include <minecpp/chat/Chat.h>
#include <minecpp/game/entity/Entity.h>
#include <minecpp/game/Notifier.h>
#include <minecpp/game/player/Id.h>
#include <minecpp/game/player/Player.h>

namespace minecpp::player {
class Player;
}

namespace minecpp::service::engine {

using boost::uuids::uuid;

class Dispatcher : public minecpp::game::Notifier
{
   EventManager<BidiStream> &m_events;

 public:
   explicit Dispatcher(EventManager<BidiStream> &events);

   void load_terrain(game::PlayerId player_id, const game::ChunkPosition &central_chunk,
                     std::vector<minecpp::game::ChunkPosition> coords) override;
   void transfer_player(game::PlayerId player_id, boost::uuids::uuid target_engine);
   void update_block(game::BlockPosition block, game::BlockStateId state) override;

   void entity_move(game::PlayerId player_id, game::EntityId entity_id,
                    const game::entity::Movement &movement, const game::entity::Rotation &rotation) override;
   void entity_look(game::PlayerId player_id, mb::u32 entity_id,
                    const game::entity::Rotation &rotation) override;

   void add_player(game::PlayerId player_id, const std::string &name, mb::u32 ping) override;
   void spawn_player(game::PlayerId player_id, mb::u32 entity_id, minecpp::util::Vec3 position,
                     const game::entity::Rotation &rotation) override;
   void remove_player(game::PlayerId player_id, mb::u32 entity_id) override;
   void send_chat(chat::MessageType msg_type, const std::string &msg) override;
   void acknowledge_block_change(game::PlayerId player_id, int sequence_id) override;
   void animate_hand(game::PlayerId player_id, mb::u32 entity_id, mb::u32 hand) override;
   void unload_chunk(game::PlayerId player_id, const game::ChunkPosition &chunk_position) override;

   void player_list(game::PlayerId player_id, const std::vector<game::player::Status> &status_list);
   void entity_list(game::PlayerId player_id, const std::vector<game::entity::Entity> &entity_list);

   void accept_player(const game::player::Player &player_id, const game::entity::Entity &entity);
   void deny_player(const game::PlayerId &player_id, const std::string &reason);

   void set_inventory_slot(game::PlayerId player_id, game::ItemId item_id, game::SlotId slot_id,
                           std::size_t count) override;
   void update_block_light(game::ISectionSlice &slice, game::SectionRange range) override;
};

}// namespace minecpp::service::engine
