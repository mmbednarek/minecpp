#include <algorithm>
#include <minecpp/game/entity/Entity.h>
#include <minecpp/game/player/Id.h>
#include <minecpp/nbt/player/v1/Player.nbt.h>

namespace minecpp::game::entity {

std::array<std::string, 7> known_attributes{
        "generic.maxHealth",      "generic.knockbackResistance", "generic.movementSpeed",   "generic.armor",
        "generic.armorToughness", "generic.followRange",         "generic.attackKnockback",
};

AttributeName to_attribute_name(const std::string &s)
{
   return *std::find(known_attributes.begin(), known_attributes.end(), s);
}

std::string g_player_type = "minecraft:player";

Entity::Entity(uuid uid, const Type &type) :
    uid(uid),
    type(type)
{
}

math::Vector3 Entity::get_pos() const
{
   return pos;
}

float Entity::get_yaw() const
{
   return yaw;
}

float Entity::get_pitch() const
{
   return pitch;
}

void Entity::set_pos(Notifier &n, math::Vector3 pos)
{
   this->pos     = pos;
   auto movement = process_movement();
   if (movement.x != 0 || movement.y != 0 || movement.z != 0) {
      n.entity_move(uid, id, movement, {yaw, pitch});
   }
}

void Entity::set_rot(float yaw, float pitch)
{
   this->yaw   = yaw;
   this->pitch = pitch;
}

void Entity::set_id(uint32_t id)
{
   this->id = id;
}

uint32_t Entity::get_id()
{
   return id;
}

Movement Entity::process_movement()
{
   math::Vector3 tracked_pos = math::Vector3{static_cast<double>(tracking.x), static_cast<double>(tracking.y),
                                             static_cast<double>(tracking.z)} /
                               4096.0;
   math::Vector3 diff = pos - tracked_pos;

   auto movement = Movement{
           .x = static_cast<short>(diff.x() * 4096),
           .y = static_cast<short>(diff.y() * 4096),
           .z = static_cast<short>(diff.z() * 4096),
   };

   tracking.x += static_cast<int64_t>(movement.x);
   tracking.y += static_cast<int64_t>(movement.y);
   tracking.z += static_cast<int64_t>(movement.z);

   return movement;
}

void Entity::sync_tracking()
{
   tracking.x = static_cast<mb::i64>(pos.x() * 4096.0);
   tracking.y = static_cast<mb::i64>(pos.y() * 4096.0);
   tracking.z = static_cast<mb::i64>(pos.z() * 4096.0);
}

void Attributes::set_attribute(AttributeName name, double value)
{
   attributes[name] = value;
}

Entity Entity::from_player_nbt(const nbt::player::v1::Location &player)
{
   Entity entity(player::read_id_from_nbt(player.uuid), g_player_type);
   for (const auto &at : player.attributes) {
      entity.attributes.set_attribute(entity::to_attribute_name(at.name), at.base);
   }

   //   entity.health            = player.health;
   entity.health            = 20.0f;
   entity.absorption_amount = player.absorption_amount;
   entity.fall_distance     = player.fall_distance;
   entity.air               = player.air;
   entity.death_time        = player.death_time;
   entity.fire              = player.fire;
   entity.hurt_time         = player.hurt_time;
   entity.can_pick_up_loot  = true;
   entity.fall_flying       = player.fall_flying;
   entity.hurt_by_timestamp = player.hurt_by_timestamp;
   entity.invulnerable      = player.invulnerable;
   entity.on_ground         = player.on_ground;
   if (player.motion.size() == 3) {
      entity.motion = math::Vector3{player.motion[0], player.motion[1], player.motion[2]};
   }
   if (player.pos.size() == 3) {
      entity.pos = math::Vector3{player.pos[0], player.pos[1], player.pos[2]};
   }
   if (player.rotation.size() == 2) {
      entity.yaw   = player.rotation[0];
      entity.pitch = player.rotation[1];
   }
   entity.sync_tracking();

   return entity;
}

void Entity::damage(float value)
{
   if (health - value <= 0) {
      health = 0;
      // dieee
      return;
   }

   health -= value;
}

float Entity::get_health() const
{
   return health;
}

}

// namespace minecpp::game::entity
