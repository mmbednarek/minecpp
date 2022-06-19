#include <minecpp/event/Clientbound.h>
#include <minecpp/event/Serverbound.h>

namespace minecpp::event {

std::vector<game::PlayerId> read_recipients(const clientbound_v1::Event &event)
{
   switch (event.recipient_case()) {
   case proto::event::clientbound::v1::Event::kSinglePlayer:
      return std::vector<game::PlayerId>{game::player::read_id_from_proto(event.single_player().player_id())};
   case proto::event::clientbound::v1::Event::kMultiplePlayers: {
      std::vector<game::PlayerId> result(event.multiple_players().player_ids_size());
      auto &player_ids = event.multiple_players().player_ids();
      std::transform(
              player_ids.begin(), player_ids.end(), result.begin(),
              [](const proto::player::v1::PlayerId &id) { return game::player::read_id_from_proto(id); });
      return result;
   }
   case proto::event::clientbound::v1::Event::kAllPlayers:
      return std::vector<game::PlayerId>();// empty signifies all players.
   case proto::event::clientbound::v1::Event::kExcluding:
      // TODO: Implement excluding
      return std::vector<game::PlayerId>();// empty signifies all players.
   }
   return std::vector<game::PlayerId>();
}
}// namespace minecpp::event
