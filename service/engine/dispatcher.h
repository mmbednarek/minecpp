#pragma once
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

class Stream;

class Dispatcher : public minecpp::game::Notifier {
   EventManager &m_events;

 public:
   explicit Dispatcher(EventManager &events);

   void load_terrain(player::Id player_id, const game::ChunkPosition &central_chunk,
                     std::vector<minecpp::game::ChunkPosition> coords) override;
   void transfer_player(player::Id player_id, boost::uuids::uuid target_engine);
   void update_block(minecpp::game::BlockPosition block, mb::u32 state) override;

   void entity_move(player::Id player_id, entity::Id entity_id, const entity::Movement &movement, const entity::Rotation &rotation) override;
   void entity_look(player::Id player_id, mb::u32 entity_id, const entity::Rotation &rotation) override;

   void add_player(player::Id player_id, const std::string &name, mb::u32 ping) override;
   void spawn_player(player::Id player_id, mb::u32 entity_id, minecpp::util::Vec3 position, const entity::Rotation &rotation) override;
   void remove_player(player::Id player_id, mb::u32 entity_id) override;
   void send_chat(chat::MessageType msg_type, const std::string &msg) override;
   void update_block(mb::i32 x, mb::i32 y, mb::i32 z, mb::u32 state) override;
   void animate_hand(player::Id player_id, mb::u32 entity_id, mb::u32 hand) override;
   void unload_chunk(player::Id player_id, const game::ChunkPosition &chunk_position) override;

   void player_list(player::Id player_id, const std::vector<player::Status> &status_list);
   void entity_list(player::Id player_id, const std::vector<game::entity::Entity> &entity_list);

   void accept_player(const player::Player &player_id, const game::entity::Entity &entity);
   void deny_player(const player::Id &player_id, const std::string &reason);
};

}// namespace minecpp::service::engine
