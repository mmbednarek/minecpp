#include "player_data.h"
#include <game/items/registry.h>
#include <nbt/parser.h>

namespace Game {

using NBT::TagID;

PlayerData::PlayerData(boost::uuids::uuid id) : id(id) {}

PlayerData::PlayerData(NBT::Reader &r) : id() {
   r.read_compound([this](NBT::Reader &r, NBT::TagID tagid,
                          const std::string &name) { load(r, tagid, name); });
}

void PlayerData::load(NBT::Reader &r, NBT::TagID tagid,
                      const std::string &name) {
   switch (tagid) {
   case TagID::Float:
      if (name == "AbsorptionAmount") {
         absorption_amount = r.read_payload<TagID::Float>();
         return;
      }
      if (name == "FallDistance") {
         fall_distance = r.read_payload<TagID::Float>();
         return;
      }
      if (name == "Health") {
         health = r.read_payload<TagID::Float>();
         return;
      }
      if (name == "XpP") {
         xp_points = r.read_payload<TagID::Float>();
         return;
      }
      if (name == "foodExhaustionLevel") {
         food_exhaustion_level = r.read_payload<TagID::Float>();
         return;
      }
      if (name == "foodSaturationLevel") {
         food_saturation_level = r.read_payload<TagID::Float>();
         return;
      }
      break;
   case TagID::Int:
      if (name == "playerGameType") {
         game_type = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "Dimension") {
         dimension = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "HurtByTimestamp") {
         hurt_by_timestamp = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "Score") {
         score = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "SelectedItemSlot") {
         slot = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "XpLevel") {
         xp_level = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "XpSeed") {
         xp_seed = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "XpTotal") {
         xp_total = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "foodLevel") {
         food_level = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "foodTickTimer") {
         food_tick_timer = r.read_payload<TagID::Int>();
         return;
      }
      if (name == "PortalCooldown") {
         portal_cooldown = r.read_payload<TagID::Int>();
         return;
      }
      break;
   case TagID::Short:
      if (name == "Air") {
         air = r.read_payload<TagID::Short>();
         return;
      }
      if (name == "DeathTime") {
         death_time = r.read_payload<TagID::Short>();
         return;
      }
      if (name == "Fire") {
         fire = r.read_payload<TagID::Short>();
         return;
      }
      if (name == "HurtTime") {
         hurt_time = r.read_payload<TagID::Short>();
         return;
      }
      if (name == "SleepTimer") {
         sleep_timer = r.read_payload<TagID::Short>();
         return;
      }
      if (name == "SleepTimer") {
         sleep_timer = r.read_payload<TagID::Short>();
         return;
      }
      break;
   case TagID::Byte:
      if (name == "FallFlying") {
         fall_flying = r.read_payload<TagID::Byte>();
         return;
      }
      if (name == "Invulnerable") {
         invulnerable = r.read_payload<TagID::Byte>();
         return;
      }
      if (name == "OnGround") {
         on_ground = r.read_payload<TagID::Byte>();
         return;
      }
      if (name == "seenCredits") {
         seen_credits = r.read_payload<TagID::Byte>();
         return;
      }
      break;
   case TagID::List:
      if (name == "Motion") {
         motion = r.read_vec3();
         return;
      }
      if (name == "Pos") {
         motion = r.read_vec3();
         return;
      }
      if (name == "Rotation") {
         auto rot = r.read_list_payload<TagID::Float>();
         if (rot.size() == 2) {
            yaw = rot[0];
            pitch = rot[1];
         }
         return;
      }
      if (name == "EnderItems") {
         r.read_list([this](NBT::Reader &r) {
            ender_chest.emplace_back(InventoryItem(r));
         });
         return;
      }
      if (name == "Inventory") {
         r.read_list([this](NBT::Reader &r) {
            inventory.emplace_back(InventoryItem(r));
         });
         return;
      }
      if (name == "Attributes") {
         r.read_list([this](NBT::Reader &r) {
            double base = 0.0;
            std::string name;
            r.read_compound([&base, &name](NBT::Reader &r, NBT::TagID tagid,
                                           const std::string &key) {
               if (tagid == NBT::Double && key == "Base") {
                  base = r.read_payload<NBT::Double>();
                  return;
               }
               if (tagid == NBT::String && key == "Name") {
                  name = r.read_payload<NBT::String>();
                  return;
               }
               r.skip_payload(tagid);
            });
            attributes[name] = base;
         });
         return;
      }
      break;
   case TagID::Compound:
      if (name == "abilities") {
         abilities = Abilities(r);
         return;
      }
      if (name == "recipeBook") {
         recipe_book = RecipeBook(r);
         return;
      }
      break;
   case TagID::Long:
      if (name == "UUIDLeast") {
         uint64_t value = r.read_payload<NBT::Long>();
         std::memcpy(id.data, (char *)&value, sizeof(uint64_t));
         return;
      }
      if (name == "UUIDMost") {
         uint64_t value = r.read_payload<NBT::Long>();
         std::memcpy(id.data + sizeof(uint64_t), (char *)&value,
                     sizeof(uint64_t));
         return;
      }
      break;
   default:
      break;
   }

   r.skip_payload(tagid);
}

Entity::Entity PlayerData::to_entity() {
   Entity::Entity player_entity(id, Entity::player_type);
   for (const auto &at : attributes) {
      player_entity.attributes.set_attribute(
          Entity::to_attribute_name(at.first), at.second);
   }
   player_entity.dimension = static_cast<Dimension>(dimension);
   player_entity.health = health;
   player_entity.absorption_amount = absorption_amount;
   player_entity.fall_distance = fall_distance;
   player_entity.air = air;
   player_entity.death_time = death_time;
   player_entity.fire = fire;
   player_entity.hurt_time = hurt_time;
   player_entity.can_pick_up_loot = true;
   player_entity.fall_flying = fall_flying;
   player_entity.hurt_by_timestamp = hurt_by_timestamp;
   player_entity.invulnerable = invulnerable;
   player_entity.on_ground = on_ground;
   player_entity.motion = motion;
   player_entity.pos = pos;
   player_entity.yaw = yaw;
   player_entity.pitch = pitch;
   player_entity.sync_tracking();
   return player_entity;
}

Player PlayerData::to_player(std::string &name) {
   Player player(id, name, pos);
   player.xp_total = xp_total;
   player.xp_points = xp_points;
   player.xp_seed = xp_seed;
   player.xp_level = xp_level;
   player.food_level = food_level;
   player.food_saturation_level = food_saturation_level;
   player.food_exhaustion_level = food_exhaustion_level;
   player.food_tick_timer = food_tick_timer;
   player.recipe_book = recipe_book;
   player.inventory = std::move(inventory);
   player.ender_chest = std::move(ender_chest);
   player.abilities.invulnerable = player.abilities.invulnerable;
   player.abilities.may_build = player.abilities.may_build;
   player.abilities.instant_build = player.abilities.instant_build;
   player.abilities.flying = player.abilities.flying;
   player.abilities.may_fly = player.abilities.may_fly;
   player.abilities.walk_speed = player.abilities.walk_speed;
   player.abilities.fly_speed = player.abilities.fly_speed;
   return player;
}

PlayerData::Abilities::Abilities(NBT::Reader &r) {
   r.read_compound(
       [this](NBT::Reader &r, TagID tagid, const std::string &name) {
          switch (tagid) {
          case TagID::Float:
             if (name == "flySpeed") {
                fly_speed = r.read_payload<TagID::Float>();
                return;
             }
             if (name == "walkSpeed") {
                walk_speed = r.read_payload<TagID::Float>();
                return;
             }
             break;
          case TagID::Byte:
             if (name == "flying") {
                flying = r.read_payload<TagID::Byte>();
                return;
             }
             if (name == "instabuild") {
                instant_build = r.read_payload<TagID::Byte>();
                return;
             }
             if (name == "invulnerable") {
                invulnerable = r.read_payload<TagID::Byte>();
                return;
             }
             if (name == "may_build") {
                may_build = r.read_payload<TagID::Byte>();
                return;
             }
             if (name == "may_fly") {
                may_fly = r.read_payload<TagID::Byte>();
                return;
             }
             break;
          default:
             break;
          }
          r.skip_payload(tagid);
       });
}

} // namespace Game
