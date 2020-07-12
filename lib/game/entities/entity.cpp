#include "entity.h"
#include <algorithm>

namespace Game::Entity {

std::array<std::string, 7> known_attributes{
    "generic.maxHealth",      "generic.knockbackResistance", "generic.movementSpeed",   "generic.armor",
    "generic.armorToughness", "generic.followRange",         "generic.attackKnockback",
};

AttributeName to_attribute_name(const std::string &s) {
   return *std::find(known_attributes.begin(), known_attributes.end(), s);
}

std::string player_type = "player";

Entity::Entity(uuid uid, Type type) : uid(uid), type(type) {}

Dimension Entity::get_dimension() const { return dimension; }

Vec3 Entity::get_pos() const { return pos; }

float Entity::get_yaw() const { return yaw; }

float Entity::get_pitch() const { return pitch; }

void Entity::set_pos(Notifier &n, Vec3 pos) {
   this->pos = pos;
   auto movement = process_movement();
   if (!movement.nil()) {
      n.entity_move(id, uid, movement, yaw, pitch);
   }
}

void Entity::set_rot(float yaw, float pitch) {
   this->yaw = yaw;
   this->pitch = pitch;
}

void Entity::set_id(uint32_t id) { this->id = id; }

uint32_t Entity::get_id() { return id; }

Movement Entity::process_movement() {
   Vec3 tracked_pos = Vec3(tracking.x, tracking.y, tracking.z) / 4096.0;
   Vec3 diff = pos - tracked_pos;

   auto movement = Movement{
       .x = static_cast<short>(diff.x * 4096),
       .y = static_cast<short>(diff.y * 4096),
       .z = static_cast<short>(diff.z * 4096),
   };

   tracking.x += static_cast<int64_t>(movement.x);
   tracking.y += static_cast<int64_t>(movement.y);
   tracking.z += static_cast<int64_t>(movement.z);

   return movement;
}

void Entity::sync_tracking() {
   tracking.x = pos.x * 4096.0;
   tracking.y = pos.y * 4096.0;
   tracking.z = pos.z * 4096.0;
}

void Attributes::set_attribute(AttributeName name, double value) { attributes[name] = value; }

bool Movement::nil() { return x == 0 && y == 0 && z == 0; }
} // namespace Game::Entity
