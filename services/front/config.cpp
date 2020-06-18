#include "config.h"
#include <yaml-cpp/yaml.h>

Config get_config() {
   Config response;

   std::string cfg_filename = std::getenv("CONFIG_FILE");
   if (cfg_filename.empty()) {
      cfg_filename = "config.yml";
   }

   //   response.own_ip = std::getenv("INSTANCE_IP");

   YAML::Node config = YAML::LoadFile(cfg_filename);
   response.engine_hosts =
       config["engine_hosts"].as<std::vector<std::string>>();
   response.port = config["front_port"].as<int>(4001);
   response.recipe_path = config["recipes"].as<std::string>("recipes.dat");
   response.tags_path = config["tags"].as<std::string>("tags.dat");
   response.chunk_storage_host =
       config["chunk_storage_host"].as<std::string>("127.0.0.1:7600");
   response.kafka_hosts =
       config["kafka_hosts"].as<std::string>("localhost:9092");

   return response;
}
