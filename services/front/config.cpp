#include "config.h"
#include <yaml-cpp/yaml.h>

Config get_config() {
   Config response;

   std::string cfg_filename = std::getenv("CONFIG_FILE");
   if (cfg_filename.empty()) {
      cfg_filename = "config.yml";
   }

   response.own_ip = std::getenv("INSTANCE_IP");

   YAML::Node config = YAML::LoadFile(cfg_filename);
   response.engine_hosts = config["engine_hosts"].as<std::vector<std::string>>();
   response.port = config["front_port"].as<int>(4001);
   response.recipe_path = config["recipes"].as<std::string>("recipes.dat");
   response.tags_path = config["tags"].as<std::string>("tags.dat");

   return response;
}
