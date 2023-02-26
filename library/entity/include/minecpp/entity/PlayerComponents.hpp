#pragma once

#include "component/Health.h"
#include "component/Inventory.h"
#include "component/Location.h"
#include "component/Player.h"
#include "component/Streamer.h"
#include "component/Velocity.h"

namespace minecpp {
using PlayerComponent    = entity::component::Player;
using LocationComponent  = entity::component::Location;
using RotationComponent  = entity::component::Rotation;
using HealthComponent    = entity::component::Health;
using VelocityComponent  = entity::component::Velocity;
using InventoryComponent = entity::component::Inventory;
using StreamerComponent  = entity::component::Streamer;
}// namespace minecpp
