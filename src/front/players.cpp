#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <stdexcept>
#include "players.h"

namespace Front {

static boost::uuids::basic_random_generator<boost::mt19937> gen;

Player::Player(std::string name) : _name(std::move(name)), id(gen()) {
}

const std::string& Player::name() const {
	return _name;
}

LoginState Player::state() const {
	return _state;
}

void Player::set_state(LoginState s) {
	_state = s;
}

std::string Player::user_id() {
	return boost::uuids::to_string(id);
}

void PlayerManager::add_player(Player *p) {
	if(p->name().empty()) {
		throw PlayerException("empty player name");
	}

	if(players.find(p->name()) != players.end()) {
		throw PlayerException("player already added");
	}

	players[p->name()] = std::unique_ptr<Player>(p);
}

Player& PlayerManager::get_player(const std::string& name) {
	return *players[name];
}

PlayerException::PlayerException(const char *msg) : runtime_error(msg) {
}

PlayerException::PlayerException(const std::string& s) : std::runtime_error(s) {
}

}
