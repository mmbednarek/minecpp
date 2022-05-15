#include <minecpp/nbt/chunk/v1/chunk.nbt.h>

namespace minecpp::nbt::chunk::v1 {

void ArmorItem::serialize_no_header(minecpp::nbt::Writer &w) const { w.end_compound(); }

void ArmorItem::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ArmorItem ArmorItem::deserialize_no_header(minecpp::nbt::Reader &r)
{
   ArmorItem res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      r.skip_payload(tagid);
   });
   return res;
}

ArmorItem ArmorItem::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return ArmorItem();
   }
   return ArmorItem::deserialize_no_header(r);
}

void Attribute::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::Double, "Base");
   w.write_double_content(base);
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.end_compound();
}

void Attribute::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Attribute Attribute::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Attribute res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String: res.__xx_put(name, r.read_str()); return;
      case minecpp::nbt::TagId::Double: res.__xx_put(name, r.read_float64()); return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Attribute Attribute::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Attribute();
   }
   return Attribute::deserialize_no_header(r);
}

void Memories::serialize_no_header(minecpp::nbt::Writer &w) const { w.end_compound(); }

void Memories::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Memories Memories::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Memories res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      r.skip_payload(tagid);
   });
   return res;
}

Memories Memories::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Memories();
   }
   return Memories::deserialize_no_header(r);
}

void Brain::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::Compound, "memories");
   memories.serialize_no_header(w);
   w.end_compound();
}

void Brain::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Brain Brain::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Brain res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         if (name == "memories") {
            res.__xx_put(name, Memories::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Brain Brain::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Brain();
   }
   return Brain::deserialize_no_header(r);
}

void HandItem::serialize_no_header(minecpp::nbt::Writer &w) const { w.end_compound(); }

void HandItem::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

HandItem HandItem::deserialize_no_header(minecpp::nbt::Reader &r)
{
   HandItem res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      r.skip_payload(tagid);
   });
   return res;
}

HandItem HandItem::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return HandItem();
   }
   return HandItem::deserialize_no_header(r);
}

void Entity::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::Float, "AbsorptionAmount");
   w.write_float_content(absorption_amount);
   w.write_header(minecpp::nbt::TagId::Short, "Air");
   w.write_short_content(air);
   w.write_header(minecpp::nbt::TagId::List, "ArmorDropChances");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, armor_drop_chances.size());
   std::for_each(armor_drop_chances.begin(), armor_drop_chances.end(),
                 [&w](const auto &value) { w.write_float_content(value); });
   w.write_header(minecpp::nbt::TagId::List, "ArmorItems");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, armor_items.size());
   std::for_each(armor_items.begin(), armor_items.end(),
                 [&w](const auto &value) { value.serialize_no_header(w); });
   w.write_header(minecpp::nbt::TagId::List, "Attributes");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, attributes.size());
   std::for_each(attributes.begin(), attributes.end(),
                 [&w](const auto &value) { value.serialize_no_header(w); });
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
   std::for_each(hand_drop_chances.begin(), hand_drop_chances.end(),
                 [&w](const auto &value) { w.write_float_content(value); });
   w.write_header(minecpp::nbt::TagId::List, "HandItems");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, hand_items.size());
   std::for_each(hand_items.begin(), hand_items.end(),
                 [&w](const auto &value) { value.serialize_no_header(w); });
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
   std::for_each(motion.begin(), motion.end(), [&w](const auto &value) { w.write_double_content(value); });
   w.write_header(minecpp::nbt::TagId::Byte, "OnGround");
   w.write_byte_content(on_ground);
   w.write_header(minecpp::nbt::TagId::Byte, "PersistenceRequired");
   w.write_byte_content(persistence_required);
   w.write_header(minecpp::nbt::TagId::Int, "PortalCooldown");
   w.write_int_content(portal_cooldown);
   w.write_header(minecpp::nbt::TagId::List, "Pos");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, pos.size());
   std::for_each(pos.begin(), pos.end(), [&w](const auto &value) { w.write_double_content(value); });
   w.write_header(minecpp::nbt::TagId::List, "Rotation");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, rotation.size());
   std::for_each(rotation.begin(), rotation.end(), [&w](const auto &value) { w.write_float_content(value); });
   w.write_header(minecpp::nbt::TagId::IntArray, "UUID");
   w.write_ints_content(uuid);
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.write_header(minecpp::nbt::TagId::Byte, "ignited");
   w.write_byte_content(ignited);
   w.end_compound();
}

void Entity::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Entity Entity::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Entity res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte: res.__xx_put(name, r.read_byte()); return;
      case minecpp::nbt::TagId::Short: res.__xx_put(name, r.read_short()); return;
      case minecpp::nbt::TagId::Int: res.__xx_put(name, r.read_int()); return;
      case minecpp::nbt::TagId::String: res.__xx_put(name, r.read_str()); return;
      case minecpp::nbt::TagId::Float: res.__xx_put(name, r.read_float32()); return;
      case minecpp::nbt::TagId::IntArray: res.__xx_put(name, r.read_int_vec()); return;
      case minecpp::nbt::TagId::Compound:
         if (name == "Brain") {
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
               std::generate(ls.begin(), ls.end(), [&r]() { return r.read_float32(); });
               res.__xx_put(name, ls);
               return;
            }
            case minecpp::nbt::TagId::Double: {
               std::vector<double> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() { return r.read_float64(); });
               res.__xx_put(name, ls);
               return;
            }
            case minecpp::nbt::TagId::Compound: {
               if (name == "ArmorItems") {
                  std::vector<ArmorItem> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() { return ArmorItem::deserialize_no_header(r); });
                  res.__xx_put(name, ls);
                  return;
               }
               if (name == "Attributes") {
                  std::vector<Attribute> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() { return Attribute::deserialize_no_header(r); });
                  res.__xx_put(name, ls);
                  return;
               }
               if (name == "HandItems") {
                  std::vector<HandItem> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() { return HandItem::deserialize_no_header(r); });
                  res.__xx_put(name, ls);
                  return;
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

Entity Entity::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Entity();
   }
   return Entity::deserialize_no_header(r);
}

void Heightmaps::serialize_no_header(minecpp::nbt::Writer &w) const
{
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

void Heightmaps::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Heightmaps Heightmaps::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Heightmaps res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::LongArray: res.__xx_put(name, r.read_long_vec()); return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Heightmaps Heightmaps::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Heightmaps();
   }
   return Heightmaps::deserialize_no_header(r);
}

void PaletteItem::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Compound, "Properties");
   minecpp::nbt::serialize_compound_content(w, properties);
   w.end_compound();
}

void PaletteItem::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

PaletteItem PaletteItem::deserialize_no_header(minecpp::nbt::Reader &r)
{
   PaletteItem res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String: res.__xx_put(name, r.read_str()); return;
      case minecpp::nbt::TagId::Compound:
         if (name == "Properties") {
            res.__xx_put(name, r.read_compound_content());
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

PaletteItem PaletteItem::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return PaletteItem();
   }
   return PaletteItem::deserialize_no_header(r);
}

void Section::serialize_no_header(minecpp::nbt::Writer &w) const
{
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
   std::for_each(palette.begin(), palette.end(), [&w](const auto &value) { value.serialize_no_header(w); });
   w.end_compound();
}

void Section::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Section Section::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Section res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte: res.__xx_put(name, r.read_byte()); return;
      case minecpp::nbt::TagId::ByteArray: res.__xx_put(name, r.read_byte_vector()); return;
      case minecpp::nbt::TagId::LongArray: res.__xx_put(name, r.read_long_vec()); return;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               if (name == "Palette") {
                  std::vector<PaletteItem> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(),
                                [&r]() { return PaletteItem::deserialize_no_header(r); });
                  res.__xx_put(name, ls);
                  return;
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

Section Section::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Section();
   }
   return Section::deserialize_no_header(r);
}

void Start::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.end_compound();
}

void Start::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Start Start::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Start res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String: res.__xx_put(name, r.read_str()); return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Start Start::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Start();
   }
   return Start::deserialize_no_header(r);
}

void Structures::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::Compound, "Starts");
   std::for_each(starts.begin(), starts.end(), [&w](const auto &pair) {
      w.write_header(minecpp::nbt::TagId::Compound, pair.first);
      pair.second.serialize_no_header(w);
   });
   w.end_compound();
   w.end_compound();
}

void Structures::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Structures Structures::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Structures res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         if (name == "Starts") {
            r.read_compound(
                    [&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
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

Structures Structures::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Structures();
   }
   return Structures::deserialize_no_header(r);
}

void CarvingMasks::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::ByteArray, "AIR");
   w.write_bytes_content(air);
   w.write_header(minecpp::nbt::TagId::ByteArray, "LIQUID");
   w.write_bytes_content(liquid);
   w.end_compound();
}

void CarvingMasks::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

CarvingMasks CarvingMasks::deserialize_no_header(minecpp::nbt::Reader &r)
{
   CarvingMasks res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::ByteArray: res.__xx_put(name, r.read_byte_vector()); return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

CarvingMasks CarvingMasks::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return CarvingMasks();
   }
   return CarvingMasks::deserialize_no_header(r);
}

void Level::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::IntArray, "Biomes");
   w.write_ints_content(biomes);
   w.write_header(minecpp::nbt::TagId::Compound, "CarvingMasks");
   carving_masks.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::List, "Entities");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, entities.size());
   std::for_each(entities.begin(), entities.end(), [&w](const auto &value) { value.serialize_no_header(w); });
   w.write_header(minecpp::nbt::TagId::Compound, "Heightmaps");
   heightmaps.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Long, "LastUpdate");
   w.write_long_content(last_update);
   w.write_header(minecpp::nbt::TagId::List, "Lights");
   w.begin_list_no_header(minecpp::nbt::TagId::List, lights.size());
   std::for_each(lights.begin(), lights.end(), [&w](const auto &value) {
      w.begin_list_no_header(minecpp::nbt::TagId::Short, value.size());
      std::for_each(value.begin(), value.end(), [&w](const auto &value) { w.write_short_content(value); });
   });
   w.write_header(minecpp::nbt::TagId::Long, "InhabitedTime");
   w.write_long_content(inhabited_time);
   w.write_header(minecpp::nbt::TagId::List, "PostProcessing");
   w.begin_list_no_header(minecpp::nbt::TagId::List, post_processing.size());
   std::for_each(post_processing.begin(), post_processing.end(), [&w](const auto &value) {
      w.begin_list_no_header(minecpp::nbt::TagId::Short, value.size());
      std::for_each(value.begin(), value.end(), [&w](const auto &value) { w.write_short_content(value); });
   });
   w.write_header(minecpp::nbt::TagId::List, "Sections");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, sections.size());
   std::for_each(sections.begin(), sections.end(), [&w](const auto &value) { value.serialize_no_header(w); });
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

void Level::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Level Level::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Level res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte: res.__xx_put(name, r.read_byte()); return;
      case minecpp::nbt::TagId::Int: res.__xx_put(name, r.read_int()); return;
      case minecpp::nbt::TagId::Long: res.__xx_put(name, r.read_long()); return;
      case minecpp::nbt::TagId::String: res.__xx_put(name, r.read_str()); return;
      case minecpp::nbt::TagId::IntArray: res.__xx_put(name, r.read_int_vec()); return;
      case minecpp::nbt::TagId::Compound:
         if (name == "CarvingMasks") {
            res.__xx_put(name, CarvingMasks::deserialize_no_header(r));
            return;
         }
         if (name == "Heightmaps") {
            res.__xx_put(name, Heightmaps::deserialize_no_header(r));
            return;
         }
         if (name == "Structures") {
            res.__xx_put(name, Structures::deserialize_no_header(r));
            return;
         }
         break;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               if (name == "Entities") {
                  std::vector<Entity> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() { return Entity::deserialize_no_header(r); });
                  res.__xx_put(name, ls);
                  return;
               }
               if (name == "Sections") {
                  std::vector<Section> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() { return Section::deserialize_no_header(r); });
                  res.__xx_put(name, ls);
                  return;
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
                        *it     = [&r, &list_info1]() {
                           std::vector<std::int16_t> ls(list_info1.size);
                           std::generate(ls.begin(), ls.end(), [&r]() { return r.read_short(); });
                           return ls;
                        }();
                        std::generate(it + 1, ls.end(), [&r]() {
                           auto list_info1 = r.peek_list();
                           std::vector<std::int16_t> ls(list_info1.size);
                           std::generate(ls.begin(), ls.end(), [&r]() { return r.read_short(); });
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

Level Level::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Level();
   }
   return Level::deserialize_no_header(r);
}

void Chunk::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::Int, "DataVersion");
   w.write_int_content(version);
   w.write_header(minecpp::nbt::TagId::Compound, "Level");
   level.serialize_no_header(w);
   w.end_compound();
}

void Chunk::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Chunk Chunk::deserialize_no_header(minecpp::nbt::Reader &r)
{
   Chunk res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int: res.__xx_put(name, r.read_int()); return;
      case minecpp::nbt::TagId::Compound:
         if (name == "Level") {
            res.__xx_put(name, Level::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Chunk Chunk::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Chunk();
   }
   return Chunk::deserialize_no_header(r);
}

}// namespace minecpp::nbt::chunk::v1