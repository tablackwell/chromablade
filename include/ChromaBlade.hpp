#ifndef CHROMABLADE_HPP
#define CHROMABLADE_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include "ProcessManager.hpp"
#include "PlayerView.hpp"
#include "GameLogic.hpp"
#include "GameState.hpp"
#include "TileMap.hpp"
#include "CollisionMap.hpp"
#include "Title.hpp"
#include "Audio.hpp"

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
    void handleEvents();
    void update(float &deltaTime);
    void render();

private: // vars and objs
    GameLogic m_gameLogic;
    PlayerView m_view;
    sf::RenderWindow m_window;
    sf::Clock m_fpsTimer;
    TileMap m_map;
    TileMap m_overlay;
    TileMap m_collisionMap;
    Title m_title;
    ProcessManager m_processManager;
    Audio m_audio;
    GameState m_state;
};

#endif
