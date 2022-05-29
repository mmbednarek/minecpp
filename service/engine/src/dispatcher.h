#pragma once
#include "api.h"
#include "event_manager.h"
#include <minecpp/chat/chat.h>
#include <minecpp/game/entity/entity.h>
#include <minecpp/game/notifier.h>
#include <minecpp/player/id.h>
#include <minecpp/player/player.h>

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

   void load_terrain(player::Id player_id, const game::ChunkPosition &central_chunk,
                     std::vector<minecpp::game::ChunkPosition> coords) override;
   void transfer_player(player::Id player_id, boost::uuids::uuid target_engine);
   void update_block(game::BlockPosition block, game::BlockState state) override;

   void entity_move(player::Id player_id, entity::Id entity_id, const entity::Movement &movement,
                    const entity::Rotation &rotation) override;
   void entity_look(player::Id player_id, mb::u32 entity_id, const entity::Rotation &rotation) override;

   void add_player(player::Id player_id, const std::string &name, mb::u32 ping) override;
   void spawn_player(player::Id player_id, mb::u32 entity_id, minecpp::util::Vec3 position,
                     const entity::Rotation &rotation) override;
   void remove_player(player::Id player_id, mb::u32 entity_id) override;
   void send_chat(chat::MessageType msg_type, const std::string &msg) override;
   void acknowledge_player_digging(player::Id player_id, game::BlockPosition &pos,
                                   game::BlockState block_state, game::PlayerDiggingState state,
                                   bool successful) override;
   void animate_hand(player::Id player_id, mb::u32 entity_id, mb::u32 hand) override;
   void unload_chunk(player::Id player_id, const game::ChunkPosition &chunk_position) override;

   void player_list(player::Id player_id, const std::vector<player::Status> &status_list);
   void entity_list(player::Id player_id, const std::vector<game::entity::Entity> &entity_list);

   void accept_player(const player::Player &player_id, const game::entity::Entity &entity);
   void deny_player(const player::Id &player_id, const std::string &reason);

   void set_inventory_slot(player::Id player_id, game::item::ItemId item_id, player::SlotId slot_id,
                           std::size_t count) override;
};

}// namespace minecpp::service::engine
