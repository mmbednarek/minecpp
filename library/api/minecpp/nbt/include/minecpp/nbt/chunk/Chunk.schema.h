#pragma once
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::chunk {

class ArmorItem {
 public:
   std::int32_t no_empty{};
   ArmorItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ArmorItem deserialize_no_header(minecpp::nbt::Reader &r);
   static ArmorItem deserialize(std::istream &in);
};

class Attribute {
 public:
   double base{};
   std::string name{};
   Attribute() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Attribute deserialize_no_header(minecpp::nbt::Reader &r);
   static Attribute deserialize(std::istream &in);
};

class Memories {
 public:
   std::int32_t no_empty{};
   Memories() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Memories deserialize_no_header(minecpp::nbt::Reader &r);
   static Memories deserialize(std::istream &in);
};

class Brain {
 public:
   Memories memories{};
   Brain() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Brain deserialize_no_header(minecpp::nbt::Reader &r);
   static Brain deserialize(std::istream &in);
};

class HandItem {
 public:
   std::int32_t no_empty{};
   HandItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static HandItem deserialize_no_header(minecpp::nbt::Reader &r);
   static HandItem deserialize(std::istream &in);
};

class Entity {
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

class Heightmaps {
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

class PaletteItem {
 public:
   std::string name{};
   ::minecpp::nbt::CompoundContent properties{};
   PaletteItem() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static PaletteItem deserialize_no_header(minecpp::nbt::Reader &r);
   static PaletteItem deserialize(std::istream &in);
};

class Section {
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

class Start {
 public:
   std::string id{};
   Start() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Start deserialize_no_header(minecpp::nbt::Reader &r);
   static Start deserialize(std::istream &in);
};

class Structures {
 public:
   std::map<std::string, Start> starts{};
   Structures() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Structures deserialize_no_header(minecpp::nbt::Reader &r);
   static Structures deserialize(std::istream &in);
};

class CarvingMasks {
 public:
   std::vector<std::uint8_t> air{};
   std::vector<std::uint8_t> liquid{};
   CarvingMasks() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static CarvingMasks deserialize_no_header(minecpp::nbt::Reader &r);
   static CarvingMasks deserialize(std::istream &in);
};

class Level {
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

class Chunk {
 public:
   std::int32_t version{};
   Level level{};
   Chunk() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Chunk deserialize_no_header(minecpp::nbt::Reader &r);
   static Chunk deserialize(std::istream &in);
};

}
