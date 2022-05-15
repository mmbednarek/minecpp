#include "config.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <mb/core.h>
#include <yaml-cpp/yaml.h>

Config get_config()
{
   Config response;
   response.front_id = mb::getenv("FRONT_ID").unwrap(boost::uuids::to_string(boost::uuids::random_generator()()));
   response.port     = std::stoi(mb::getenv("PORT").unwrap("25565"));

   auto cfg_filename = mb::getenv("CONFIG_FILE").unwrap("config.yml");

   YAML::Node config           = YAML::LoadFile(cfg_filename);
   response.engine_hosts       = config["engine_hosts"].as<std::vector<std::string>>();
   response.recipe_path        = config["recipes"].as<std::string>("recipes.dat");
   response.tags_path          = config["tags"].as<std::string>("tags.dat");
   response.chunk_storage_host = config["chunk_storage_host"].as<std::string>("127.0.0.1:7600");

   return response;
}
