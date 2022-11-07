#pragma once
#include <cstdint>
#include <mb/result.h>
#include <string>
#include <vector>

struct Config
{
   std::string server_bind_address;
   int server_bind_port;
   std::vector<std::string> engine_endpoints;
   std::string resources_registry;
   bool debug_logger;
};

Config get_config(const std::string &file_name);
