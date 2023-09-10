#pragma once
#include "Id.h"
#include <minecpp/game/IDispatcher.hpp>
#include <minecpp/game/Mode.h>
#include <minecpp/math/Vector3.h>
#include <string_view>

namespace minecpp::game {
class IWorld;

namespace entity {
class Entity;
}
}// namespace minecpp::game

namespace minecpp::nbt::player {
class Player;
}

namespace minecpp::game::player {

using boost::uuids::uuid;

struct Status
{
   Id id;
   std::string name;
   int ping;
   game::Mode mode;
};

class Player
{
   Id m_id;
   EntityId m_entity_id{};
   std::string m_name;
   game::Mode m_game_mode = game::Mode::Survival;
   bool m_is_alive{false};
   int m_ping{};
   bool m_has_loaded_initial_chunks{false};

 public:
   Player(Id id, std::string_view name);

   [[nodiscard]] constexpr Id id() const
   {
      return m_id;
   }

   [[nodiscard]] constexpr EntityId entity_id() const
   {
      return m_entity_id;
   }

   [[nodiscard]] constexpr game::Mode game_mode() const
   {
      return m_game_mode;
   }

   [[nodiscard]] constexpr const std::string &name() const
   {
      return m_name;
   }

   [[nodiscard]] constexpr int ping() const
   {
      return m_ping;
   }

   [[nodiscard]] constexpr bool has_loaded_initial_chunks() const
   {
      return m_has_loaded_initial_chunks;
   }

   void set_has_loaded_initial_chunks(bool has_loaded_initial_chunks)
   {
      m_has_loaded_initial_chunks = has_loaded_initial_chunks;
   }

   constexpr void set_entity_id(EntityId entity_id)
   {
      m_is_alive  = true;
      m_entity_id = entity_id;
   }

   constexpr void set_is_alive(bool is_alive)
   {
      m_is_alive = is_alive;
   }

   [[nodiscard]] constexpr bool is_alive() const
   {
      return m_is_alive;
   }

   constexpr void set_ping(int ping)
   {
      m_ping = ping;
   }

   [[nodiscard]] inline Status status() const
   {
      return Status{
              .id   = m_id,
              .name = m_name,
              .ping = m_ping,
              .mode = m_game_mode,
      };
   }

   static Player from_nbt(const nbt::player::Player &player, std::string_view name);
};

}// namespace minecpp::game::player