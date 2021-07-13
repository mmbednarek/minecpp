#include <minecpp/message/nbt/chunk.nbt.h>

namespace minecpp::message::nbt {

void ArmorItem::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.end_compound();
}

void ArmorItem::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ArmorItem ArmorItem::deserialize_no_header(minecpp::nbt::Reader &r) {
   ArmorItem res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      r.skip_payload(tagid);
   });
   return res;
}

ArmorItem ArmorItem::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return ArmorItem();
   }
   return ArmorItem::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> ArmorItem::__xx_offsets {
};

int ArmorItem::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Attribute::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Double, "Base");
   w.write_double_content(base);
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.end_compound();
}

void Attribute::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Attribute Attribute::deserialize_no_header(minecpp::nbt::Reader &r) {
   Attribute res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Double:
         res.__xx_put(name, r.read_float64());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Attribute Attribute::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Attribute();
   }
   return Attribute::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Attribute::__xx_offsets {
   {"Base", {offsetof(Attribute, base), sizeof(Attribute::base), 1}},
   {"Name", {offsetof(Attribute, name), sizeof(Attribute::name), 2}},
};

int Attribute::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Memories::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.end_compound();
}

void Memories::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Memories Memories::deserialize_no_header(minecpp::nbt::Reader &r) {
   Memories res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      r.skip_payload(tagid);
   });
   return res;
}

Memories Memories::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Memories();
   }
   return Memories::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Memories::__xx_offsets {
};

int Memories::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Brain::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "memories");
   memories.serialize_no_header(w);
   w.end_compound();
}

void Brain::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Brain Brain::deserialize_no_header(minecpp::nbt::Reader &r) {
   Brain res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 1:
            res.__xx_put(name, Memories::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Brain Brain::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Brain();
   }
   return Brain::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Brain::__xx_offsets {
   {"memories", {offsetof(Brain, memories), sizeof(Brain::memories), 1}},
};

int Brain::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void HandItem::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.end_compound();
}

void HandItem::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

HandItem HandItem::deserialize_no_header(minecpp::nbt::Reader &r) {
   HandItem res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      r.skip_payload(tagid);
   });
   return res;
}

HandItem HandItem::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return HandItem();
   }
   return HandItem::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> HandItem::__xx_offsets {
};

int HandItem::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Entity::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Float, "AbsorptionAmount");
   w.write_float_content(absorption_amount);
   w.write_header(minecpp::nbt::TagId::Short, "Air");
   w.write_short_content(air);
   w.write_header(minecpp::nbt::TagId::List, "ArmorDropChances");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, armor_drop_chances.size());
   std::for_each(armor_drop_chances.begin(), armor_drop_chances.end(), [&w](const auto &value) {
      w.write_float_content(value);
   });
   w.write_header(minecpp::nbt::TagId::List, "ArmorItems");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, armor_items.size());
   std::for_each(armor_items.begin(), armor_items.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::List, "Attributes");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, attributes.size());
   std::for_each(attributes.begin(), attributes.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::Compound, "Brain");
   brain.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "CanPickUpLoot");
   w.write_byte_content(can_pick_up_loot);
   w.write_header(minecpp::nbt::TagId::Short, "DeathTime");
   w.write_short_content(death_time);
   w.write_header(minecpp::nbt::TagId::Byte, "ExplosionRadius");
   w.write_byte_content(explosion_radius);
   w.write_header(minecpp::nbt::TagId::Float, "FallDistance");
   w.write_float_content(fall_distance);
   w.write_header(minecpp::nbt::TagId::Byte, "FallFlying");
   w.write_byte_content(fall_flying);
   w.write_header(minecpp::nbt::TagId::Short, "Fire");
   w.write_short_content(fire);
   w.write_header(minecpp::nbt::TagId::Short, "Fuse");
   w.write_short_content(fuse);
   w.write_header(minecpp::nbt::TagId::List, "HandDropChances");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, hand_drop_chances.size());
   std::for_each(hand_drop_chances.begin(), hand_drop_chances.end(), [&w](const auto &value) {
      w.write_float_content(value);
   });
   w.write_header(minecpp::nbt::TagId::List, "HandItems");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, hand_items.size());
   std::for_each(hand_items.begin(), hand_items.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::Float, "Health");
   w.write_float_content(health);
   w.write_header(minecpp::nbt::TagId::Int, "HurtByTimestamp");
   w.write_int_content(hurt_by_timestamp);
   w.write_header(minecpp::nbt::TagId::Short, "HurtTime");
   w.write_short_content(hurt_time);
   w.write_header(minecpp::nbt::TagId::Byte, "Invulnerable");
   w.write_byte_content(invulnerable);
   w.write_header(minecpp::nbt::TagId::Byte, "LeftHanded");
   w.write_byte_content(left_handed);
   w.write_header(minecpp::nbt::TagId::List, "Motion");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, motion.size());
   std::for_each(motion.begin(), motion.end(), [&w](const auto &value) {
      w.write_double_content(value);
   });
   w.write_header(minecpp::nbt::TagId::Byte, "OnGround");
   w.write_byte_content(on_ground);
   w.write_header(minecpp::nbt::TagId::Byte, "PersistenceRequired");
   w.write_byte_content(persistence_required);
   w.write_header(minecpp::nbt::TagId::Int, "PortalCooldown");
   w.write_int_content(portal_cooldown);
   w.write_header(minecpp::nbt::TagId::List, "Pos");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, pos.size());
   std::for_each(pos.begin(), pos.end(), [&w](const auto &value) {
      w.write_double_content(value);
   });
   w.write_header(minecpp::nbt::TagId::List, "Rotation");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, rotation.size());
   std::for_each(rotation.begin(), rotation.end(), [&w](const auto &value) {
      w.write_float_content(value);
   });
   w.write_header(minecpp::nbt::TagId::IntArray, "UUID");
   w.write_ints_content(uuid);
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.write_header(minecpp::nbt::TagId::Byte, "ignited");
   w.write_byte_content(ignited);
   w.end_compound();
}

void Entity::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Entity Entity::deserialize_no_header(minecpp::nbt::Reader &r) {
   Entity res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Short:
         res.__xx_put(name, r.read_short());
         return;
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Float:
         res.__xx_put(name, r.read_float32());
         return;
      case minecpp::nbt::TagId::IntArray:
         res.__xx_put(name, r.read_int_vec());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 6:
            res.__xx_put(name, Brain::deserialize_no_header(r));
            return;
         }
         break;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Float: {
               std::vector<float> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() {
                  return r.read_float32();
               });
               res.__xx_put(name, ls);
               return;
            }
            case minecpp::nbt::TagId::Double: {
               std::vector<double> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() {
                  return r.read_float64();
               });
               res.__xx_put(name, ls);
               return;
            }
            case minecpp::nbt::TagId::Compound: {
               switch (res.__xx_get_id(name)) {
               case 4: {
                  std::vector<ArmorItem> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return ArmorItem::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               case 5: {
                  std::vector<Attribute> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return Attribute::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               case 15: {
                  std::vector<HandItem> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return HandItem::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               }
               break;
            }
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      }
      r.skip_payload(tagid);
   });
   return res;
}

Entity Entity::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Entity();
   }
   return Entity::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Entity::__xx_offsets {
   {"AbsorptionAmount", {offsetof(Entity, absorption_amount), sizeof(Entity::absorption_amount), 1}},
   {"Air", {offsetof(Entity, air), sizeof(Entity::air), 2}},
   {"ArmorDropChances", {offsetof(Entity, armor_drop_chances), sizeof(Entity::armor_drop_chances), 3}},
   {"ArmorItems", {offsetof(Entity, armor_items), sizeof(Entity::armor_items), 4}},
   {"Attributes", {offsetof(Entity, attributes), sizeof(Entity::attributes), 5}},
   {"Brain", {offsetof(Entity, brain), sizeof(Entity::brain), 6}},
   {"CanPickUpLoot", {offsetof(Entity, can_pick_up_loot), sizeof(Entity::can_pick_up_loot), 7}},
   {"DeathTime", {offsetof(Entity, death_time), sizeof(Entity::death_time), 8}},
   {"ExplosionRadius", {offsetof(Entity, explosion_radius), sizeof(Entity::explosion_radius), 9}},
   {"FallDistance", {offsetof(Entity, fall_distance), sizeof(Entity::fall_distance), 10}},
   {"FallFlying", {offsetof(Entity, fall_flying), sizeof(Entity::fall_flying), 11}},
   {"Fire", {offsetof(Entity, fire), sizeof(Entity::fire), 12}},
   {"Fuse", {offsetof(Entity, fuse), sizeof(Entity::fuse), 13}},
   {"HandDropChances", {offsetof(Entity, hand_drop_chances), sizeof(Entity::hand_drop_chances), 14}},
   {"HandItems", {offsetof(Entity, hand_items), sizeof(Entity::hand_items), 15}},
   {"Health", {offsetof(Entity, health), sizeof(Entity::health), 16}},
   {"HurtByTimestamp", {offsetof(Entity, hurt_by_timestamp), sizeof(Entity::hurt_by_timestamp), 17}},
   {"HurtTime", {offsetof(Entity, hurt_time), sizeof(Entity::hurt_time), 18}},
   {"Invulnerable", {offsetof(Entity, invulnerable), sizeof(Entity::invulnerable), 19}},
   {"LeftHanded", {offsetof(Entity, left_handed), sizeof(Entity::left_handed), 20}},
   {"Motion", {offsetof(Entity, motion), sizeof(Entity::motion), 21}},
   {"OnGround", {offsetof(Entity, on_ground), sizeof(Entity::on_ground), 22}},
   {"PersistenceRequired", {offsetof(Entity, persistence_required), sizeof(Entity::persistence_required), 23}},
   {"PortalCooldown", {offsetof(Entity, portal_cooldown), sizeof(Entity::portal_cooldown), 24}},
   {"Pos", {offsetof(Entity, pos), sizeof(Entity::pos), 25}},
   {"Rotation", {offsetof(Entity, rotation), sizeof(Entity::rotation), 26}},
   {"UUID", {offsetof(Entity, uuid), sizeof(Entity::uuid), 27}},
   {"id", {offsetof(Entity, id), sizeof(Entity::id), 28}},
   {"ignited", {offsetof(Entity, ignited), sizeof(Entity::ignited), 29}},
};

int Entity::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Heightmaps::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::LongArray, "MOTION_BLOCKING");
   w.write_longs_content(motion_blocking);
   w.write_header(minecpp::nbt::TagId::LongArray, "MOTION_BLOCKING_NO_LEAVES");
   w.write_longs_content(motion_blocking_no_leaves);
   w.write_header(minecpp::nbt::TagId::LongArray, "OCEAN_FLOOR");
   w.write_longs_content(ocean_floor);
   w.write_header(minecpp::nbt::TagId::LongArray, "OCEAN_FLOOR_WG");
   w.write_longs_content(ocean_floor_wg);
   w.write_header(minecpp::nbt::TagId::LongArray, "WORLD_SURFACE");
   w.write_longs_content(world_surface);
   w.write_header(minecpp::nbt::TagId::LongArray, "WORLD_SURFACE_WG");
   w.write_longs_content(world_surface_wg);
   w.end_compound();
}

void Heightmaps::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Heightmaps Heightmaps::deserialize_no_header(minecpp::nbt::Reader &r) {
   Heightmaps res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::LongArray:
         res.__xx_put(name, r.read_long_vec());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Heightmaps Heightmaps::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Heightmaps();
   }
   return Heightmaps::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Heightmaps::__xx_offsets {
   {"MOTION_BLOCKING", {offsetof(Heightmaps, motion_blocking), sizeof(Heightmaps::motion_blocking), 1}},
   {"MOTION_BLOCKING_NO_LEAVES", {offsetof(Heightmaps, motion_blocking_no_leaves), sizeof(Heightmaps::motion_blocking_no_leaves), 2}},
   {"OCEAN_FLOOR", {offsetof(Heightmaps, ocean_floor), sizeof(Heightmaps::ocean_floor), 3}},
   {"OCEAN_FLOOR_WG", {offsetof(Heightmaps, ocean_floor_wg), sizeof(Heightmaps::ocean_floor_wg), 4}},
   {"WORLD_SURFACE", {offsetof(Heightmaps, world_surface), sizeof(Heightmaps::world_surface), 5}},
   {"WORLD_SURFACE_WG", {offsetof(Heightmaps, world_surface_wg), sizeof(Heightmaps::world_surface_wg), 5}},
};

int Heightmaps::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void PaletteItem::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Compound, "Properties");
   minecpp::nbt::serialize_compound_content(w, properties);
   w.end_compound();
}

void PaletteItem::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

PaletteItem PaletteItem::deserialize_no_header(minecpp::nbt::Reader &r) {
   PaletteItem res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 2:
            res.__xx_put(name, r.read_compound_content());
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

PaletteItem PaletteItem::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return PaletteItem();
   }
   return PaletteItem::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> PaletteItem::__xx_offsets {
   {"Name", {offsetof(PaletteItem, name), sizeof(PaletteItem::name), 1}},
   {"Properties", {offsetof(PaletteItem, properties), sizeof(PaletteItem::properties), 2}},
};

int PaletteItem::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Section::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "Y");
   w.write_byte_content(y);
   w.write_header(minecpp::nbt::TagId::ByteArray, "BlockLight");
   w.write_bytes_content(block_light);
   w.write_header(minecpp::nbt::TagId::ByteArray, "SkyLight");
   w.write_bytes_content(sky_light);
   w.write_header(minecpp::nbt::TagId::LongArray, "BlockStates");
   w.write_longs_content(block_states);
   w.write_header(minecpp::nbt::TagId::List, "Palette");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, palette.size());
   std::for_each(palette.begin(), palette.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.end_compound();
}

void Section::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Section Section::deserialize_no_header(minecpp::nbt::Reader &r) {
   Section res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::ByteArray:
         res.__xx_put(name, r.read_byte_vector());
         return;
      case minecpp::nbt::TagId::LongArray:
         res.__xx_put(name, r.read_long_vec());
         return;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               switch (res.__xx_get_id(name)) {
               case 5: {
                  std::vector<PaletteItem> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return PaletteItem::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               }
               break;
            }
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      }
      r.skip_payload(tagid);
   });
   return res;
}

Section Section::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Section();
   }
   return Section::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Section::__xx_offsets {
   {"Y", {offsetof(Section, y), sizeof(Section::y), 1}},
   {"BlockLight", {offsetof(Section, block_light), sizeof(Section::block_light), 2}},
   {"SkyLight", {offsetof(Section, sky_light), sizeof(Section::sky_light), 3}},
   {"BlockStates", {offsetof(Section, block_states), sizeof(Section::block_states), 4}},
   {"Palette", {offsetof(Section, palette), sizeof(Section::palette), 5}},
};

int Section::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Start::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.end_compound();
}

void Start::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Start Start::deserialize_no_header(minecpp::nbt::Reader &r) {
   Start res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Start Start::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Start();
   }
   return Start::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Start::__xx_offsets {
   {"id", {offsetof(Start, id), sizeof(Start::id), 1}},
};

int Start::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Structures::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "Starts");
   std::for_each(starts.begin(), starts.end(), [&w](const auto &pair) {
      w.write_header(minecpp::nbt::TagId::Compound, pair.first);
      pair.second.serialize_no_header(w);
   });
   w.end_compound();
   w.end_compound();
}

void Structures::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Structures Structures::deserialize_no_header(minecpp::nbt::Reader &r) {
   Structures res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 1:
            r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
               if (tagid != minecpp::nbt::TagId::Compound) {
                  r.skip_payload(tagid);
                  return;
               }
               res.starts.insert(std::make_pair(name, Start::deserialize_no_header(r)));
            });
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Structures Structures::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Structures();
   }
   return Structures::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Structures::__xx_offsets {
   {"Starts", {offsetof(Structures, starts), sizeof(Structures::starts), 1}},
};

int Structures::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void CarvingMasks::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::ByteArray, "AIR");
   w.write_bytes_content(air);
   w.write_header(minecpp::nbt::TagId::ByteArray, "LIQUID");
   w.write_bytes_content(liquid);
   w.end_compound();
}

void CarvingMasks::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

CarvingMasks CarvingMasks::deserialize_no_header(minecpp::nbt::Reader &r) {
   CarvingMasks res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::ByteArray:
         res.__xx_put(name, r.read_byte_vector());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

CarvingMasks CarvingMasks::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return CarvingMasks();
   }
   return CarvingMasks::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> CarvingMasks::__xx_offsets {
   {"AIR", {offsetof(CarvingMasks, air), sizeof(CarvingMasks::air), 1}},
   {"LIQUID", {offsetof(CarvingMasks, liquid), sizeof(CarvingMasks::liquid), 2}},
};

int CarvingMasks::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Level::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::IntArray, "Biomes");
   w.write_ints_content(biomes);
   w.write_header(minecpp::nbt::TagId::Compound, "CarvingMasks");
   carving_masks.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::List, "Entities");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, entities.size());
   std::for_each(entities.begin(), entities.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::Compound, "Heightmaps");
   heightmaps.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Long, "LastUpdate");
   w.write_long_content(last_update);
   w.write_header(minecpp::nbt::TagId::List, "Lights");
   w.begin_list_no_header(minecpp::nbt::TagId::List, lights.size());
   std::for_each(lights.begin(), lights.end(), [&w](const auto &value) {
      w.begin_list_no_header(minecpp::nbt::TagId::Short, value.size());
      std::for_each(value.begin(), value.end(), [&w](const auto &value) {
         w.write_short_content(value);
      });
   });
   w.write_header(minecpp::nbt::TagId::Long, "InhabitedTime");
   w.write_long_content(inhabited_time);
   w.write_header(minecpp::nbt::TagId::List, "PostProcessing");
   w.begin_list_no_header(minecpp::nbt::TagId::List, post_processing.size());
   std::for_each(post_processing.begin(), post_processing.end(), [&w](const auto &value) {
      w.begin_list_no_header(minecpp::nbt::TagId::Short, value.size());
      std::for_each(value.begin(), value.end(), [&w](const auto &value) {
         w.write_short_content(value);
      });
   });
   w.write_header(minecpp::nbt::TagId::List, "Sections");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, sections.size());
   std::for_each(sections.begin(), sections.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::String, "Status");
   w.write_string_content(status);
   w.write_header(minecpp::nbt::TagId::Compound, "Structures");
   structures.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "isLightOn");
   w.write_byte_content(is_light_on);
   w.write_header(minecpp::nbt::TagId::Int, "xPos");
   w.write_int_content(x_pos);
   w.write_header(minecpp::nbt::TagId::Int, "zPos");
   w.write_int_content(z_pos);
   w.end_compound();
}

void Level::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Level Level::deserialize_no_header(minecpp::nbt::Reader &r) {
   Level res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::Long:
         res.__xx_put(name, r.read_long());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::IntArray:
         res.__xx_put(name, r.read_int_vec());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 2:
            res.__xx_put(name, CarvingMasks::deserialize_no_header(r));
            return;
         case 4:
            res.__xx_put(name, Heightmaps::deserialize_no_header(r));
            return;
         case 11:
            res.__xx_put(name, Structures::deserialize_no_header(r));
            return;
         }
         break;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               switch (res.__xx_get_id(name)) {
               case 3: {
                  std::vector<Entity> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return Entity::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               case 9: {
                  std::vector<Section> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return Section::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               }
               break;
            }
            case minecpp::nbt::TagId::List: {
               auto list_info1 = r.peek_list();
               if (list_info1.size > 0) {
                  switch (list_info1.tagid) {
                  case minecpp::nbt::TagId::Short: {
                     std::vector<std::vector<std::int16_t>> ls(list_info0.size);
                     if (list_info0.size != 0) {
                        auto it = ls.begin();
                        *it = [&r, &list_info1]() {
                           std::vector<std::int16_t> ls(list_info1.size);
                           std::generate(ls.begin(), ls.end(), [&r]() {
                              return r.read_short();
                           });
                           return ls;
                        }();
                        std::generate(it + 1, ls.end(), [&r]() {
                           auto list_info1 = r.peek_list();
                           std::vector<std::int16_t> ls(list_info1.size);
                           std::generate(ls.begin(), ls.end(), [&r]() {
                              return r.read_short();
                           });
                           return ls;
                        });
                     }
                     res.__xx_put(name, ls);
                     return;
                  }
                  }
                  for (mb::size i = 0; i < list_info1.size; ++i) {
                     r.skip_payload(list_info1.tagid);
                  }
               }
               return;
            }
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      }
      r.skip_payload(tagid);
   });
   return res;
}

Level Level::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Level();
   }
   return Level::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Level::__xx_offsets {
   {"Biomes", {offsetof(Level, biomes), sizeof(Level::biomes), 1}},
   {"CarvingMasks", {offsetof(Level, carving_masks), sizeof(Level::carving_masks), 2}},
   {"Entities", {offsetof(Level, entities), sizeof(Level::entities), 3}},
   {"Heightmaps", {offsetof(Level, heightmaps), sizeof(Level::heightmaps), 4}},
   {"LastUpdate", {offsetof(Level, last_update), sizeof(Level::last_update), 5}},
   {"Lights", {offsetof(Level, lights), sizeof(Level::lights), 6}},
   {"InhabitedTime", {offsetof(Level, inhabited_time), sizeof(Level::inhabited_time), 7}},
   {"PostProcessing", {offsetof(Level, post_processing), sizeof(Level::post_processing), 8}},
   {"Sections", {offsetof(Level, sections), sizeof(Level::sections), 9}},
   {"Status", {offsetof(Level, status), sizeof(Level::status), 10}},
   {"Structures", {offsetof(Level, structures), sizeof(Level::structures), 11}},
   {"isLightOn", {offsetof(Level, is_light_on), sizeof(Level::is_light_on), 14}},
   {"xPos", {offsetof(Level, x_pos), sizeof(Level::x_pos), 15}},
   {"zPos", {offsetof(Level, z_pos), sizeof(Level::z_pos), 16}},
};

int Level::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Chunk::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "DataVersion");
   w.write_int_content(version);
   w.write_header(minecpp::nbt::TagId::Compound, "Level");
   level.serialize_no_header(w);
   w.end_compound();
}

void Chunk::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Chunk Chunk::deserialize_no_header(minecpp::nbt::Reader &r) {
   Chunk res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 2:
            res.__xx_put(name, Level::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Chunk Chunk::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Chunk();
   }
   return Chunk::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Chunk::__xx_offsets {
   {"DataVersion", {offsetof(Chunk, version), sizeof(Chunk::version), 1}},
   {"Level", {offsetof(Chunk, level), sizeof(Chunk::level), 2}},
};

int Chunk::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

}