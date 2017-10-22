#ifndef CHROMABLADE
#define CHROMABLADE

#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include "PlayerView.hpp"
#include "GameLogic.hpp"
#include "TileMap.hpp"
#include "Title.hpp"

#define WIDTH 800
#define HEIGHT 600

class ChromaBlade{
public:
    ChromaBlade();
    void init();
    void run();
    void pause();
    void shutdown();

private: // functions

private: // vars and objs
    GameLogic m_gameLogic;
    PlayerView m_view;
    sf::RenderWindow m_window;
    sf::Clock m_fpsTimer;
    TileMap m_map;
    Title m_title;
};

#endif
