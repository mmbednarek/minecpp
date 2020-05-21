#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct Config {
   std::string own_ip;
   std::vector<std::string> engine_hosts;
   uint16_t port;
   std::string recipe_path;
   std::string tags_path;
};

Config get_config();
