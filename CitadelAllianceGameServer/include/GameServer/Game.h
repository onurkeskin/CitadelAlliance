#pragma once

#include <string>
#include "json/json.h"

#include "GameLogic/GameLogic.h"

class Game
{
public:
	Game();
	~Game();

	inline void setGameLogic(GameLogic& logic) { m_logic = logic; }

	std::string getGameStateJson();
protected:
	GameLogic m_logic;
	GameState m_state;
};

