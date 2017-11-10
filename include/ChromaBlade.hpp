#ifndef CHROMABLADE_HPP
#define CHROMABLADE_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include "ProcessManager.hpp"
#include "PlayerView.hpp"
#include "EventManager.hpp"
#include "ChangeStateEvent.hpp"
#include "GameLogic.hpp"
#include "GameState.hpp"
#include "TileMap.hpp"
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
    void shutdown(const EventInterface &event);

private: // functions
    void handleEvents(float deltaTime);
    void update(float &deltaTime);
    void updateState(const EventInterface &event);
    void render();
    GameState getState();
    void setState(GameState state);
    void handleInput(float);

private: // vars and objs
    GameLogic m_gameLogic;
    PlayerView m_view;
    EventManager m_eventManager;
    sf::RenderWindow m_window;
    sf::Clock m_fpsTimer;
    TileMap m_map;
    TileMap m_overlay;
    Title m_title;
    ProcessManager m_processManager;
    Audio m_audio;
    GameState m_state;
};

#endif
