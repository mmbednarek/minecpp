#include "Config.h"
#include <yaml-cpp/yaml.h>

Config get_config(const std::string &file_name)
{
   YAML::Node config = YAML::LoadFile(file_name);

   Config response;
   response.server_bind_address = config["server"]["bind_address"].as<std::string>("0.0.0.0");
   response.server_bind_port    = config["server"]["bind_port"].as<int>(25565);
   response.resources_registry  = config["resources"]["registry"].as<std::string>("registry.bin");
   response.engine_endpoints    = config["engine"]["endpoints"].as<std::vector<std::string>>();
   response.debug_logger        = config["debug_logger"].as<bool>(false);
   return response;
}
