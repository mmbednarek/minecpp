#pragma once
#include <boost/uuid/uuid.hpp>
#include <map>
#include <memory>
#include <string>

namespace Front {

enum LoginState : uint8_t  {
	Hello,
	Key,
	Negotiating
};

class Player {
public:
	explicit Player(std::string name);
	[[nodiscard]] const std::string& name() const;
	[[nodiscard]] LoginState state() const;
	void set_state(LoginState s);
	std::string user_id();
private:
	std::string _name;
	LoginState _state = Hello;
	boost::uuids::uuid id;
};

class PlayerManager {
public:
	void add_player(Player *p);
	Player& get_player(const std::string& name);
private:
	std::map<std::string, std::unique_ptr<Player>> players;
};

class PlayerException : public std::runtime_error {
public:
	explicit PlayerException(const std::string& s);
	explicit PlayerException(const char *msg);
};

}


