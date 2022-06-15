#pragma once
#include <cstdint>
#include <mb/result.h>
#include <string>
#include <vector>

struct Config
{
   std::vector<std::string> engine_hosts;
   uint16_t port;
   std::string recipe_path;
   std::string tags_path;
   std::string chunk_storage_host;
   std::string front_id;
   std::string registry_path;
};

Config get_config();
