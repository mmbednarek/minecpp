#pragma once
#include "inventory.h"
#include "mode.h"
#include "recipe_book.h"
#include "tracking.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <minepb/player.pb.h>
#include <string>

namespace Game {

class PlayerData;

using boost::uuids::uuid;

class Player {
   friend PlayerData;

 public:
   struct Abilities {
      float fly_speed = 0.05f;
      bool flying = false;
      bool instant_build = true;
      bool invulnerable = false;
      bool may_build = true;
      bool may_fly = true;
      float walk_speed = 0.1f;

      void from_proto(minecpp::player::Abilities abilities);
      void as_proto(minecpp::player::Abilities *abilities) const;
      uint32_t flags();
   };

 private:
   uuid id;
   uint32_t entity_id{};
   std::string player_name;
   Mode game_mode = Mode::Survival;
   Tracking tracking;

   int ping{};

   int xp_level = 0;
   float xp_points = .0f;
   int xp_seed = 0;
   int xp_total = 0;

   int food_level = 20;
   float food_exhaustion_level = 0.16f;
   float food_saturation_level = 5.0f;
   int food_tick_timer = 0;

   Abilities abilities;

   RecipeBook recipe_book;

   std::vector<InventoryItem> ender_chest;
   std::vector<InventoryItem> inventory;

 public:
   Player(uuid id, std::string &name, Vec3 pos);

   void set_entity_id(uint32_t entity_id);
   void set_ping(int ping);
   [[nodiscard]] uuid get_id() const;
   [[nodiscard]] uint32_t get_entity_id() const;
   [[nodiscard]] Mode get_game_mode() const;
   [[nodiscard]] const Abilities &get_abilities() const;
   [[nodiscard]] const RecipeBook &get_recipe_book() const;
   [[nodiscard]] std::string_view get_player_name() const;
   [[nodiscard]] int get_ping() const;

   void on_movement(World &w, Vec3 pos);
   void load_chunks(World &w);
};

} // namespace Game
