#ifndef MINECPP_NBT_CHUNK_V1_CHUNK_H
#define MINECPP_NBT_CHUNK_V1_CHUNK_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::chunk::v1 {

class ArmorItem
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "no_empty") {
            this->no_empty = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::int32_t no_empty{};
   ArmorItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ArmorItem deserialize_no_header(minecpp::nbt::Reader &r);
   static ArmorItem deserialize(std::istream &in);
};

class Attribute
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, double>) {
         if (in_field_name == "Base") {
            this->base = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "Name") {
            this->name = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   double base{};
   std::string name{};
   Attribute() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Attribute deserialize_no_header(minecpp::nbt::Reader &r);
   static Attribute deserialize(std::istream &in);
};

class Memories
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "no_empty") {
            this->no_empty = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::int32_t no_empty{};
   Memories() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Memories deserialize_no_header(minecpp::nbt::Reader &r);
   static Memories deserialize(std::istream &in);
};

class Brain
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, Memories>) {
         if (in_field_name == "memories") {
            this->memories = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   Memories memories{};
   Brain() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Brain deserialize_no_header(minecpp::nbt::Reader &r);
   static Brain deserialize(std::istream &in);
};

class HandItem
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "no_empty") {
            this->no_empty = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::int32_t no_empty{};
   HandItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static HandItem deserialize_no_header(minecpp::nbt::Reader &r);
   static HandItem deserialize(std::istream &in);
};

class Entity
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, Brain>) {
         if (in_field_name == "Brain") {
            this->brain = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, float>) {
         if (in_field_name == "AbsorptionAmount") {
            this->absorption_amount = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "FallDistance") {
            this->fall_distance = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Health") {
            this->health = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int16_t>) {
         if (in_field_name == "Air") {
            this->air = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "DeathTime") {
            this->death_time = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Fire") {
            this->fire = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Fuse") {
            this->fuse = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "HurtTime") {
            this->hurt_time = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "HurtByTimestamp") {
            this->hurt_by_timestamp = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "PortalCooldown") {
            this->portal_cooldown = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "CanPickUpLoot") {
            this->can_pick_up_loot = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "ExplosionRadius") {
            this->explosion_radius = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "FallFlying") {
            this->fall_flying = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Invulnerable") {
            this->invulnerable = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "LeftHanded") {
            this->left_handed = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "OnGround") {
            this->on_ground = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "PersistenceRequired") {
            this->persistence_required = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "ignited") {
            this->ignited = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "id") {
            this->id = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<ArmorItem>>) {
         if (in_field_name == "ArmorItems") {
            this->armor_items = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<Attribute>>) {
         if (in_field_name == "Attributes") {
            this->attributes = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<HandItem>>) {
         if (in_field_name == "HandItems") {
            this->hand_items = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<double>>) {
         if (in_field_name == "Motion") {
            this->motion = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Pos") {
            this->pos = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<float>>) {
         if (in_field_name == "ArmorDropChances") {
            this->armor_drop_chances = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "HandDropChances") {
            this->hand_drop_chances = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Rotation") {
            this->rotation = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::int32_t>>) {
         if (in_field_name == "UUID") {
            this->uuid = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   float absorption_amount{};
   std::int16_t air{};
   std::vector<float> armor_drop_chances{};
   std::vector<ArmorItem> armor_items{};
   std::vector<Attribute> attributes{};
   Brain brain{};
   std::int8_t can_pick_up_loot{};
   std::int16_t death_time{};
   std::int8_t explosion_radius{};
   float fall_distance{};
   std::int8_t fall_flying{};
   std::int16_t fire{};
   std::int16_t fuse{};
   std::vector<float> hand_drop_chances{};
   std::vector<HandItem> hand_items{};
   float health{};
   std::int32_t hurt_by_timestamp{};
   std::int16_t hurt_time{};
   std::int8_t invulnerable{};
   std::int8_t left_handed{};
   std::vector<double> motion{};
   std::int8_t on_ground{};
   std::int8_t persistence_required{};
   std::int32_t portal_cooldown{};
   std::vector<double> pos{};
   std::vector<float> rotation{};
   std::vector<std::int32_t> uuid{};
   std::string id{};
   std::int8_t ignited{};
   Entity() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Entity deserialize_no_header(minecpp::nbt::Reader &r);
   static Entity deserialize(std::istream &in);
};

class Heightmaps
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::vector<std::int64_t>>) {
         if (in_field_name == "MOTION_BLOCKING") {
            this->motion_blocking = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "MOTION_BLOCKING_NO_LEAVES") {
            this->motion_blocking_no_leaves = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "OCEAN_FLOOR") {
            this->ocean_floor = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "OCEAN_FLOOR_WG") {
            this->ocean_floor_wg = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "WORLD_SURFACE") {
            this->world_surface = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "WORLD_SURFACE_WG") {
            this->world_surface_wg = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<std::int64_t> motion_blocking{};
   std::vector<std::int64_t> motion_blocking_no_leaves{};
   std::vector<std::int64_t> ocean_floor{};
   std::vector<std::int64_t> ocean_floor_wg{};
   std::vector<std::int64_t> world_surface{};
   std::vector<std::int64_t> world_surface_wg{};
   Heightmaps() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Heightmaps deserialize_no_header(minecpp::nbt::Reader &r);
   static Heightmaps deserialize(std::istream &in);
};

class PaletteItem
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, minecpp::nbt::CompoundContent>) {
         if (in_field_name == "Properties") {
            this->properties = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "Name") {
            this->name = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   minecpp::nbt::CompoundContent properties{};
   PaletteItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static PaletteItem deserialize_no_header(minecpp::nbt::Reader &r);
   static PaletteItem deserialize(std::istream &in);
};

class Section
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "Y") {
            this->y = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<PaletteItem>>) {
         if (in_field_name == "Palette") {
            this->palette = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::int64_t>>) {
         if (in_field_name == "BlockStates") {
            this->block_states = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::uint8_t>>) {
         if (in_field_name == "BlockLight") {
            this->block_light = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SkyLight") {
            this->sky_light = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t y{};
   std::vector<std::uint8_t> block_light{};
   std::vector<std::uint8_t> sky_light{};
   std::vector<std::int64_t> block_states{};
   std::vector<PaletteItem> palette{};
   Section() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Section deserialize_no_header(minecpp::nbt::Reader &r);
   static Section deserialize(std::istream &in);
};

class Start
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "id") {
            this->id = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::string id{};
   Start() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Start deserialize_no_header(minecpp::nbt::Reader &r);
   static Start deserialize(std::istream &in);
};

class Structures
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::map<std::string, Start>>) {
         if (in_field_name == "Starts") {
            this->starts = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::map<std::string, Start> starts{};
   Structures() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Structures deserialize_no_header(minecpp::nbt::Reader &r);
   static Structures deserialize(std::istream &in);
};

class CarvingMasks
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::vector<std::uint8_t>>) {
         if (in_field_name == "AIR") {
            this->air = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "LIQUID") {
            this->liquid = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<std::uint8_t> air{};
   std::vector<std::uint8_t> liquid{};
   CarvingMasks() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static CarvingMasks deserialize_no_header(minecpp::nbt::Reader &r);
   static CarvingMasks deserialize(std::istream &in);
};

class Level
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, CarvingMasks>) {
         if (in_field_name == "CarvingMasks") {
            this->carving_masks = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, Heightmaps>) {
         if (in_field_name == "Heightmaps") {
            this->heightmaps = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, Structures>) {
         if (in_field_name == "Structures") {
            this->structures = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "xPos") {
            this->x_pos = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "zPos") {
            this->z_pos = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int64_t>) {
         if (in_field_name == "LastUpdate") {
            this->last_update = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "InhabitedTime") {
            this->inhabited_time = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "isLightOn") {
            this->is_light_on = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "Status") {
            this->status = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<Entity>>) {
         if (in_field_name == "Entities") {
            this->entities = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<Section>>) {
         if (in_field_name == "Sections") {
            this->sections = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::int32_t>>) {
         if (in_field_name == "Biomes") {
            this->biomes = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::vector<std::int16_t>>>) {
         if (in_field_name == "Lights") {
            this->lights = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "PostProcessing") {
            this->post_processing = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<std::int32_t> biomes{};
   CarvingMasks carving_masks{};
   std::vector<Entity> entities{};
   Heightmaps heightmaps{};
   std::int64_t last_update{};
   std::vector<std::vector<std::int16_t>> lights{};
   std::int64_t inhabited_time{};
   std::vector<std::vector<std::int16_t>> post_processing{};
   std::vector<Section> sections{};
   std::string status{};
   Structures structures{};
   std::int8_t is_light_on{};
   std::int32_t x_pos{};
   std::int32_t z_pos{};
   Level() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Level deserialize_no_header(minecpp::nbt::Reader &r);
   static Level deserialize(std::istream &in);
};

class Chunk
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, Level>) {
         if (in_field_name == "Level") {
            this->level = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "DataVersion") {
            this->version = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::int32_t version{};
   Level level{};
   Chunk() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Chunk deserialize_no_header(minecpp::nbt::Reader &r);
   static Chunk deserialize(std::istream &in);
};

}// namespace minecpp::nbt::chunk::v1
#endif//MINECPP_NBT_CHUNK_V1_CHUNK_H
