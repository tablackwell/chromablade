#ifndef CHROMABLADE_HPP
#define CHROMABLADE_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include "ProcessManager.hpp"
#include "EventManager.hpp"
#include "ChangeStateEvent.hpp"
#include "GameLogic.hpp"
#include "PlayerView.hpp"
#include "GameState.hpp"
#include "Audio.hpp"
#include "EventType.hpp"
#include "Macros.hpp"


class ChromaBlade{
public:
    ChromaBlade();
    void init();
    void run();
    GameState getState();
    GameState getPrevState();
    void setState(GameState state);
    void registerListener(EventListener listener, EventType eventType);
    void queueEvent(EventInterface *event);
    bool inDebugMode();
    void setDebug();

private: // functions
    void handleInput(float);
    void update(float &deltaTime);
    void render();
    void handleEvents(float deltaTime);
    void registerListeners();
    void updateState(const EventInterface &event);

private: // data
    GameLogic m_gameLogic;
    PlayerView m_view;
    EventManager m_eventManager;
    sf::RenderWindow m_window;
    sf::Clock m_fpsTimer;
    ProcessManager m_processManager;
    Audio m_audio;
    GameState m_state;
    GameState m_prevState;
    bool inDebug = false;
};

#endif
