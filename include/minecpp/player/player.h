#pragma once
#include "id.h"
#include "inventory.h"
#include "tracking.h"
#include <minecpp/entity/entity.h>
#include <minecpp/game/mode.h>
#include <minecpp/proto/player/v1/player.pb.h>
#include <minecpp/util/vec.h>
#include <string_view>

namespace minecpp::game {
class World;

namespace entity {
class Entity;
}
}// namespace minecpp::game

namespace minecpp::nbt::player::v1 {
class Player;
}

namespace minecpp::player {

using boost::uuids::uuid;

struct Abilities
{
   float fly_speed    = 0.05f;
   bool flying        = false;
   bool instant_build = true;
   bool invulnerable  = false;
   bool may_build     = true;
   bool may_fly       = true;
   float walk_speed   = 0.1f;

   static Abilities from_proto(const minecpp::proto::player::v1::Abilities &abilities);

   [[nodiscard]] minecpp::proto::player::v1::Abilities to_proto() const;

   [[nodiscard]] constexpr mb::u32 flags() const
   {
      return (invulnerable ? 1u : 0u) | (flying ? 2u : 0u) | (may_fly ? 4u : 0u) | (instant_build ? 8u : 0u);
   }
};

struct Status
{
   Id id;
   std::string name;
   int ping;
   game::Mode mode;

   [[nodiscard]] inline proto::player::v1::Status to_proto() const
   {
      proto::player::v1::Status status;
      *status.mutable_id() = write_id_to_proto(id);
      status.set_name(name);
      status.set_ping(ping);
      status.set_game_mode(game::write_mode_to_proto(mode));
      return status;
   }
};

class Player
{
   Id m_id;
   entity::Id m_entity_id{};
   std::string m_name;
   game::Mode m_game_mode = game::Mode::Survival;
   std::unique_ptr<Tracking> m_tracking;

   int m_ping{};

   int m_xp_level    = 0;
   float m_xp_points = .0f;
   int m_xp_seed     = 0;
   int m_xp_total    = 0;

   int m_food_level              = 20;
   float m_food_exhaustion_level = 0.16f;
   float m_food_saturation_level = 5.0f;
   int m_food_tick_timer         = 0;

   Abilities m_abilities;
   Inventory m_inventory;

 public:
   Player(Id id, std::string_view name, const util::Vec3 &pos);

   [[nodiscard]] constexpr Id id() const
   {
      return m_id;
   }

   [[nodiscard]] constexpr entity::Id entity_id() const
   {
      return m_entity_id;
   }

   [[nodiscard]] constexpr game::Mode game_mode() const
   {
      return m_game_mode;
   }

   [[nodiscard]] constexpr const Abilities &abilities() const
   {
      return m_abilities;
   }

   [[nodiscard]] constexpr const Inventory &inventory() const
   {
      return m_inventory;
   }

   [[nodiscard]] constexpr Inventory &inventory()
   {
      return m_inventory;
   }

   [[nodiscard]] constexpr const std::string &name() const
   {
      return m_name;
   }

   [[nodiscard]] constexpr int ping() const
   {
      return m_ping;
   }

   constexpr void set_entity_id(entity::Id entity_id)
   {
      m_entity_id = entity_id;
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

   void on_movement(game::World &w, util::Vec3 pos);
   mb::result<mb::empty> load_chunks(game::World &w);

   static Player from_nbt(const nbt::player::v1::Player &player, const std::string &name);

   [[nodiscard]] proto::player::v1::Player to_proto(const game::entity::Entity &entity) const;
};

}// namespace minecpp::player