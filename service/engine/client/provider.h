#pragma once
#include <boost/uuid/uuid.hpp>
#include <map>
#include <mb/result.h>
#include <minecpp/service/engine/api.h>
#include <random>
#include <string>
#include <vector>

namespace minecpp::service::engine {

struct Config
{
   std::vector<std::string> addresses;
};

using PlayerService = std::unique_ptr<minecpp::proto::service::engine::v1::EngineService::Stub>;
using boost::uuids::uuid;

}// namespace minecpp::service::engine
