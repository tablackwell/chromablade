#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include "Process.hpp"
#include "Player.hpp"
#include <tuple>

enum Level { red, blue, yellow, green, orange, purple };

class GameLogic : public Process {
	public:
		GameLogic();
		void init();
		void update(float &deltaTime);
		Level getLevel();
		void setCharPosition(std::tuple<float, float> position);

	private:
		Level m_level;
		Player m_player;
	private:
};

#endif
