#pragma once

#include "minecpp/net/play/Clientbound.schema.h"

#include <vector>

namespace minecpp::game
{

struct NetworkEntity
{
   net::play::cb::SpawnEntity entity_data;
   net::play::cb::SetEntityMetadata metadata;
   std::vector<net::play::cb::SetEquipment> equipment;
};

struct NetworkPlayer
{
   net::play::cb::SpawnPlayer player_data;
   net::play::cb::SetEntityMetadata metadata;
   std::vector<net::play::cb::SetEquipment> equipment;
};

}