#include "player.h"

namespace Game {

Player::Player(uuid id, std::string &name)
    : id(id), player_name(std::move(name)) {}

void Player::set_entity_id(uint32_t entity_id) { this->entity_id = entity_id; }

uint32_t Player::get_entity_id() const { return entity_id; }

Mode Player::get_game_mode() const { return game_mode; }

const Player::Abilities &Player::get_abilities() const { return abilities; }

const RecipeBook &Player::get_recipe_book() const { return recipe_book; }

std::string_view Player::get_player_name() const { return player_name; }

uuid Player::get_id() const { return id; }

int Player::get_ping() const { return ping; }

void Player::set_ping(int ping) { this->ping = ping; }

void Player::Abilities::as_proto(minecpp::player::Abilities *abilities) const {
   abilities->set_fly_speed(fly_speed);
   abilities->set_walk_speed(walk_speed);
   abilities->set_flying(flying);
   abilities->set_instant_build(instant_build);
   abilities->set_may_fly(may_fly);
   abilities->set_may_build(may_build);
   abilities->set_invulnerable(invulnerable);
}

void Player::Abilities::from_proto(const minecpp::player::Abilities abilities) {
   fly_speed = abilities.fly_speed();
   walk_speed = abilities.walk_speed();
   flying = abilities.flying();
   instant_build = abilities.instant_build();
   may_fly = abilities.may_fly();
   may_build = abilities.may_build();
   invulnerable = abilities.invulnerable();
}

uint32_t Player::Abilities::flags() {
   return (invulnerable ? 1u : 0u) | (flying ? 2u : 0u) | (may_fly ? 4u : 0u) |
          (instant_build ? 8u : 0u);
}

} // namespace Game
