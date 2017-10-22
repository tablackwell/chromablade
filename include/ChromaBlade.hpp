#ifndef CHROMABLADE
#define CHROMABLADE

#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include <PlayerView.hpp>
#include <GameLogic.hpp>
#include <TileMap.hpp>

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
    		PlayerView view;
		sf::RenderWindow window;
        sf::Clock fpsTimer;
        TileMap map;
};

#endif
