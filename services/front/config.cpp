#include "config.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <yaml-cpp/yaml.h>

Config get_config() {
   Config response;

   std::string cfg_filename = std::getenv("CONFIG_FILE");
   if (cfg_filename.empty()) {
      cfg_filename = "config.yml";
   }

   response.front_id = std::getenv("FRONT_ID");
   if (response.front_id.empty()) {
      response.front_id =
          boost::uuids::to_string(boost::uuids::random_generator()());
   }

   response.port = 25565;
   std::string env_port = std::getenv("PORT");
   if (!env_port.empty()) {
      response.port = std::stoi(env_port);
   }

   YAML::Node config = YAML::LoadFile(cfg_filename);
   response.engine_hosts =
       config["engine_hosts"].as<std::vector<std::string>>();
   response.recipe_path = config["recipes"].as<std::string>("recipes.dat");
   response.tags_path = config["tags"].as<std::string>("tags.dat");
   response.chunk_storage_host =
       config["chunk_storage_host"].as<std::string>("127.0.0.1:7600");

   return response;
}
