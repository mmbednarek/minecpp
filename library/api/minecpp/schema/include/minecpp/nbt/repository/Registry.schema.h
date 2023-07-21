#pragma once
#include "minecpp/nbt/repository/Biome.schema.h"
#include "minecpp/nbt/repository/Chat.schema.h"
#include "minecpp/nbt/repository/Damage.schema.h"
#include "minecpp/nbt/repository/Dimension.schema.h"
#include "minecpp/nbt/repository/Trim.schema.h"
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::repository {

class Registry {
 public:
   ChatTypes chat_types{};
   DamageTypes damage_types{};
   DimensionTypes dimension_types{};
   TrimMaterialTypes trim_materials{};
   TrimPatternTypes trim_patterns{};
   BiomeTypes biomes{};
   Registry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Registry deserialize_no_header(minecpp::nbt::Reader &r);
   static Registry deserialize(std::istream &in);
};

}
