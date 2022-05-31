#pragma once
#include <string>
#include <memory>
#include "Statistics.h"

class Player
{
public:
	static Player& getInstance() {
		if (!_instance.get()) {
			Player::_instance.reset(new Player());
		}
		return *Player::_instance;
	}

	std::string name() const {
		return _playerName;
	}

	void setsName(const std::string& newName) {
		_playerName = newName;
	}

	Statistics& statistics() {
		return *_stats;
	}

	~Player() {
		if (_stats) {
			delete _stats;
		}
	}

	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
private:
	Player() :
		_playerName{},
		_stats{ new Statistics{} }
	{};
	std::string _playerName;
	Statistics* _stats;

	static std::shared_ptr<Player> _instance;
	
};

