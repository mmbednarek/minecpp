#pragma once

namespace minecpp {

namespace entity {

namespace component {
class Player;
class Location;
class Rotation;
class Health;
class Velocity;
class Inventory;
class Streamer;
class Trader;
class Team;
class Abilities;
}// namespace component

namespace factory {
class Arrow;
class Item;
class Player;
class Totem;
class Trader;
}// namespace factory

}// namespace entity

// Components
using PlayerComponent    = entity::component::Player;
using LocationComponent  = entity::component::Location;
using RotationComponent  = entity::component::Rotation;
using HealthComponent    = entity::component::Health;
using VelocityComponent  = entity::component::Velocity;
using InventoryComponent = entity::component::Inventory;
using StreamerComponent  = entity::component::Streamer;
using TraderComponent    = entity::component::Trader;
using TeamComponent      = entity::component::Team;
using AbilitiesComponent = entity::component::Abilities;

// Factories
using ArrowFactory  = entity::factory::Arrow;
using ItemFactory   = entity::factory::Item;
using PlayerFactory = entity::factory::Player;
using TotemFactory  = entity::factory::Totem;
using TraderFactory = entity::factory::Trader;
}// namespace minecpp
