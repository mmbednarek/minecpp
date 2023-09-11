#pragma once

#include "Server.h"

#include "minecpp/game/player/Id.h"
#include "minecpp/nbt/repository/Registry.schema.h"
#include "minecpp/service/engine/Api.h"

#include <string>
#include <vector>

namespace minecpp::service::front {

struct RawMsg
{
   container::BufferView message;

   void serialize(network::message::Writer &writer) const;
};

class EventHandler : public engine::IVisitor
{
 public:
   explicit EventHandler(Server &server);

   void set_client(engine::Client *client);

   void on_send_msg_to_single_player(engine::Client &client,
                                     const net::engine::cb::SendMsgToSinglePlayer &msg) override;
   void on_send_msg_to_some_players(engine::Client &client,
                                    const net::engine::cb::SendMsgToSomePlayers &msg) override;
   void on_send_msg_to_all_players(engine::Client &client,
                                   const net::engine::cb::SendMsgToAllPlayers &msg) override;
   void on_send_msg_to_all_players_except(engine::Client &client,
                                          const net::engine::cb::SendMsgToAllPlayersExcept &msg) override;
   void on_failure(engine::Client &client, std::uint8_t message_id) override;

 private:
   Server &m_server;
   engine::Client *m_client{};
   std::unique_ptr<std::future<bool>> m_player_list{};
};

}// namespace minecpp::service::front
