#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "GameLogic.hpp"

#include <cstdio>
#include <iostream>


/* The game application layer */
ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
    /* Starts on the Title screen. */
    m_state = GameState::Title;

    m_gameLogic.setGameApplication(this);
    m_view.setGameLogic(&m_gameLogic);
    m_view.setContext(&m_window);
    m_view.setGameApplication(this);
    m_eventManager.setWindow(&m_window);
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);
    registerListeners();
}


void ChromaBlade::init(){
    m_gameLogic.init();
    m_view.init();

    /* Play music on start. */
    m_audio.init();

    /* Attach PlayerView, GameLogic, and Audio to ProcessManager. */
    m_processManager.attachProcess(&m_view);
    m_processManager.attachProcess(&m_gameLogic);
    m_processManager.attachProcess(&m_audio);
}


/* Main game loop */
void ChromaBlade::run(){
	while(m_window.isOpen()){
        float deltaTime = m_fpsTimer.restart().asSeconds();
        handleInput(deltaTime);
        update(deltaTime);
        handleEvents(deltaTime);
        render();
	}
}


/* Calls playerView to handle player inputs */
void ChromaBlade::handleInput(float deltaTime) {
    m_view.handleInput(deltaTime);
}


/* Updates game logic */
void ChromaBlade::update(float &deltaTime) {
    /* Naive switch to handle game state transitions. */
    switch (m_state) {
        case GameState::Title:
            break;
        case GameState::Hub:
            m_processManager.update(deltaTime);
            break;
    }
}


/* Processes events in eventManager */
void ChromaBlade::handleEvents(float deltaTime) {
    m_eventManager.update(deltaTime);
}


/* Calls playerView to render */
void ChromaBlade::render() {
    m_view.draw();
}


/* Sets the game state */
void ChromaBlade::setState(GameState state) {
    m_state = state;
}


 /* Gets the game state */
GameState ChromaBlade::getState() {
    return m_state;
}


/* Allows other components to register listeners */
void ChromaBlade::registerListener(EventListener listener, EventType eventType) {
    m_eventManager.addListener(listener, eventType);
}


/* Allows other components to queue events */
void ChromaBlade::queueEvent(EventInterface *event) {
    m_eventManager.queueEvent(event);
}


void ChromaBlade::registerListeners() {
    // Subscribe to events.
    std::function<void(const EventInterface &event)> changeState = std::bind(&ChromaBlade::updateState, this, std::placeholders::_1);
    const EventListener m_listener1 = EventListener(changeState, EventType::changeStateEvent);
    m_eventManager.addListener(m_listener1, EventType::changeStateEvent);
}


/* Update m_state to game state. */
void ChromaBlade::updateState(const EventInterface &event) {
    const EventInterface *ptr = &event;
    if (const ChangeStateEvent *stateEvent = dynamic_cast<const ChangeStateEvent*>(ptr)){
        m_state = stateEvent->getGameState();
        switch(m_state) {
            case GameState::Title:
                std::cout<<"Changed state to Title!\n";
                break;
            case GameState::Hub:
                m_view.setListener();
                m_gameLogic.setListener();
                std::cout<<"Changed state to Game!\n";
                break;
            case GameState::RedLevel:
                std::cout<<"Changed state to RedLevel!\n";
                break;
        }
    }
}
