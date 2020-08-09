#pragma once
#include "entities/entity.h"
#include "inventory.h"
#include "player.h"
#include "recipe_book.h"
#include <boost/uuid/uuid.hpp>
#include <map>
#include <mineutils/vec.h>
#include <nbt/reader.h>

namespace Game {

using Utils::Vec3;

class PlayerData {
 public:
   struct Abilities {
      float fly_speed = 0.05f;
      bool flying = false;
      bool instant_build = true;
      bool invulnerable = false;
      bool may_build = true;
      bool may_fly = false;
      float walk_speed = 0.1f;

      Abilities() = default;
      explicit Abilities(NBT::Reader &r);
   };

   explicit PlayerData(NBT::Reader &r);
   explicit PlayerData(boost::uuids::uuid id);

   void load(NBT::Reader &r, NBT::TagId tagid, const std::string &name);

   Entity::Entity to_entity();
   // NOTICE: ender chest and inventory is moved
   Player to_player(std::string &name);

   boost::uuids::uuid id;
   int game_type = 0;
   Abilities abilities;
   RecipeBook recipe_book;

   std::vector<InventoryItem> ender_chest;
   std::vector<InventoryItem> inventory;

   std::map<std::string, double> attributes;

   float absorption_amount = 0.0f;
   short air = 300;
   short death_time = 0;
   int dimension = 0;
   float fall_distance = 0.0f;
   bool fall_flying = false;
   short fire = -20;

   float health = 20.0f;
   int hurt_by_timestamp = 1600;
   short hurt_time = 0;
   bool invulnerable = false;

   Vec3 motion;
   Vec3 pos{0.0, 75.0, 0.0};
   bool on_ground = true;
   int portal_cooldown = 0;

   float yaw = 0.0, pitch = 0.0;

   int score = 0;
   int slot = 0;
   short sleep_timer = 0;

   int xp_level = 0;
   float xp_points = .0f;
   int xp_seed = 0;
   int xp_total = 0;

   int food_level = 20;
   float food_exhaustion_level = 0.16f;
   float food_saturation_level = 5.0f;
   int food_tick_timer = 0;

   bool seen_credits = false;
};

} // namespace Game
