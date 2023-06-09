#pragma once

#include "ApiHandler.h"
#include "minecpp/service/storage/Storage.h"

#include <atomic>
#include <thread>

namespace minecpp::service::engine {

class World;

class TickSystem
{
 public:
   explicit TickSystem(World &world, ApiHandler &api_handler, storage::StorageClient &m_client);

   void run_tick(double delta_time);
   void loop();

 private:
   World &m_world;
   std::atomic_bool m_running{true};
   ApiHandler &m_api_handler;
   storage::StorageClient &m_storage_client;
   int m_last_tps{200};
};

}// namespace minecpp::service::engine