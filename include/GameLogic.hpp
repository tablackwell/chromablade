#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

enum Level { red, blue, yellow, green, orange, purple };

class GameLogic{
	public:
		GameLogic();
		void init();
		void update(float deltaTime);
		Level getLevel();
	private:
		Level level;
	private:
};

#endif
