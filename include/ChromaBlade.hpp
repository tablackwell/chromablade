#ifndef CHROMABLADE
#define CHROMABLADE

#include <View.hpp>
#include <GameLogic.hpp>
#include <SFML/System/Clock.hpp>

class ChromaBlade{
    public:
    	ChromaBlade();
    	void init();
    	void run();
    	void pause();
    	void shutdown();

    private: // functions

    private: // vars and objs
    	GameLogic gameLogic;
    	View view;
		sf::RenderWindow window;
        sf::Clock fpsTimer;
};

#endif
