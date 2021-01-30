#pragma once
#include "minecpp/game/notifier.h"
#include <boost/uuid/uuid.hpp>
#include <map>
#include <minecpp/game/dimension.h>
#include <minecpp/util/vec.h>

namespace minecpp::game {
class PlayerData;
}

namespace minecpp::game::entity {

using boost::uuids::uuid;
using minecpp::util::Vec3;

typedef std::string_view AttributeName;
typedef std::string_view Type;

extern std::string player_type;
extern std::array<std::string, 7> known_attributes;

AttributeName to_attribute_name(const std::string &s);

class Attributes {
   std::map<AttributeName, double> attributes;

 public:
   void set_attribute(AttributeName name, double value);
};

struct Tracking {
   int64_t x, y, z;
};

struct Movement {
   short x, y, z;

   bool nil();
};

class Entity {
   friend PlayerData;

   uint32_t id;
   uuid uid;
   Type type;

   Attributes attributes;
   Dimension dimension = Dimension::Overworld;
   Tracking tracking;

   float health = 10.0f;
   float absorption_amount = 0.0f;
   float fall_distance = 0;

   short air = 300;
   short death_time = 0;
   short fire = -1;
   short hurt_time = 0;

   bool can_pick_up_loot = false;
   bool fall_flying = false;
   bool hurt_by_timestamp = false;
   bool invulnerable = false;
   bool left_handed = false;
   bool on_ground = true;
   bool persistence_required = false;

   Vec3 motion;
   Vec3 pos;
   float yaw = 0.0f, pitch = 0.0f;

 public:
   Entity(uuid uid, Type type);

   [[nodiscard]] Dimension get_dimension() const;
   [[nodiscard]] Vec3 get_pos() const;
   [[nodiscard]] float get_yaw() const;
   [[nodiscard]] float get_pitch() const;
   void set_pos(Notifier &n, Vec3 pos);
   void set_rot(float yaw, float pitch);
   void set_id(uint32_t id);
   uint32_t get_id();

   Movement process_movement();
   void sync_tracking();
};

} // namespace minecpp::game::entity
