#pragma once
#include "minecpp/game/mode.h"
#include "minecpp/game/rules.h"
#include <istream>
#include <minecpp/util/vec.h>

namespace minecpp::game::level {

struct BorderInfo {
   minecpp::util::Vec2 center;
   double damage_per_block;
   double size_lerp_target;
   long long size_lerp_time;
   double warning_blocks;
};

class Info {
 public:
   explicit Info(std::istream &s);

 private:
   BorderInfo border;
   long long day_time;
   uint8_t difficulty;
   game::Rules rules;
   game::Mode mode;
   bool features;
   long long seed;
   std::vector<std::string> server_brands;
   long long size_on_disk;
   long long time;
   int version_id;
   std::string version;
   uint8_t snapshot;
};

} // namespace minecpp::game::level
