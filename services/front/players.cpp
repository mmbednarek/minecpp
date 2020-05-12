#include "players.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <stdexcept>

namespace Front {

static boost::uuids::basic_random_generator<boost::mt19937> gen;

Player::Player(std::string name) : _name(std::move(name)), id(gen()) {}

const std::string &Player::name() const { return _name; }

LoginState Player::state() const { return _state; }

void Player::set_state(LoginState s) { _state = s; }

std::string Player::user_id_str() { return boost::uuids::to_string(id); }

const boost::uuids::uuid &Player::user_id() { return id; }

void PlayerManager::add_player(Player *p) {
   if (p->name().empty()) {
      throw PlayerException("empty player name");
   }

   auto id = boost::uuids::to_string(p->user_id());

   if (players.find(id) != players.end()) {
      throw PlayerException("player already added");
   }

   players[id] = std::unique_ptr<Player>(p);
}

Player &PlayerManager::get_player(const boost::uuids::uuid id) {
   return *players[boost::uuids::to_string(id)];
}

PlayerException::PlayerException(const char *msg) : runtime_error(msg) {}

PlayerException::PlayerException(const std::string &s)
    : std::runtime_error(s) {}

} // namespace Front
