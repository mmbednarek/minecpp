#include "chunk/Chunk.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::chunk {

void ArmorItem::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "no_empty");
   w.write_int_content(no_empty);
   w.end_compound();
}

void ArmorItem::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ArmorItem ArmorItem::deserialize_no_header(minecpp::nbt::Reader &r) {
   ArmorItem result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "no_empty") {
         ::minecpp::nbt::verify_tag("ArmorItem", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.no_empty = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ArmorItem ArmorItem::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ArmorItem::deserialize_no_header(r);
}

void Attribute::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Double, "Base");
   w.write_double_content(base);
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.end_compound();
}

void Attribute::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Attribute Attribute::deserialize_no_header(minecpp::nbt::Reader &r) {
   Attribute result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Base") {
         ::minecpp::nbt::verify_tag("Attribute", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.base = r.read_float64();
         continue;
      }
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("Attribute", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Attribute Attribute::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Attribute::deserialize_no_header(r);
}

void Memories::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "no_empty");
   w.write_int_content(no_empty);
   w.end_compound();
}

void Memories::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Memories Memories::deserialize_no_header(minecpp::nbt::Reader &r) {
   Memories result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "no_empty") {
         ::minecpp::nbt::verify_tag("Memories", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.no_empty = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Memories Memories::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Memories::deserialize_no_header(r);
}

void Brain::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "memories");
   memories.serialize_no_header(w);
   w.end_compound();
}

void Brain::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Brain Brain::deserialize_no_header(minecpp::nbt::Reader &r) {
   Brain result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "memories") {
         ::minecpp::nbt::verify_tag("Brain", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.memories = Memories::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Brain Brain::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Brain::deserialize_no_header(r);
}

void HandItem::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "no_empty");
   w.write_int_content(no_empty);
   w.end_compound();
}

void HandItem::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

HandItem HandItem::deserialize_no_header(minecpp::nbt::Reader &r) {
   HandItem result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "no_empty") {
         ::minecpp::nbt::verify_tag("HandItem", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.no_empty = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

HandItem HandItem::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return HandItem::deserialize_no_header(r);
}

void Entity::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Float, "AbsorptionAmount");
   w.write_float_content(absorption_amount);
   w.write_header(minecpp::nbt::TagId::Short, "Air");
   w.write_short_content(air);
   w.write_header(minecpp::nbt::TagId::List, "ArmorDropChances");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, armor_drop_chances.size());
   for (const auto &list_item_0 : armor_drop_chances) {
      w.write_float_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::List, "ArmorItems");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, armor_items.size());
   for (const auto &list_item_0 : armor_items) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::List, "Attributes");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, attributes.size());
   for (const auto &list_item_0 : attributes) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::Compound, "Brain");
   brain.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "CanPickUpLoot");
   w.write_byte_content(static_cast<std::uint8_t>(can_pick_up_loot));
   w.write_header(minecpp::nbt::TagId::Short, "DeathTime");
   w.write_short_content(death_time);
   w.write_header(minecpp::nbt::TagId::Byte, "ExplosionRadius");
   w.write_byte_content(static_cast<std::uint8_t>(explosion_radius));
   w.write_header(minecpp::nbt::TagId::Float, "FallDistance");
   w.write_float_content(fall_distance);
   w.write_header(minecpp::nbt::TagId::Byte, "FallFlying");
   w.write_byte_content(static_cast<std::uint8_t>(fall_flying));
   w.write_header(minecpp::nbt::TagId::Short, "Fire");
   w.write_short_content(fire);
   w.write_header(minecpp::nbt::TagId::Short, "Fuse");
   w.write_short_content(fuse);
   w.write_header(minecpp::nbt::TagId::List, "HandDropChances");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, hand_drop_chances.size());
   for (const auto &list_item_0 : hand_drop_chances) {
      w.write_float_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::List, "HandItems");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, hand_items.size());
   for (const auto &list_item_0 : hand_items) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::Float, "Health");
   w.write_float_content(health);
   w.write_header(minecpp::nbt::TagId::Int, "HurtByTimestamp");
   w.write_int_content(hurt_by_timestamp);
   w.write_header(minecpp::nbt::TagId::Short, "HurtTime");
   w.write_short_content(hurt_time);
   w.write_header(minecpp::nbt::TagId::Byte, "Invulnerable");
   w.write_byte_content(static_cast<std::uint8_t>(invulnerable));
   w.write_header(minecpp::nbt::TagId::Byte, "LeftHanded");
   w.write_byte_content(static_cast<std::uint8_t>(left_handed));
   w.write_header(minecpp::nbt::TagId::List, "Motion");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, motion.size());
   for (const auto &list_item_0 : motion) {
      w.write_double_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::Byte, "OnGround");
   w.write_byte_content(static_cast<std::uint8_t>(on_ground));
   w.write_header(minecpp::nbt::TagId::Byte, "PersistenceRequired");
   w.write_byte_content(static_cast<std::uint8_t>(persistence_required));
   w.write_header(minecpp::nbt::TagId::Int, "PortalCooldown");
   w.write_int_content(portal_cooldown);
   w.write_header(minecpp::nbt::TagId::List, "Pos");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, pos.size());
   for (const auto &list_item_0 : pos) {
      w.write_double_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::List, "Rotation");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, rotation.size());
   for (const auto &list_item_0 : rotation) {
      w.write_float_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::IntArray, "UUID");
   w.write_ints_content(uuid);
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.write_header(minecpp::nbt::TagId::Byte, "ignited");
   w.write_byte_content(static_cast<std::uint8_t>(ignited));
   w.end_compound();
}

void Entity::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Entity Entity::deserialize_no_header(minecpp::nbt::Reader &r) {
   Entity result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "AbsorptionAmount") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.absorption_amount = r.read_float32();
         continue;
      }
      if (in_field_name == "Air") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.air = r.read_short();
         continue;
      }
      if (in_field_name == "ArmorDropChances") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<float> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_float32();
         });
         result.armor_drop_chances = std::move(list);
         continue;
      }
      if (in_field_name == "ArmorItems") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<ArmorItem> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return ArmorItem::deserialize_no_header(r);
         });
         result.armor_items = std::move(list);
         continue;
      }
      if (in_field_name == "Attributes") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<Attribute> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return Attribute::deserialize_no_header(r);
         });
         result.attributes = std::move(list);
         continue;
      }
      if (in_field_name == "Brain") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.brain = Brain::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "CanPickUpLoot") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.can_pick_up_loot = r.read_byte();
         continue;
      }
      if (in_field_name == "DeathTime") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.death_time = r.read_short();
         continue;
      }
      if (in_field_name == "ExplosionRadius") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.explosion_radius = r.read_byte();
         continue;
      }
      if (in_field_name == "FallDistance") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.fall_distance = r.read_float32();
         continue;
      }
      if (in_field_name == "FallFlying") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.fall_flying = r.read_byte();
         continue;
      }
      if (in_field_name == "Fire") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.fire = r.read_short();
         continue;
      }
      if (in_field_name == "Fuse") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.fuse = r.read_short();
         continue;
      }
      if (in_field_name == "HandDropChances") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<float> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_float32();
         });
         result.hand_drop_chances = std::move(list);
         continue;
      }
      if (in_field_name == "HandItems") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<HandItem> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return HandItem::deserialize_no_header(r);
         });
         result.hand_items = std::move(list);
         continue;
      }
      if (in_field_name == "Health") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.health = r.read_float32();
         continue;
      }
      if (in_field_name == "HurtByTimestamp") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.hurt_by_timestamp = r.read_int();
         continue;
      }
      if (in_field_name == "HurtTime") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.hurt_time = r.read_short();
         continue;
      }
      if (in_field_name == "Invulnerable") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.invulnerable = r.read_byte();
         continue;
      }
      if (in_field_name == "LeftHanded") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.left_handed = r.read_byte();
         continue;
      }
      if (in_field_name == "Motion") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<double> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_float64();
         });
         result.motion = std::move(list);
         continue;
      }
      if (in_field_name == "OnGround") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.on_ground = r.read_byte();
         continue;
      }
      if (in_field_name == "PersistenceRequired") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.persistence_required = r.read_byte();
         continue;
      }
      if (in_field_name == "PortalCooldown") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.portal_cooldown = r.read_int();
         continue;
      }
      if (in_field_name == "Pos") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<double> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_float64();
         });
         result.pos = std::move(list);
         continue;
      }
      if (in_field_name == "Rotation") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<float> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_float32();
         });
         result.rotation = std::move(list);
         continue;
      }
      if (in_field_name == "UUID") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::IntArray, tagid);
         result.uuid = r.read_int_vec();
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.id = r.read_str();
         continue;
      }
      if (in_field_name == "ignited") {
         ::minecpp::nbt::verify_tag("Entity", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.ignited = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Entity Entity::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Entity::deserialize_no_header(r);
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

void Heightmaps::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Heightmaps Heightmaps::deserialize_no_header(minecpp::nbt::Reader &r) {
   Heightmaps result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "MOTION_BLOCKING") {
         ::minecpp::nbt::verify_tag("Heightmaps", in_field_name, minecpp::nbt::TagId::LongArray, tagid);
         result.motion_blocking = r.read_long_vec();
         continue;
      }
      if (in_field_name == "MOTION_BLOCKING_NO_LEAVES") {
         ::minecpp::nbt::verify_tag("Heightmaps", in_field_name, minecpp::nbt::TagId::LongArray, tagid);
         result.motion_blocking_no_leaves = r.read_long_vec();
         continue;
      }
      if (in_field_name == "OCEAN_FLOOR") {
         ::minecpp::nbt::verify_tag("Heightmaps", in_field_name, minecpp::nbt::TagId::LongArray, tagid);
         result.ocean_floor = r.read_long_vec();
         continue;
      }
      if (in_field_name == "OCEAN_FLOOR_WG") {
         ::minecpp::nbt::verify_tag("Heightmaps", in_field_name, minecpp::nbt::TagId::LongArray, tagid);
         result.ocean_floor_wg = r.read_long_vec();
         continue;
      }
      if (in_field_name == "WORLD_SURFACE") {
         ::minecpp::nbt::verify_tag("Heightmaps", in_field_name, minecpp::nbt::TagId::LongArray, tagid);
         result.world_surface = r.read_long_vec();
         continue;
      }
      if (in_field_name == "WORLD_SURFACE_WG") {
         ::minecpp::nbt::verify_tag("Heightmaps", in_field_name, minecpp::nbt::TagId::LongArray, tagid);
         result.world_surface_wg = r.read_long_vec();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Heightmaps Heightmaps::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Heightmaps::deserialize_no_header(r);
}

void PaletteItem::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Compound, "Properties");
   minecpp::nbt::serialize_compound_content(w, properties);
   w.end_compound();
}

void PaletteItem::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

PaletteItem PaletteItem::deserialize_no_header(minecpp::nbt::Reader &r) {
   PaletteItem result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("PaletteItem", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "Properties") {
         ::minecpp::nbt::verify_tag("PaletteItem", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.properties = r.read_compound_content();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

PaletteItem PaletteItem::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return PaletteItem::deserialize_no_header(r);
}

void Section::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "Y");
   w.write_byte_content(static_cast<std::uint8_t>(y));
   w.write_header(minecpp::nbt::TagId::ByteArray, "BlockLight");
   w.write_bytes_content(block_light);
   w.write_header(minecpp::nbt::TagId::ByteArray, "SkyLight");
   w.write_bytes_content(sky_light);
   w.write_header(minecpp::nbt::TagId::LongArray, "BlockStates");
   w.write_longs_content(block_states);
   w.write_header(minecpp::nbt::TagId::List, "Palette");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, palette.size());
   for (const auto &list_item_0 : palette) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void Section::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Section Section::deserialize_no_header(minecpp::nbt::Reader &r) {
   Section result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Y") {
         ::minecpp::nbt::verify_tag("Section", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.y = r.read_byte();
         continue;
      }
      if (in_field_name == "BlockLight") {
         ::minecpp::nbt::verify_tag("Section", in_field_name, minecpp::nbt::TagId::ByteArray, tagid);
         result.block_light = r.read_byte_vector();
         continue;
      }
      if (in_field_name == "SkyLight") {
         ::minecpp::nbt::verify_tag("Section", in_field_name, minecpp::nbt::TagId::ByteArray, tagid);
         result.sky_light = r.read_byte_vector();
         continue;
      }
      if (in_field_name == "BlockStates") {
         ::minecpp::nbt::verify_tag("Section", in_field_name, minecpp::nbt::TagId::LongArray, tagid);
         result.block_states = r.read_long_vec();
         continue;
      }
      if (in_field_name == "Palette") {
         ::minecpp::nbt::verify_tag("Section", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<PaletteItem> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return PaletteItem::deserialize_no_header(r);
         });
         result.palette = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Section Section::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Section::deserialize_no_header(r);
}

void Start::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.end_compound();
}

void Start::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Start Start::deserialize_no_header(minecpp::nbt::Reader &r) {
   Start result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("Start", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.id = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Start Start::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Start::deserialize_no_header(r);
}

void Structures::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "Starts");
   for (const auto &[key_0, value_0] : starts) {
      w.write_header(minecpp::nbt::TagId::Compound, key_0);
      value_0.serialize_no_header(w);
   }
   w.end_compound();
   w.end_compound();
}

void Structures::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Structures Structures::deserialize_no_header(minecpp::nbt::Reader &r) {
   Structures result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Starts") {
         ::minecpp::nbt::verify_tag("Structures", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         std::map<std::string, Start> map_result;
         for (const auto &[tag_id, key] : r.iterate_compound()) {
            map_result[key] = Start::deserialize_no_header(r);
         }
         result.starts = std::move(map_result);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Structures Structures::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Structures::deserialize_no_header(r);
}

void CarvingMasks::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::ByteArray, "AIR");
   w.write_bytes_content(air);
   w.write_header(minecpp::nbt::TagId::ByteArray, "LIQUID");
   w.write_bytes_content(liquid);
   w.end_compound();
}

void CarvingMasks::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

CarvingMasks CarvingMasks::deserialize_no_header(minecpp::nbt::Reader &r) {
   CarvingMasks result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "AIR") {
         ::minecpp::nbt::verify_tag("CarvingMasks", in_field_name, minecpp::nbt::TagId::ByteArray, tagid);
         result.air = r.read_byte_vector();
         continue;
      }
      if (in_field_name == "LIQUID") {
         ::minecpp::nbt::verify_tag("CarvingMasks", in_field_name, minecpp::nbt::TagId::ByteArray, tagid);
         result.liquid = r.read_byte_vector();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

CarvingMasks CarvingMasks::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return CarvingMasks::deserialize_no_header(r);
}

void Level::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::IntArray, "Biomes");
   w.write_ints_content(biomes);
   w.write_header(minecpp::nbt::TagId::Compound, "CarvingMasks");
   carving_masks.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::List, "Entities");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, entities.size());
   for (const auto &list_item_0 : entities) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::Compound, "Heightmaps");
   heightmaps.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Long, "LastUpdate");
   w.write_long_content(last_update);
   w.write_header(minecpp::nbt::TagId::List, "Lights");
   w.begin_list_no_header(minecpp::nbt::TagId::List, lights.size());
   for (const auto &list_item_0 : lights) {
      w.begin_list_no_header(minecpp::nbt::TagId::Short, list_item_0.size());
      for (const auto &list_item_1 : list_item_0) {
         w.write_short_content(list_item_1);
      }
   }
   w.write_header(minecpp::nbt::TagId::Long, "InhabitedTime");
   w.write_long_content(inhabited_time);
   w.write_header(minecpp::nbt::TagId::List, "PostProcessing");
   w.begin_list_no_header(minecpp::nbt::TagId::List, post_processing.size());
   for (const auto &list_item_0 : post_processing) {
      w.begin_list_no_header(minecpp::nbt::TagId::Short, list_item_0.size());
      for (const auto &list_item_1 : list_item_0) {
         w.write_short_content(list_item_1);
      }
   }
   w.write_header(minecpp::nbt::TagId::List, "Sections");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, sections.size());
   for (const auto &list_item_0 : sections) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::String, "Status");
   w.write_string_content(status);
   w.write_header(minecpp::nbt::TagId::Compound, "Structures");
   structures.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "isLightOn");
   w.write_byte_content(static_cast<std::uint8_t>(is_light_on));
   w.write_header(minecpp::nbt::TagId::Int, "xPos");
   w.write_int_content(x_pos);
   w.write_header(minecpp::nbt::TagId::Int, "zPos");
   w.write_int_content(z_pos);
   w.end_compound();
}

void Level::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Level Level::deserialize_no_header(minecpp::nbt::Reader &r) {
   Level result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Biomes") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::IntArray, tagid);
         result.biomes = r.read_int_vec();
         continue;
      }
      if (in_field_name == "CarvingMasks") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.carving_masks = CarvingMasks::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "Entities") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<Entity> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return Entity::deserialize_no_header(r);
         });
         result.entities = std::move(list);
         continue;
      }
      if (in_field_name == "Heightmaps") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.heightmaps = Heightmaps::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "LastUpdate") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.last_update = r.read_long();
         continue;
      }
      if (in_field_name == "Lights") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::vector<std::int16_t>> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            auto list_info = r.peek_list();
            std::vector<std::int16_t> list(list_info.size);
            std::generate(list.begin(), list.end(), [&r]() {
               return r.read_short();
            });
            return list;
         });
         result.lights = std::move(list);
         continue;
      }
      if (in_field_name == "InhabitedTime") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.inhabited_time = r.read_long();
         continue;
      }
      if (in_field_name == "PostProcessing") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::vector<std::int16_t>> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            auto list_info = r.peek_list();
            std::vector<std::int16_t> list(list_info.size);
            std::generate(list.begin(), list.end(), [&r]() {
               return r.read_short();
            });
            return list;
         });
         result.post_processing = std::move(list);
         continue;
      }
      if (in_field_name == "Sections") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<Section> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return Section::deserialize_no_header(r);
         });
         result.sections = std::move(list);
         continue;
      }
      if (in_field_name == "Status") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.status = r.read_str();
         continue;
      }
      if (in_field_name == "Structures") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.structures = Structures::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "isLightOn") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_light_on = r.read_byte();
         continue;
      }
      if (in_field_name == "xPos") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.x_pos = r.read_int();
         continue;
      }
      if (in_field_name == "zPos") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.z_pos = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Level Level::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Level::deserialize_no_header(r);
}

void Chunk::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "DataVersion");
   w.write_int_content(version);
   w.write_header(minecpp::nbt::TagId::Compound, "Level");
   level.serialize_no_header(w);
   w.end_compound();
}

void Chunk::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Chunk Chunk::deserialize_no_header(minecpp::nbt::Reader &r) {
   Chunk result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "DataVersion") {
         ::minecpp::nbt::verify_tag("Chunk", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.version = r.read_int();
         continue;
      }
      if (in_field_name == "Level") {
         ::minecpp::nbt::verify_tag("Chunk", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.level = Level::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Chunk Chunk::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Chunk::deserialize_no_header(r);
}

}