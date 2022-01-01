#ifndef MINECPP_NBT_CHUNK_V1_CHUNK_H
#define MINECPP_NBT_CHUNK_V1_CHUNK_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/writer.h>
#include <string>
#include <vector>

namespace minecpp::nbt::chunk::v1 {

#ifndef MINECPP_NBT_CHUNK_V1_CHUNK_H_OFFSET_CLASS
#define MINECPP_NBT_CHUNK_V1_CHUNK_H_OFFSET_CLASS
class __nbt_idl_offset {
 public:
   mb::size offset{};
   mb::size size{};
   int id{};
};
#endif//MINECPP_NBT_CHUNK_V1_CHUNK_H_OFFSET_CLASS

class ArmorItem {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   ArmorItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ArmorItem deserialize_no_header(minecpp::nbt::Reader &r);
   static ArmorItem deserialize(std::istream &in);
};

class Attribute {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   double base{};
   std::string name{};
   Attribute() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Attribute deserialize_no_header(minecpp::nbt::Reader &r);
   static Attribute deserialize(std::istream &in);
};

class Memories {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   Memories() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Memories deserialize_no_header(minecpp::nbt::Reader &r);
   static Memories deserialize(std::istream &in);
};

class Brain {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   Memories memories{};
   Brain() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Brain deserialize_no_header(minecpp::nbt::Reader &r);
   static Brain deserialize(std::istream &in);
};

class HandItem {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   HandItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static HandItem deserialize_no_header(minecpp::nbt::Reader &r);
   static HandItem deserialize(std::istream &in);
};

class Entity {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
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
   void serialize(std::ostream &out, std::string_view name) const;
   static Entity deserialize_no_header(minecpp::nbt::Reader &r);
   static Entity deserialize(std::istream &in);
};

class Heightmaps {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
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
   void serialize(std::ostream &out, std::string_view name) const;
   static Heightmaps deserialize_no_header(minecpp::nbt::Reader &r);
   static Heightmaps deserialize(std::istream &in);
};

class PaletteItem {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   std::string name{};
   minecpp::nbt::CompoundContent properties{};
   PaletteItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static PaletteItem deserialize_no_header(minecpp::nbt::Reader &r);
   static PaletteItem deserialize(std::istream &in);
};

class Section {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   std::int8_t y{};
   std::vector<std::uint8_t> block_light{};
   std::vector<std::uint8_t> sky_light{};
   std::vector<std::int64_t> block_states{};
   std::vector<PaletteItem> palette{};
   Section() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Section deserialize_no_header(minecpp::nbt::Reader &r);
   static Section deserialize(std::istream &in);
};

class Start {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   std::string id{};
   Start() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Start deserialize_no_header(minecpp::nbt::Reader &r);
   static Start deserialize(std::istream &in);
};

class Structures {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   std::map<std::string, Start> starts{};
   Structures() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Structures deserialize_no_header(minecpp::nbt::Reader &r);
   static Structures deserialize(std::istream &in);
};

class CarvingMasks {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   std::vector<std::uint8_t> air{};
   std::vector<std::uint8_t> liquid{};
   CarvingMasks() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static CarvingMasks deserialize_no_header(minecpp::nbt::Reader &r);
   static CarvingMasks deserialize(std::istream &in);
};

class Level {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
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
   void serialize(std::ostream &out, std::string_view name) const;
   static Level deserialize_no_header(minecpp::nbt::Reader &r);
   static Level deserialize(std::istream &in);
};

class Chunk {
   static std::unordered_map<std::string, __nbt_idl_offset> __xx_offsets;
   int __xx_get_id(const std::string &name) const;

   template<typename T>
   void __xx_put(const std::string &name, T value) {
      auto it = __xx_offsets.find(name);
      if (it == __xx_offsets.end()) {
         return;
      }
      if (it->second.size != sizeof(T)) {
         return;
      }
      T *ptr = reinterpret_cast<T *>(reinterpret_cast<char *>(this) + it->second.offset);
      ptr->~T();
      *ptr = std::forward<T>(value);
   }

 public:
   std::int32_t version{};
   Level level{};
   Chunk() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Chunk deserialize_no_header(minecpp::nbt::Reader &r);
   static Chunk deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_CHUNK_V1_CHUNK_H
