// Generated using ProtoNBT generator
#include "chunk.h"

namespace Game::NbtChunk {

int ArmorItem::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void ArmorItem::serialize_no_header(NBT::Writer &w) const {
   w.end_compound();
}

void ArmorItem::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> ArmorItem::__xx_offsets {
};

ArmorItem ArmorItem::deserialize_no_header(NBT::Reader &r) {
   ArmorItem res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      }
      r.skip_payload(tagid);
   });

   return res;
}

ArmorItem ArmorItem::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return ArmorItem();
   }
   return ArmorItem::deserialize_no_header(r);
}

int Attribute::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Attribute::serialize_no_header(NBT::Writer &w) const {
   w.write_double("Base", base);
   w.write_string("Name", this->name);
   w.end_compound();
}

void Attribute::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Attribute::__xx_offsets {
   {"Base", {offsetof(Attribute, base), sizeof(Attribute::base), 1}},
   {"Name", {offsetof(Attribute, name), sizeof(Attribute::name), 2}},
};

Attribute Attribute::deserialize_no_header(NBT::Reader &r) {
   Attribute res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::Double: 
         res.__xx_put(name, r.read_float64());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

Attribute Attribute::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Attribute();
   }
   return Attribute::deserialize_no_header(r);
}

int Memories::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Memories::serialize_no_header(NBT::Writer &w) const {
   w.end_compound();
}

void Memories::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Memories::__xx_offsets {
};

Memories Memories::deserialize_no_header(NBT::Reader &r) {
   Memories res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      }
      r.skip_payload(tagid);
   });

   return res;
}

Memories Memories::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Memories();
   }
   return Memories::deserialize_no_header(r);
}

int Brain::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Brain::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("memories");
   this->memories.serialize_no_header(w);
   w.end_compound();
}

void Brain::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Brain::__xx_offsets {
   {"memories", {offsetof(Brain, memories), sizeof(Brain::memories), 1}},
};

Brain Brain::deserialize_no_header(NBT::Reader &r) {
   Brain res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 1:
               res.__xx_put(name, Memories::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Brain Brain::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Brain();
   }
   return Brain::deserialize_no_header(r);
}

int HandItem::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void HandItem::serialize_no_header(NBT::Writer &w) const {
   w.end_compound();
}

void HandItem::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> HandItem::__xx_offsets {
};

HandItem HandItem::deserialize_no_header(NBT::Reader &r) {
   HandItem res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      }
      r.skip_payload(tagid);
   });

   return res;
}

HandItem HandItem::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return HandItem();
   }
   return HandItem::deserialize_no_header(r);
}

int Entity::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Entity::serialize_no_header(NBT::Writer &w) const {
   w.write_float("AbsorptionAmount", this->absorption_amount);
   w.write_short("Air", this->air);
   w.begin_list("ArmorDropChances", NBT::TagId::Float, armor_drop_chances.size());
   for (const auto &val0 : armor_drop_chances) {
      w.write_float_content(val0);
   }
   w.begin_list("ArmorItems", NBT::TagId::Compound, armor_items.size());
   for (const auto &val0 : armor_items) {
      val0.serialize_no_header(w);
   }
   w.begin_list("Attributes", NBT::TagId::Compound, attributes.size());
   for (const auto &val0 : attributes) {
      val0.serialize_no_header(w);
   }
   w.begin_compound("Brain");
   this->brain.serialize_no_header(w);
   w.write_byte("CanPickUpLoot", this->can_pick_up_loot);
   w.write_short("DeathTime", this->death_time);
   w.write_byte("ExplosionRadius", this->explosion_radius);
   w.write_float("FallDistance", this->fall_distance);
   w.write_byte("FallFlying", this->fall_flying);
   w.write_short("Fire", this->fire);
   w.write_short("Fuse", this->fuse);
   w.begin_list("HandDropChances", NBT::TagId::Float, hand_drop_chances.size());
   for (const auto &val0 : hand_drop_chances) {
      w.write_float_content(val0);
   }
   w.begin_list("HandItems", NBT::TagId::Compound, hand_items.size());
   for (const auto &val0 : hand_items) {
      val0.serialize_no_header(w);
   }
   w.write_float("Health", this->health);
   w.write_int("HurtByTimestamp", this->hurt_by_timestamp);
   w.write_short("HurtTime", this->hurt_time);
   w.write_byte("Invulnerable", this->invulnerable);
   w.write_byte("LeftHanded", this->left_handed);
   w.begin_list("Motion", NBT::TagId::Double, motion.size());
   for (const auto &val0 : motion) {
      w.write_double_content(val0);
   }
   w.write_byte("OnGround", this->on_ground);
   w.write_byte("PersistenceRequired", this->persistence_required);
   w.write_int("PortalCooldown", this->portal_cooldown);
   w.begin_list("Pos", NBT::TagId::Double, pos.size());
   for (const auto &val0 : pos) {
      w.write_double_content(val0);
   }
   w.begin_list("Rotation", NBT::TagId::Float, rotation.size());
   for (const auto &val0 : rotation) {
      w.write_float_content(val0);
   }
   w.write_ints("UUID", uuid);
   w.write_string("id", this->id);
   w.write_byte("ignited", this->ignited);
   w.end_compound();
}

void Entity::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Entity::__xx_offsets {
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

Entity Entity::deserialize_no_header(NBT::Reader &r) {
   Entity res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::Short: 
         res.__xx_put(name, r.read_short());
         return;
      case NBT::TagId::Int: 
         res.__xx_put(name, r.read_int());
         return;
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::Float: 
         res.__xx_put(name, r.read_float32());
         return;
      case NBT::TagId::IntArray: 
         res.__xx_put(name, r.read_int_vec());
         return;
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 6:
               res.__xx_put(name, Brain::deserialize_no_header(r));
               return;
         }
         break;
      }
      case NBT::TagId::List: {
         auto list_info0 = r.peek_list();
         switch (list_info0.tagid) {
         case NBT::TagId::Float: {
            std::vector<float> ls(list_info0.size);
            std::generate(ls.begin(), ls.end(), [&r]() { return r.read_float32(); });
            res.__xx_put(name, ls);
            return;
         }
         case NBT::TagId::Double: {
            std::vector<double> ls(list_info0.size);
            std::generate(ls.begin(), ls.end(), [&r]() { return r.read_float64(); });
            res.__xx_put(name, ls);
            return;
         }
         case NBT::TagId::Compound: {
            switch(res.__xx_get_id(name)) {
            case 4: {
               std::vector<ArmorItem> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() { return ArmorItem::deserialize_no_header(r); });
               res.__xx_put(name, ls);
               return;
            }
            case 5: {
               std::vector<Attribute> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() { return Attribute::deserialize_no_header(r); });
               res.__xx_put(name, ls);
               return;
            }
            case 15: {
               std::vector<HandItem> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() { return HandItem::deserialize_no_header(r); });
               res.__xx_put(name, ls);
               return;
            }
            }
            break;
         }
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Entity Entity::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Entity();
   }
   return Entity::deserialize_no_header(r);
}

int Heightmaps::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Heightmaps::serialize_no_header(NBT::Writer &w) const {
   w.write_longs("MOTION_BLOCKING", motion_blocking);
   w.write_longs("MOTION_BLOCKING_NO_LEAVES", motion_blocking_no_leaves);
   w.write_longs("OCEAN_FLOOR", ocean_floor);
   w.write_longs("WORLD_SURFACE", world_surface);
   w.end_compound();
}

void Heightmaps::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Heightmaps::__xx_offsets {
   {"MOTION_BLOCKING", {offsetof(Heightmaps, motion_blocking), sizeof(Heightmaps::motion_blocking), 1}},
   {"MOTION_BLOCKING_NO_LEAVES", {offsetof(Heightmaps, motion_blocking_no_leaves), sizeof(Heightmaps::motion_blocking_no_leaves), 2}},
   {"OCEAN_FLOOR", {offsetof(Heightmaps, ocean_floor), sizeof(Heightmaps::ocean_floor), 3}},
   {"WORLD_SURFACE", {offsetof(Heightmaps, world_surface), sizeof(Heightmaps::world_surface), 4}},
};

Heightmaps Heightmaps::deserialize_no_header(NBT::Reader &r) {
   Heightmaps res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::LongArray: 
         res.__xx_put(name, r.read_long_vec());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

Heightmaps Heightmaps::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Heightmaps();
   }
   return Heightmaps::deserialize_no_header(r);
}

int PaletteItem::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void PaletteItem::serialize_no_header(NBT::Writer &w) const {
   w.write_string("Name", this->name);
   w.begin_compound("Properties");
   this->properties.serialize_no_header(w);
   w.end_compound();
}

void PaletteItem::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> PaletteItem::__xx_offsets {
   {"Name", {offsetof(PaletteItem, name), sizeof(PaletteItem::name), 1}},
   {"Properties", {offsetof(PaletteItem, properties), sizeof(PaletteItem::properties), 2}},
};

PaletteItem PaletteItem::deserialize_no_header(NBT::Reader &r) {
   PaletteItem res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 2:
               res.__xx_put(name, map::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

PaletteItem PaletteItem::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return PaletteItem();
   }
   return PaletteItem::deserialize_no_header(r);
}

int Section::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Section::serialize_no_header(NBT::Writer &w) const {
   w.write_byte("Y", this->y);
   w.write_bytes("BlockLight", block_light);
   w.write_bytes("SkyLight", sky_light);
   w.write_longs("BlockStates", block_states);
   w.begin_list("Palette", NBT::TagId::Compound, palette.size());
   for (const auto &val0 : palette) {
      val0.serialize_no_header(w);
   }
   w.end_compound();
}

void Section::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Section::__xx_offsets {
   {"Y", {offsetof(Section, y), sizeof(Section::y), 1}},
   {"BlockLight", {offsetof(Section, block_light), sizeof(Section::block_light), 2}},
   {"SkyLight", {offsetof(Section, sky_light), sizeof(Section::sky_light), 3}},
   {"BlockStates", {offsetof(Section, block_states), sizeof(Section::block_states), 4}},
   {"Palette", {offsetof(Section, palette), sizeof(Section::palette), 5}},
};

Section Section::deserialize_no_header(NBT::Reader &r) {
   Section res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::ByteArray: 
         res.__xx_put(name, r.read_byte_vector());
         return;
      case NBT::TagId::LongArray: 
         res.__xx_put(name, r.read_long_vec());
         return;
      case NBT::TagId::List: {
         auto list_info0 = r.peek_list();
         switch (list_info0.tagid) {
         case NBT::TagId::Compound: {
            switch(res.__xx_get_id(name)) {
            case 5: {
               std::vector<PaletteItem> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() { return PaletteItem::deserialize_no_header(r); });
               res.__xx_put(name, ls);
               return;
            }
            }
            break;
         }
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Section Section::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Section();
   }
   return Section::deserialize_no_header(r);
}

int References::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void References::serialize_no_header(NBT::Writer &w) const {
   w.write_longs("bastion_remnant", bastion_remnant);
   w.write_longs("buried_treasure", buried_treasure);
   w.write_longs("desert_pyramid", desert_pyramid);
   w.write_longs("fortress", fortress);
   w.write_longs("jungle_pyramid", jungle_pyramid);
   w.write_longs("mineshaft", mineshaft);
   w.write_longs("monument", monument);
   w.write_longs("nether_fossil", nether_fossil);
   w.write_longs("ocean_ruin", ocean_ruin);
   w.write_longs("pillager_outpost", pillager_outpost);
   w.write_longs("shipwreck", shipwreck);
   w.write_longs("swamp_hut", swamp_hut);
   w.end_compound();
}

void References::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> References::__xx_offsets {
   {"bastion_remnant", {offsetof(References, bastion_remnant), sizeof(References::bastion_remnant), 1}},
   {"buried_treasure", {offsetof(References, buried_treasure), sizeof(References::buried_treasure), 2}},
   {"desert_pyramid", {offsetof(References, desert_pyramid), sizeof(References::desert_pyramid), 3}},
   {"fortress", {offsetof(References, fortress), sizeof(References::fortress), 4}},
   {"jungle_pyramid", {offsetof(References, jungle_pyramid), sizeof(References::jungle_pyramid), 5}},
   {"mineshaft", {offsetof(References, mineshaft), sizeof(References::mineshaft), 6}},
   {"monument", {offsetof(References, monument), sizeof(References::monument), 7}},
   {"nether_fossil", {offsetof(References, nether_fossil), sizeof(References::nether_fossil), 8}},
   {"ocean_ruin", {offsetof(References, ocean_ruin), sizeof(References::ocean_ruin), 9}},
   {"pillager_outpost", {offsetof(References, pillager_outpost), sizeof(References::pillager_outpost), 10}},
   {"shipwreck", {offsetof(References, shipwreck), sizeof(References::shipwreck), 11}},
   {"swamp_hut", {offsetof(References, swamp_hut), sizeof(References::swamp_hut), 12}},
};

References References::deserialize_no_header(NBT::Reader &r) {
   References res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::LongArray: 
         res.__xx_put(name, r.read_long_vec());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

References References::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return References();
   }
   return References::deserialize_no_header(r);
}

int StartId::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void StartId::serialize_no_header(NBT::Writer &w) const {
   w.write_string("id", this->id);
   w.end_compound();
}

void StartId::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> StartId::__xx_offsets {
   {"id", {offsetof(StartId, id), sizeof(StartId::id), 1}},
};

StartId StartId::deserialize_no_header(NBT::Reader &r) {
   StartId res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

StartId StartId::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return StartId();
   }
   return StartId::deserialize_no_header(r);
}

int Starts::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Starts::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("mineshaft");
   this->mineshaft.serialize_no_header(w);
   w.begin_compound("ruined_portal");
   this->ruined_portal.serialize_no_header(w);
   w.begin_compound("stronghold");
   this->stronghold.serialize_no_header(w);
   w.end_compound();
}

void Starts::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Starts::__xx_offsets {
   {"mineshaft", {offsetof(Starts, mineshaft), sizeof(Starts::mineshaft), 1}},
   {"ruined_portal", {offsetof(Starts, ruined_portal), sizeof(Starts::ruined_portal), 2}},
   {"stronghold", {offsetof(Starts, stronghold), sizeof(Starts::stronghold), 3}},
};

Starts Starts::deserialize_no_header(NBT::Reader &r) {
   Starts res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 1:
               res.__xx_put(name, StartId::deserialize_no_header(r));
               return;
            case 2:
               res.__xx_put(name, StartId::deserialize_no_header(r));
               return;
            case 3:
               res.__xx_put(name, StartId::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Starts Starts::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Starts();
   }
   return Starts::deserialize_no_header(r);
}

int Structures::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Structures::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("References");
   this->references.serialize_no_header(w);
   w.begin_compound("Starts");
   this->starts.serialize_no_header(w);
   w.end_compound();
}

void Structures::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Structures::__xx_offsets {
   {"References", {offsetof(Structures, references), sizeof(Structures::references), 1}},
   {"Starts", {offsetof(Structures, starts), sizeof(Structures::starts), 2}},
};

Structures Structures::deserialize_no_header(NBT::Reader &r) {
   Structures res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 1:
               res.__xx_put(name, References::deserialize_no_header(r));
               return;
            case 2:
               res.__xx_put(name, Starts::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Structures Structures::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Structures();
   }
   return Structures::deserialize_no_header(r);
}

int Level::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Level::serialize_no_header(NBT::Writer &w) const {
   w.write_ints("Biomes", biomes);
   w.begin_list("Entities", NBT::TagId::Compound, entities.size());
   for (const auto &val0 : entities) {
      val0.serialize_no_header(w);
   }
   w.begin_compound("Heightmaps");
   this->heightmaps.serialize_no_header(w);
   w.write_long("InhabitedTime", this->inhabited_time);
   w.write_long("LastUpdate", this->last_update);
   w.begin_list("Sections", NBT::TagId::Compound, sections.size());
   for (const auto &val0 : sections) {
      val0.serialize_no_header(w);
   }
   w.write_string("Status", this->status);
   w.begin_compound("Structures");
   this->structures.serialize_no_header(w);
   w.write_byte("isLightOn", this->is_light_on);
   w.write_int("xPos", this->x_pos);
   w.write_int("zPos", this->z_pos);
   w.end_compound();
}

void Level::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Level::__xx_offsets {
   {"Biomes", {offsetof(Level, biomes), sizeof(Level::biomes), 1}},
   {"Entities", {offsetof(Level, entities), sizeof(Level::entities), 2}},
   {"Heightmaps", {offsetof(Level, heightmaps), sizeof(Level::heightmaps), 3}},
   {"InhabitedTime", {offsetof(Level, inhabited_time), sizeof(Level::inhabited_time), 4}},
   {"LastUpdate", {offsetof(Level, last_update), sizeof(Level::last_update), 5}},
   {"Sections", {offsetof(Level, sections), sizeof(Level::sections), 7}},
   {"Status", {offsetof(Level, status), sizeof(Level::status), 8}},
   {"Structures", {offsetof(Level, structures), sizeof(Level::structures), 9}},
   {"isLightOn", {offsetof(Level, is_light_on), sizeof(Level::is_light_on), 12}},
   {"xPos", {offsetof(Level, x_pos), sizeof(Level::x_pos), 13}},
   {"zPos", {offsetof(Level, z_pos), sizeof(Level::z_pos), 14}},
};

Level Level::deserialize_no_header(NBT::Reader &r) {
   Level res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::Int: 
         res.__xx_put(name, r.read_int());
         return;
      case NBT::TagId::Long: 
         res.__xx_put(name, r.read_long());
         return;
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::IntArray: 
         res.__xx_put(name, r.read_int_vec());
         return;
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 3:
               res.__xx_put(name, Heightmaps::deserialize_no_header(r));
               return;
            case 9:
               res.__xx_put(name, Structures::deserialize_no_header(r));
               return;
         }
         break;
      }
      case NBT::TagId::List: {
         auto list_info0 = r.peek_list();
         switch (list_info0.tagid) {
         case NBT::TagId::Compound: {
            switch(res.__xx_get_id(name)) {
            case 2: {
               std::vector<Entity> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() { return Entity::deserialize_no_header(r); });
               res.__xx_put(name, ls);
               return;
            }
            case 7: {
               std::vector<Section> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() { return Section::deserialize_no_header(r); });
               res.__xx_put(name, ls);
               return;
            }
            }
            break;
         }
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Level Level::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Level();
   }
   return Level::deserialize_no_header(r);
}

int Chunk::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Chunk::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("Level");
   this->level.serialize_no_header(w);
   w.end_compound();
}

void Chunk::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Chunk::__xx_offsets {
   {"Level", {offsetof(Chunk, level), sizeof(Chunk::level), 1}},
};

Chunk Chunk::deserialize_no_header(NBT::Reader &r) {
   Chunk res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 1:
               res.__xx_put(name, Level::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Chunk Chunk::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Chunk();
   }
   return Chunk::deserialize_no_header(r);
}

}// namespace Game::NbtChunk
