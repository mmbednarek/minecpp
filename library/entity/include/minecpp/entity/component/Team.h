#pragma once
#include <atomic>
#include <minecpp/game/IDispatcher.hpp>
#include <minecpp/game/Team.h>

namespace minecpp::entity::component {

class Team
{
 public:
   explicit Team(game::Team team);

   void send_team_equipment(game::IDispatcher &dispatcher, game::PlayerId player_id);

   void increment_used_apples();
   void increment_used_arrows();

   [[nodiscard]] int used_apple_count() const;
   [[nodiscard]] int used_arrow_count() const;

   void reset_counters();

   [[nodiscard]] game::Team team() const;

 private:
   game::Team m_team;
   std::atomic_int m_used_apple_count = 0;
   std::atomic_int m_used_arrow_count = 0;
};

}// namespace minecpp::entity::component